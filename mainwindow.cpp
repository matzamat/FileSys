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
    // Open file dialog to select a file
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(filename);
    currentFile = filename;

    // If the file cannot be opened, show a warning message box and return
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    // Set the text browser widget with the selected file name
    ui->textBrowser->setText(filename);
    setWindowTitle(filename);

    // Read the contents of the file using a QTextStream and set the text edit widget with the file content
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);

    file.close();
}

void MainWindow::saveFile()
{
    // Open file dialog to specify the save location and file name
    QString filename = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(filename);

    // If the file cannot be opened for writing, show a warning message box and return
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    // Set the current file and window title to the selected file name
    currentFile = filename;
    setWindowTitle(filename);

    // Write the contents of the text edit widget to the file using a QTextStream
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;

    file.close();
}

void MainWindow::on_comboBox_activated(int index)
{
    // When the combo box selection changes, check the index and perform either openFile() or saveFile()
    if (index == 0) {
        openFile();
    } else if (index == 1) {
        saveFile();
    }
}
