#include "mainwindow.h"
#include "translator.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QClipboard>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->translateButton, &QPushButton::clicked, this, &MainWindow::translate);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::clearEditors);
    connect(ui->exampleButton, &QPushButton::clicked, this, &MainWindow::loadExample);
    connect(ui->copyButton, &QPushButton::clicked, this, &MainWindow::copyOutput);
}
MainWindow::~MainWindow() { delete ui; }

void MainWindow::translate()
{
    const TranslationResult r = translatePythonToCSharp(ui->pythonEditor->toPlainText());
    ui->csharpEditor->setPlainText(r.code);
    if (r.success) { ui->statusLabel->setText("Traduccion completada"); ui->statusLabel->setStyleSheet("color:#137333;font-weight:bold"); }
    else { ui->statusLabel->setText(QString("Traduccion parcial: %1 error(es)").arg(r.errors.size())); ui->statusLabel->setStyleSheet("color:#b42318;font-weight:bold"); QMessageBox::warning(this, "Errores de traduccion", r.errors.join('\n')); }
}
void MainWindow::clearEditors() { ui->pythonEditor->clear(); ui->csharpEditor->clear(); ui->statusLabel->setText("Listo"); ui->statusLabel->setStyleSheet({}); }
void MainWindow::copyOutput() { QApplication::clipboard()->setText(ui->csharpEditor->toPlainText()); ui->statusLabel->setText("Codigo C# copiado"); }
void MainWindow::loadExample()
{
    ui->pythonEditor->setPlainText(
        "nombre = \"Elvy\"\n"
        "edad = 22\n"
        "promedio = 89.5\n"
        "aprobado = True\n\n"
        "if edad >= 18:\n"
        "    print(nombre)\n"
        "    print(\"Mayor de edad\")\n"
        "else:\n"
        "    print(\"Menor de edad\")\n\n"
        "for i in range(0, 3):\n"
        "    print(i)\n");
}
