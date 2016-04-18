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
    ui->comboBox_search_type->addItem("DFS");
    ui->comboBox_search_type->addItem("BFS");

    _default_directory = "C://";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_select_file_clicked()
{
    ui->pushButton_read->setText("Read");
    ui->groupBox_algorithems->setEnabled(false);
    //Start gui to choose graph
    filename = QFileDialog::getOpenFileName(
                this,
                tr("Select File"),
                _default_directory,
                "Text File (*.txt);;All Files (*.*)"
                );

    QDir directory = QFileInfo(filename).absoluteDir();

    cout << "Absolute path: " << directory.absolutePath().toUtf8().constData() << " and filename: " << filename.toUtf8().constData() << endl;

    _default_directory = directory.absolutePath().toUtf8().constData();

    //Set label in gui to chosen filename path
    ui->label_chosen_file->setText(QFileInfo(filename).fileName());
    ui->pushButton_read->setEnabled(true);
}

void MainWindow::on_pushButton_read_clicked()
{
    _graph = new Graph(
                ui->radioButton_weighted_yes->isChecked(),
                ui->radioButton_directed->isChecked(),
                ui->radioButton_adjacency_matrix->isChecked() ? Graph::ADJACENCY_MATRIX : Graph::EDGELIST,
                filename);

    ui->pushButton_read->setText("Done!");
    ui->pushButton_read->setEnabled(false);
    ui->spinBox_start_node->setMaximum(_graph->get_nodes().size()-1);
    QString max_node = "(Max. is ";
    max_node.append(QString::number(_graph->get_nodes().size()-1));
    max_node.append(")");
    ui->label_max_node->setText(max_node);


    ui->groupBox_algorithems->setEnabled(true);
}

void MainWindow::on_pushButton_count_components_clicked()
{
    Components components(_graph);
    components.perform_connected_compontents(Components::SearchInputType(ui->comboBox_search_type->currentIndex()));
    //_graph->reset_visited();
}

void MainWindow::on_pushButton_start_search_clicked()
{
    switch(ui->comboBox_search_type->currentIndex()){
    case Components::enum_DFS  :
    {
        DFS dfs(_graph);
        dfs.perform_recursive_DFS(ui->spinBox_start_node->value());
        //_graph->reset_visited();
        break;
    }
    case Components::enum_BFS  :
    {
        BFS bfs(_graph);
        bfs.perform_iterative_BFS(ui->spinBox_start_node->value());
        //_graph->reset_visited();
        break;
    }
    }
}

void MainWindow::on_pushButton_start_kruskal_clicked()
{
    Kruskal kruskal(_graph);
    kruskal.perform_kruskal();
}

void MainWindow::on_pushButton_start_prim_clicked()
{
    Prim prim(_graph);
    prim.perform_prim();
}

void MainWindow::on_pushButton_quit_clicked()
{
    QApplication::quit();
}
