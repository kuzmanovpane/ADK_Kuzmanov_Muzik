#include "widget.h"
#include "ui_widget.h"
#include "algorithms.h"
#include <QFileDialog>
#include "draw.h"


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
    ui->Canvas->clear();
}

void Widget::on_pushButton_clicked()
{
    ui->Canvas->changeStatus();
}

void Widget::on_pushButtonAnalyze_clicked()
{
    //Analyze position of the point and vertex
    QPoint q = ui->Canvas->getPoint();
    std::vector<QPolygon> polygons = ui->Canvas->getPolygons();
    std::vector<QPoint> pol;


    for (int i = 0; i < polygons.size(); i++)
    {
        QPolygon polygon = polygons[i];

        for (int j = 0; j < polygon.size(); j++)
        {
            pol.push_back(polygon[j]);
        }
    }


    //Get position
    Algorithms a;
    int pos = 10; //random number

    //Ray Crossing algorithm
   if (ui->comboBox->currentIndex() == 0)
    {
       pos = a.getPositionRayCrossing(q, pol);
    }

   //Winding number algorithm
    else
    {
       pos = a.getPositionWinding(q, pol);
    }
    pol.clear();


    //Print results
    if (pos == 1)
    {
        ui->label->setText("Point is inside");

    }
    else if (pos == 0)
    {
        ui->label->setText("Point is outside");
    }
    else if (pos == -1)
    {
        ui->label->setText("Point is on the border");
    }
    else
    {
        ui->label->setText("Error: No polygons");
    }

}

void Widget::on_pushButtonLoad_clicked()
{
    QString path(QFileDialog::getOpenFileName(this, tr("Select file"), "../", tr("Text Files (*.txt)")));
    std::string path_ = path.toStdString();
    ui->Canvas->loadPolygon(path_);
}

