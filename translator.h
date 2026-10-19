#pragma once
#include <QString>
#include <QStringList>

struct TranslationResult
{
    bool success = false;
    QString code;
    QStringList errors;
};

TranslationResult translatePythonToCSharp(const QString &python);
