#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionSave_as_triggered()
{
    filename=QFileDialog::getSaveFileName(this, "Save as");
    QFile file(filename);
    current_file=filename;
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file: "+file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream out(&file);
    text=ui->textEdit->toPlainText();
    out<<text;
    file.close();
}

void MainWindow::on_actionNew_triggered()
{
    current_file.clear();
    ui->textEdit->setText(QString());
}

void MainWindow::on_actionOpen_triggered()
{
    filename=QFileDialog::getOpenFileName(this, "Open the File");
    QFile file(filename);
    current_file=filename;
    if(!file.open(QIODevice::ReadOnly|QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot Open File: "+file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    text=in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionPrint_triggered()
{
    printer.setPrinterName("Printer Name");
    QPrintDialog pdialog(&printer, this);
    if(pdialog.exec()==QDialog::Rejected){
        QMessageBox::warning(this, "Warning", "Cannot access printer");
        return;
    }
    ui->textEdit->print(&printer);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
     ui->textEdit->cut();
}

void MainWindow::on_actionPaste_2_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}
