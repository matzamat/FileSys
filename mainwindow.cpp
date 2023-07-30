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

void MainWindow::on_comboBox_activated(int index)
{
    // Check if the first option is selected
    if(index==0)
    {
        // Open a file dialog to choose a file to open
        QString filename = QFileDialog::getOpenFileName(this, "Open the file");
        QFile file(filename);
        currentFile = filename;

        // If the file cannot be opened, display a warning message
        if(!file.open(QIODevice::ReadOnly | QFile::Text)){
            QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        }

        // Set the text browser widget to display the selected file name
        ui->textBrowser->setText(filename);
        setWindowTitle(filename);

        // Read the contents of the file and set the text edit widget to display the text
        QTextStream in(&file);
        QString text = in.readAll();
        ui->textEdit->setText(text);
        file.close();
    } 
    // Check if the second option is selected
    else if(index==1)
    {
        // Open a file dialog to choose a file to save as
        QString filename = QFileDialog::getSaveFileName(this, "Save as");
        QFile file(filename);

        // If the file cannot be opened for writing, display a warning message
        if(!file.open(QFile::WriteOnly | QFile::Text)){
            QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
            return;
        }

        // Set the current file name and window title
        currentFile = filename;
        setWindowTitle(filename);

        // Write the text from the text edit widget to the file
        QTextStream out(&file);
        QString text = ui->textEdit->toPlainText();
        out<<text;
        file.close();
    }
}
