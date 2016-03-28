#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bfs.h"

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

private:
    Ui::MainWindow *ui;

    Graph* _graph;
    BFS* _bfs;


};

#endif // MAINWINDOW_H
