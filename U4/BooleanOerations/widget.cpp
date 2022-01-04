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
    TPolygon A = ui->Canvas->getA();
    TPolygon B = ui->Canvas->getB();
    TBooleanOperation op = (TBooleanOperation)ui->comboBox->currentIndex();

    //Create overlay of polygons
    Algorithms a;
    TEdges res = a.createOverlay(A, B, op);

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
