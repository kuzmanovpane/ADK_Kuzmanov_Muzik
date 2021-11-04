#include "widget.h"
#include "ui_widget.h"
#include "algorithms.h"

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


void Widget::on_pushButton_2_clicked()
{
    ui->Canvas->clear();
}

//Building simplify
void Widget::on_pushButton_clicked()
{
    //Get points
    std::vector<QPoint> points = ui->Canvas->getPoints();

    //Create enclosing rectangle
    Algorithms a;
    QPolygon er;

    //Minimum area enclosing rectangle
    if (ui->comboBox->currentIndex() == 0)
    {
        QPolygon ch = a.cHull(points);
        er = a.minAreaEnclosingRectangle(points);
        ui->Canvas->setCh(ch);
    }

    //Wall Average
    if(ui->comboBox->currentIndex() == 1)
        er = a.wallAverage(points);

    //Longest Edge
    if(ui->comboBox->currentIndex() == 2)
        er = a.longestEdge(points);

    //Weighted Bisector
    if(ui->comboBox->currentIndex() == 3)
        er = a.weightedBisector(points);


    //Update enclosing rectangle
    ui->Canvas->setEr(er);

    //Repaint
    repaint();

}

