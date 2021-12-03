#include "widget.h"
#include "ui_widget.h"
#include "algorithms.h"
#include "edge.h"
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    zmin = 100.0;
    zmax = 1000.0;
    dz = 100.0;

    ui->lineEdit->setText(QString::number(zmin));
    ui->lineEdit_2->setText(QString::number(zmax));
    ui->lineEdit_3->setText(QString::number(dz));
}


Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_2_clicked()
{
    //Clear all
    ui->Canvas->clear();
    repaint();
}

void Widget::on_pushButton_clicked()
{
    //Get points
    std::vector<QPoint3D> points = ui->Canvas->getPoints();

    //Create DT
    Algorithms a;
    std::vector<Edge> dt = a.dT(points);

    //Set DT
    ui->Canvas->setDT(dt);

    repaint();

}

void Widget::on_pushButton_cleardt_clicked()
{
    //Clear DT
    ui->Canvas->clearDT();
    repaint();
}

void Widget::on_lineEdit_editingFinished()
{
    zmin = ui->lineEdit->text().toDouble();
}

void Widget::on_lineEdit_2_editingFinished()
{
    zmax = ui->lineEdit_2->text().toDouble();
}

void Widget::on_lineEdit_3_editingFinished()
{
    dz = ui->lineEdit_3->text().toDouble();
}

void Widget::on_pushButton_3_clicked()
{
    //Create contours
    std::vector<Edge> dt = ui->Canvas->getDT();

    //Is the triangulation not empty?
    if (dt.size() > 0)
    {
        Algorithms a;
        //Create contours
        std::vector<Edge> contours = a.getContourLines(dt, zmin, zmax, dz);

        //Create main contours
        std::vector<Edge> main_contours = a.getContourLines(dt, zmin, zmax, dz*5);

        //Set contours
        ui->Canvas->setContours(contours);
        ui->Canvas->setMainContours(main_contours);

        repaint();
    }

}


void Widget::on_pushButton_4_clicked()
{
    //Draw slope
    std::vector<Edge> dt = ui->Canvas->getDT();

    //Select color palette
    bool grayscale, yelred;

    if (ui->comboBox_slope->currentIndex() == 0)
    {
        grayscale = TRUE;
        yelred = FALSE;
    }
    else if (ui->comboBox_slope->currentIndex() == 1)
    {
        grayscale = FALSE;
        yelred = TRUE;
    }

    //Set color palette
    ui->Canvas->setGrayscale(grayscale);
    ui->Canvas->setYelRed(yelred);

    //Is the triangulation not empty?
    if (dt.size() > 0)
    {
        Algorithms a;
        //Analyze DTM
        std::vector<Triangle> triangles = a.analyzeDTM(dt);

        //Set triangles
        ui->Canvas->setTriangles(triangles);

        //Redraw exposition
        ui->Canvas->clearExposition();
        ui->Canvas->setDT(dt);
        repaint();
    }
}

void Widget::on_pushButton_ClearAll_clicked()
{
    //Clear all data
    ui->Canvas->clearAll();
    repaint();
}


void Widget::on_pushButton_Exposition_clicked()
{
    //Draw exposition
    std::vector<Edge> dt = ui->Canvas->getDT();

    //Select color palette
    bool kmcol, esricol;

    if (ui->comboBox_exp->currentIndex() == 0)
    {
        kmcol = TRUE;
        esricol = FALSE;
    }
    else if (ui->comboBox_exp->currentIndex() == 1)
    {
        kmcol = FALSE;
        esricol = TRUE;
    }

    //Set color palette
    ui->Canvas->setKMCol(kmcol);
    ui->Canvas->setEsriCol(esricol);

    //Is the triangulation not empty?
    if (dt.size() > 0)
    {
        Algorithms a;
        //Analyze DTM
        std::vector<Triangle> triangles_exp = a.analyzeDTM(dt);

        //Set triangles
        ui->Canvas->setTrianglesExp(triangles_exp);

        //Redraw slope
        ui->Canvas->clearSlope();
        repaint();
    }
}



void Widget::on_pushButton_LoadPoints_clicked()
{
    QString path(QFileDialog::getOpenFileName(this, tr("Select file with points"), "../", tr("Text Files (*.txt)")));
    std::string path_ = path.toStdString();
    ui->Canvas->loadPoints(path_);
}


void Widget::on_pushButton_mcLabels_clicked()
{
    std::vector<Edge> dt = ui->Canvas->getDT();
    //Is the triangulation not empty?
    if (dt.size() > 0)
    {
        Algorithms a;
        // Load main contours edges
        std::vector<Edge> main_contours_label = ui->Canvas->getMainContours();

        //Set main contours label
        ui->Canvas->setMainContoursLabel(main_contours_label);

        repaint();
    }
}


void Widget::on_pushButton_Generate_clicked()
{
    //Number of points on the line
    n = ui->lineEdit_NumberOfPoints->text().toDouble();

    //Size of the canvas
    QSize size = ui->Canvas->size();
    int height = size.height();
    int width = size.width();

    Algorithms a;
    std::vector<QPoint3D> points = a.generateRandomPoints(n, height, width);

    if (ui->comboBox->currentIndex() == 1)
        points = a.generatePile(points);
    else if (ui->comboBox->currentIndex() == 2)
        points = a.generateSaddle(points);
    else if (ui->comboBox->currentIndex() == 3)
        points = a.generateRidge(points);





    ui->Canvas->setPoints(points);
    repaint();
}

