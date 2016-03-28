#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{    

    _graph = new Graph(
                false,
                true,
                false,
                "/home/nlimpert/FH\ Aachen/MMI/Graph2.txt");

    DFS dfs(_graph);
    dfs.perform_recursive_DFS(1);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_select_file_clicked()
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

void MainWindow::on_pushButton_read_clicked()
{
    new Graph(
                ui->radioButton_weighted_yes->isChecked(),
                ui->radioButton_directed->isChecked(),
                ui->radioButton_adjacency_matrix->isChecked(),
                ui->label_chosen_file->text());
    this->hide();

}

void MainWindow::on_pushButton_cancel_clicked()
{
    QApplication::quit();
}
