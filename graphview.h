#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QMainWindow>

namespace Ui {
class GraphView;
}

class GraphView : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphView(QWidget *parent = 0);
    ~GraphView();

private slots:
    void on_pushButton_Select_File_clicked();

    void on_pushButton_Read_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::GraphView *ui;
};

#endif // MAINWINDOW_H
