#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.h"
#include "dfs.h"
#include "bfs.h"
#include "components.h"

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

    void on_pushButton_cancel_clicked();

    void on_pushButton_start_bfs_clicked();

    void on_pushButton_start_dfs_clicked();

    void on_pushButton_count_components_clicked();

private:
    Ui::MainWindow *ui;

    Graph* _graph;

};

#endif // MAINWINDOW_H
