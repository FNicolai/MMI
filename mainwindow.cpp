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

    ui->groupBox_direction->setEnabled(false);
    ui->groupBox_matrixtyp->setEnabled(false);
    ui->groupBox_weighted->setEnabled(false);
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

    ui->groupBox_direction->setEnabled(true);
    ui->groupBox_matrixtyp->setEnabled(true);
    ui->groupBox_weighted->setEnabled(true);

    ui->pushButton_read->setEnabled(true);
}

void MainWindow::on_pushButton_read_clicked()
{
    Graph::GraphInputType input_type;
    if(ui->radioButton_adjacency_matrix->isChecked()){
        input_type = Graph::ADJACENCY_MATRIX;
    }else if(ui->radioButton_edgelist->isChecked()){
        input_type = Graph::EDGELIST;
    }else if(ui->radioButton_balance_given->isChecked()){
        input_type = Graph::BALANCE;
    }
    _graph = new Graph(
                ui->radioButton_weighted_yes->isChecked(),
                ui->radioButton_directed->isChecked(),
                input_type,
                filename);

    ui->pushButton_read->setText("Done!");
    ui->pushButton_read->setEnabled(false);
    ui->spinBox_start_node->setMaximum(_graph->get_nodes().size()-1);
    ui->spinBox_end_node->setMaximum(_graph->get_nodes().size()-1);
    QString max_node = "(Max. is ";
    max_node.append(QString::number(_graph->get_nodes().size()-1));
    max_node.append(")");
    ui->label_max_node->setText(max_node);


    ui->groupBox_algorithems->setEnabled(true);
}

void MainWindow::on_pushButton_count_components_clicked()
{
    Components components(_graph, _debug);
    components.perform_connected_compontents(Components::SearchInputType(ui->comboBox_search_type->currentIndex()));
    //_graph->reset_visited();
}

void MainWindow::on_pushButton_start_search_clicked()
{
    switch(ui->comboBox_search_type->currentIndex()){
        case Components::enum_DFS  :
        {
            DFS dfs(_graph, _debug);
            dfs.perform_recursive_DFS(ui->spinBox_start_node->value());
            //_graph->reset_visited();
            break;
        }
        case Components::enum_BFS  :
        {
            BFS bfs(_graph, _debug);
            bfs.perform_iterative_BFS(ui->spinBox_start_node->value());
            //_graph->reset_visited();
            break;
        }
    }
}

void MainWindow::on_pushButton_start_kruskal_clicked()
{
    Kruskal kruskal(_graph, _debug);
    kruskal.perform_kruskal(ui->spinBox_start_node->value());
}

void MainWindow::on_pushButton_start_prim_clicked()
{
    Prim prim(_graph, _debug);
    prim.perform_prim(ui->spinBox_start_node->value());
}

void MainWindow::on_pushButton_quit_clicked()
{
    QApplication::quit();
}

void MainWindow::on_pushButton_neares_neighbor_clicked()
{
    Nearest_Neighbor nearest_neighbor(_graph, _debug);
    nearest_neighbor.perform_nearest_neighbor(ui->spinBox_start_node->value());
}

void MainWindow::on_pushButton_start_double_tree_clicked()
{
    Double_Tree double_tree (_graph, _debug);
    double_tree.perform_double_tree(ui->spinBox_start_node->value());
}

void MainWindow::on_pushButton_start_branch_and_bound_clicked()
{
    Branch_and_Bound branch_and_bound(_graph, _debug);
    branch_and_bound.perform_branch_and_bound(ui->spinBox_start_node->value());
}

void MainWindow::on_pushButton_start_tsp_bruteforce_clicked()
{
    TSP_Bruteforce tsp_bruteforce(_graph, _debug);
    tsp_bruteforce.perform_tsp_bruteforce(ui->spinBox_start_node->value());
}

void MainWindow::on_pushButton_start_bellman_ford_clicked()
{
    Bellman_Ford bellman_ford(_graph, _debug);
    bellman_ford.perform_bellman_ford(ui->spinBox_start_node->value());
}

void MainWindow::on_radioButton_directed_clicked()
{
    ui->groupBox_algorithems->setEnabled(false);
    ui->pushButton_read->setText("Read");
    ui->pushButton_read->setEnabled(true);
}

void MainWindow::on_radioButton_undirected_clicked()
{
    ui->groupBox_algorithems->setEnabled(false);
    ui->pushButton_read->setText("Read");
    ui->pushButton_read->setEnabled(true);
}

void MainWindow::on_pushButton_start_dijkstra_clicked()
{
    Dijkstra dijkstra(_graph, _debug);
    if(ui->checkBox_use_end_node->isChecked())
        dijkstra.perform_dijkstra(ui->spinBox_start_node->value(),ui->spinBox_end_node->value());
    else
        dijkstra.perform_dijkstra(ui->spinBox_start_node->value(),INFINITY);
}

void MainWindow::on_checkBox_use_end_node_clicked()
{
    if(ui->checkBox_use_end_node->isChecked()){
        ui->spinBox_end_node->setEnabled(true);
    }else{
        ui->spinBox_end_node->setEnabled(false);
    }
}
void MainWindow::on_radioButton_debug_on_clicked()
{
    _debug = true;
}

void MainWindow::on_radioButton_debug_off_clicked()
{
    _debug = false;
}

void MainWindow::on_pushButton_start_edmonds_karp_clicked()
{
    Edmonds_Karp edmonds_karp(_graph,_debug);
    if(ui->spinBox_end_node->isEnabled()){
        edmonds_karp.perform_edmonds_karp(ui->spinBox_start_node->value(), ui->spinBox_end_node->value());
    }else{
        QMessageBox messageBox;
        messageBox.setText("Please set End-Node");
        messageBox.exec();
    }
}

void MainWindow::on_pushButton_start_cycle_canceling_clicked()
{
    Cycle_Canceling cycle_canceling(_graph,_debug);
    cycle_canceling.perform_cycle_canceling();
}

void MainWindow::on_pushButton_start_successive_shortest_path_clicked()
{
    Successive_Shortest_Path successive_shortest_path(_graph,_debug);
    successive_shortest_path.perform_successive_shortest_path();
}
