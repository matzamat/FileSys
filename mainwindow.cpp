#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
ui->setupUi(this);
}

MainWindow::~MainWindow()
{
delete ui;
}


void MainWindow::openFile()
{
QString filename = QFileDialog::getOpenFileName(this, "Open the file");
QFile file(filename);
currentFile = filename;

if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
    QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
    return;
}

ui->textBrowser->setText(filename);
setWindowTitle(filename);

QTextStream in(&file);
QString text = in.readAll();
ui->textEdit->setText(text);

file.close();
}

void MainWindow::saveFile()
{
QString filename = QFileDialog::getSaveFileName(this, "Save as");
QFile file(filename);

if (!file.open(QFile::WriteOnly | QFile::Text)) {
    QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
    return;
}

currentFile = filename;
setWindowTitle(filename);

QTextStream out(&file);
QString text = ui->textEdit->toPlainText();
out << text;

file.close();
}

void MainWindow::on_comboBox_activated(int index)
{
if (index == 0) {
openFile();
} else if (index == 1) {
saveFile();
}
}
