#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

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

void MainWindow::on_pushButton_Select_File_clicked()
{
    //Start gui to choose graph
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Select File"),
                "C://",
                "Text File (*.txt);;All Files (*.*)"
                );

    //Set label in gui to chosen filename path
    ui->label_chosen_file->setText(filename);
}

void MainWindow::on_pushButton_Read_clicked()
{
    /*
     * TODO
     * Read graph depending on matrixtype
     */

    if(ui->radioButton_Adjacency_matrix->isChecked()){

    }else{
        //Only to options -> definitly Edgelist now
    }
}

void MainWindow::on_pushButton_Cancel_clicked()
{
    QApplication::quit();
}
