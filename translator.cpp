#include "translator.h"
#include <QHash>
#include <QRegularExpression>

namespace {
QString indent(int level) { return QString(level * 4, ' '); }

QString expression(QString value)
{
    value.replace(QRegularExpression("\\bTrue\\b"), "true");
    value.replace(QRegularExpression("\\bFalse\\b"), "false");
    value.replace(QRegularExpression("\\bNone\\b"), "null");
    value.replace(" and ", " && ");
    value.replace(" or ", " || ");
    value.replace(QRegularExpression("\\bnot\\s+"), "!");
    value.replace("//", "/");
    return value.trimmed();
}

QString inferredType(const QString &value)
{
    const QString v = value.trimmed();
    if (v == "True" || v == "False") return "bool";
    if ((v.startsWith('"') && v.endsWith('"')) || (v.startsWith('\'') && v.endsWith('\''))) return "string";
    if (QRegularExpression("^-?\\d+$").match(v).hasMatch()) return "int";
    if (QRegularExpression("^-?\\d+\\.\\d+$").match(v).hasMatch()) return "double";
    if (v.startsWith('[') && v.endsWith(']')) return "var";
    return "var";
}

QString convertStringQuotes(QString value)
{
    if (value.size() >= 2 && value.startsWith('\'') && value.endsWith('\'')) {
        value[0] = '"';
        value[value.size() - 1] = '"';
    }
    return value;
}
}

TranslationResult translatePythonToCSharp(const QString &python)
{
    TranslationResult result;
    QStringList output = {"using System;", "", "public class Programa", "{"};
    QHash<QString, QString> variables;
    QList<int> indentStack = {0};
    int csLevel = 1;
    bool hasMain = false;
    const QStringList lines = python.split('\n');

    for (int index = 0; index < lines.size(); ++index) {
        const QString raw = lines.at(index);
        if (raw.trimmed().isEmpty()) continue;
        int spaces = 0;
        while (spaces < raw.size() && raw.at(spaces) == ' ') spaces++;
        if (spaces % 4 != 0) {
            result.errors << QString("Linea %1: la indentacion debe usar grupos de 4 espacios.").arg(index + 1);
            continue;
        }
        const int pyLevel = spaces / 4;
        while (indentStack.size() > 1 && pyLevel < indentStack.last()) {
            indentStack.removeLast();
            csLevel--;
            output << indent(csLevel) + "}";
        }

        QString line = raw.trimmed();
        if (line.startsWith('#')) {
            output << indent(csLevel) + "//" + line.mid(1);
            continue;
        }

        QRegularExpressionMatch m;
        m = QRegularExpression("^def\\s+(\\w+)\\s*\\(([^)]*)\\)\\s*:$").match(line);
        if (m.hasMatch()) {
            const QString name = m.captured(1);
            QStringList parameters;
            for (const QString &p : m.captured(2).split(',', Qt::SkipEmptyParts))
                parameters << "dynamic " + p.trimmed();
            output << indent(csLevel) + QString("public static dynamic %1(%2)").arg(name, parameters.join(", "));
            output << indent(csLevel) + "{";
            csLevel++; indentStack << pyLevel + 1;
            continue;
        }
        if (line == "if __name__ == \"__main__\":" || line == "if __name__ == '__main__':") {
            output << indent(csLevel) + "public static void Main(string[] args)";
            output << indent(csLevel) + "{";
            hasMain = true; csLevel++; indentStack << pyLevel + 1;
            continue;
        }
        m = QRegularExpression("^if\\s+(.+)\\s*:$").match(line);
        if (m.hasMatch()) {
            output << indent(csLevel) + "if (" + expression(m.captured(1)) + ")";
            output << indent(csLevel) + "{";
            csLevel++; indentStack << pyLevel + 1; continue;
        }
        m = QRegularExpression("^elif\\s+(.+)\\s*:$").match(line);
        if (m.hasMatch()) {
            if (indentStack.size() > 1) { indentStack.removeLast(); csLevel--; output << indent(csLevel) + "}"; }
            output << indent(csLevel) + "else if (" + expression(m.captured(1)) + ")";
            output << indent(csLevel) + "{";
            csLevel++; indentStack << pyLevel + 1; continue;
        }
        if (line == "else:") {
            if (indentStack.size() > 1) { indentStack.removeLast(); csLevel--; output << indent(csLevel) + "}"; }
            output << indent(csLevel) + "else";
            output << indent(csLevel) + "{";
            csLevel++; indentStack << pyLevel + 1; continue;
        }
        m = QRegularExpression("^while\\s+(.+)\\s*:$").match(line);
        if (m.hasMatch()) {
            output << indent(csLevel) + "while (" + expression(m.captured(1)) + ")";
            output << indent(csLevel) + "{";
            csLevel++; indentStack << pyLevel + 1; continue;
        }
        m = QRegularExpression("^for\\s+(\\w+)\\s+in\\s+range\\(([^,()]+)(?:,\\s*([^,()]+))?(?:,\\s*([^()]+))?\\)\\s*:$").match(line);
        if (m.hasMatch()) {
            const QString var = m.captured(1);
            const QString start = m.captured(3).isEmpty() ? "0" : expression(m.captured(2));
            const QString end = expression(m.captured(3).isEmpty() ? m.captured(2) : m.captured(3));
            const QString step = m.captured(4).isEmpty() ? "1" : expression(m.captured(4));
            output << indent(csLevel) + QString("for (int %1 = %2; %1 < %3; %1 += %4)").arg(var, start, end, step);
            output << indent(csLevel) + "{";
            csLevel++; indentStack << pyLevel + 1; variables.insert(var, "int"); continue;
        }
        m = QRegularExpression("^print\\s*\\((.*)\\)\\s*$").match(line);
        if (m.hasMatch()) { output << indent(csLevel) + "Console.WriteLine(" + expression(convertStringQuotes(m.captured(1))) + ");"; continue; }
        m = QRegularExpression("^return(?:\\s+(.+))?$").match(line);
        if (m.hasMatch()) { output << indent(csLevel) + (m.captured(1).isEmpty() ? "return;" : "return " + expression(convertStringQuotes(m.captured(1))) + ";"); continue; }
        m = QRegularExpression("^(\\w+)\\s*=\\s*(.+)$").match(line);
        if (m.hasMatch()) {
            const QString name = m.captured(1);
            const QString value = convertStringQuotes(m.captured(2));
            if (!variables.contains(name)) {
                const QString type = inferredType(value);
                variables.insert(name, type);
                output << indent(csLevel) + type + " " + name + " = " + expression(value) + ";";
            } else output << indent(csLevel) + name + " = " + expression(value) + ";";
            continue;
        }
        m = QRegularExpression("^(\\w+)\\s*\\((.*)\\)$").match(line);
        if (m.hasMatch()) { output << indent(csLevel) + m.captured(1) + "(" + expression(m.captured(2)) + ");"; continue; }
        result.errors << QString("Linea %1: instruccion no reconocida: %2").arg(index + 1).arg(line);
    }
    while (indentStack.size() > 1) { indentStack.removeLast(); csLevel--; output << indent(csLevel) + "}"; }
    if (!hasMain) {
        QStringList body = output.mid(4);
        output = {"using System;", "", "public class Programa", "{", "    public static void Main(string[] args)", "    {"};
        for (const QString &bodyLine : body) output << "    " + bodyLine;
        output << "    }";
    }
    output << "}";
    result.success = result.errors.isEmpty();
    result.code = output.join('\n');
    return result;
}
