#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "graph.h"
#include "dfs.h"
#include "bfs.h"
#include "components.h"
#include "kruskal.h"
#include "prim.h"
#include "nearest_neighbor.h"
#include "double_tree.h"
#include "branch_and_bound.h"
#include "tsp_bruteforce.h"
#include "bellman_ford.h"
#include "dijkstra.h"
#include "edmonds_karp.h"
#include "cycle_canceling.h"
#include "successive_shortest_path.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_select_file_clicked();

    void on_pushButton_read_clicked();

    void on_pushButton_count_components_clicked();

    void on_pushButton_start_search_clicked();

    void on_pushButton_start_kruskal_clicked();

    void on_pushButton_quit_clicked();

    void on_pushButton_start_prim_clicked();

    void on_pushButton_neares_neighbor_clicked();

    void on_pushButton_start_double_tree_clicked();

    void on_pushButton_start_branch_and_bound_clicked();

    void on_pushButton_start_tsp_bruteforce_clicked();

    void on_pushButton_start_bellman_ford_clicked();

    void on_pushButton_start_dijkstra_clicked();

    void on_checkBox_use_end_node_clicked();

    void on_radioButton_directed_clicked();

    void on_radioButton_undirected_clicked();

    void on_radioButton_debug_on_clicked();

    void on_radioButton_debug_off_clicked();

    void on_pushButton_start_edmonds_karp_clicked();

    void on_pushButton_start_cycle_canceling_clicked();

    void on_pushButton_start_successive_shortest_path_clicked();

private:
    Ui::MainWindow *ui;

    QString filename;
    const char * _default_directory;

    Graph* _graph;
    bool _debug;

};

#endif // MAINWINDOW_H
