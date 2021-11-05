#include "widget.h"
#include "ui_widget.h"
#include "algorithms.h"
#include "load.h"
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


void Widget::on_pushButtonClear_clicked()
{
    ui->Canvas->clearDrawing();
}

void Widget::processPoints(std::vector<QPoint> &points)
{
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
    else if(ui->comboBox->currentIndex() == 1)
    {
        er = a.wallAverage(points);
    }

    //Longest Edge
    else if(ui->comboBox->currentIndex() == 2)
    {
        er = a.longestEdge(points);
    }

    //Weighted Bisector
    else if(ui->comboBox->currentIndex() == 3)
    {
        er = a.weightedBisector(points);
    }

    //Update enclosing rectangle
    ui->Canvas->setEr(er);

    //Repaint
    repaint();
}

//Building simplify
void Widget::on_pushButton_clicked()
{
    //Get points
    std::vector<QPoint> points = ui->Canvas->getPoints();
    std::vector<QPolygon> polygons = ui->Canvas->getPolygons();

    //Create enclosing rectangle
    Algorithms a;
    std::vector<QPoint> polygon_points;

    //Process drawn points
    if (points.size() > 1)
    processPoints(points);

    //Process loaded data
    if (polygons.size() > 0)
        for (QPolygon polygon : polygons)
        {
            polygon_points.clear();
            for (QPoint point : polygon)
                polygon_points.push_back(point);

            if (polygon_points.size() > 0)
            processPoints(polygon_points);
        }
    ui->Canvas->clearChs();
    ui->Canvas->clearErs();
}


void Widget::on_pushButtonLoad_clicked()
{
    //Open file dialog
    QString path(QFileDialog::getOpenFileName(this, tr("Select file"), "../", tr("CSV Files (*.csv)")));

    std::string path_ = path.toStdString();
    std::vector<QPolygon> polygon = Load::load_file(path_);
    ui->Canvas->drawPolygons(polygon);
}


void Widget::on_pushButtonClearData_clicked()
{
    ui->Canvas->clearAddedData();
}

