#include "graphview.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

GraphView::GraphView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphView)
{
    ui->setupUi(this);
}

GraphView::~GraphView()
{
    delete ui;
}

void GraphView::on_pushButton_select_file_clicked()
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

void GraphView::on_pushButton_read_clicked()
{
    /*
     * TODO
     * Read graph depending on matrixtype
     */

    if(ui->radioButton_adjacency_matrix->isChecked()){

    }else{
        //Only to options -> definitly Edgelist now
    }
}

void GraphView::on_pushButton_cancel_clicked()
{
    QApplication::quit();
}
