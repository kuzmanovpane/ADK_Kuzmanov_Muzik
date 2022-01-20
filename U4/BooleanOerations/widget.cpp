#include "widget.h"
#include "ui_widget.h"
#include "algorithms.h"
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

}


Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    ui->Canvas->switchSource();
}


void Widget::on_pushButton_2_clicked()
{
    //Get polygons and Boolean operation
    std::vector<TPolygon> polygons = ui->Canvas->getPolygons();
    TBooleanOperation op = (TBooleanOperation)ui->comboBox->currentIndex();

    //Create overlay of polygons
    Algorithms a;

    int n = polygons.size();
    TEdges res, res_temp;

    for (int i = 0; i < n-1; i++)
    {
        TPolygon A = polygons[i];
        for (int j = 1; j < n; j++)
        {
            TPolygon B = polygons[j];
            TEdges res_temp = a.createOverlay(A, B, op);
            for (int k = 0; k < res_temp.size(); k++)
            {
                res.push_back(res_temp[k]);
            }
        }
    }

    //Set result
    ui->Canvas->setEdges(res);

    repaint();

}


void Widget::on_pushButton_3_clicked()
{
    //Clear results
    ui->Canvas->clear();
    repaint();
}


void Widget::on_pushButton_4_clicked()
{
    //Clear all
    ui->Canvas->clearAll();
    repaint();
}

void Widget::on_pushButton_Import_clicked()
{
    //Size of the canvas
    QSize size = ui->Canvas->size();
    int height = size.height();
    int width = size.width();

    QString path(QFileDialog::getOpenFileName(this, tr("Select file with polygons"), "../", tr("Text Files (*.txt)")));
    std::string path_ = path.toStdString();
    ui->Canvas->loadData(path_, height, width);
}

