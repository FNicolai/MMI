#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{    

//    _graph = new Graph(
//                false,
//                false,
//                true,
//                "../../Graph1.txt");

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
    ui->pushButton_read->setEnabled(true);
}

void MainWindow::on_pushButton_read_clicked()
{
    _graph = new Graph(
                ui->radioButton_weighted_yes->isChecked(),
                ui->radioButton_directed->isChecked(),
                ui->radioButton_adjacency_matrix->isChecked() ? Graph::ADJACENCY_MATRIX : Graph::EDGELIST,
                ui->label_chosen_file->text());

    ui->pushButton_read->setText("Done!");
    ui->pushButton_read->setEnabled(false);
    ui->spinBox_start_node->setMaximum(_graph->get_nodes().size()-1);
    QString max_node = "(Max. is ";
    max_node.append(QString::number(_graph->get_nodes().size()-1));
    max_node.append(")");
    ui->label_max_node->setText(max_node);


    ui->groupBox_algorithems->setEnabled(true);


}

void MainWindow::on_pushButton_cancel_clicked()
{
    QApplication::quit();
}

void MainWindow::on_pushButton_start_bfs_clicked()
{
    BFS bfs(_graph);
    bfs.perform_iterative_BFS(ui->spinBox_start_node->value());
    _graph->reset_visited();
}

void MainWindow::on_pushButton_start_dfs_clicked()
{
    DFS dfs(_graph);
    dfs.perform_recursive_DFS(ui->spinBox_start_node->value());
    _graph->reset_visited();
}

void MainWindow::on_pushButton_count_components_clicked()
{
    Components components(_graph);
    components.perform_connected_compontents();
    _graph->reset_visited();
}
