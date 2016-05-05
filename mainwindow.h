#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.h"
#include "dfs.h"
#include "bfs.h"
#include "components.h"
#include "kruskal.h"
#include "prim.h"
#include "nearest_neighbor.h"
#include "double_tree.h"
#include "branch_and_bound.h"

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

private:
    Ui::MainWindow *ui;

    QString filename;
    const char * _default_directory;

    Graph* _graph;

};

#endif // MAINWINDOW_H
