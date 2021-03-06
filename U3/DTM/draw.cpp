#include "draw.h"
#include <stdlib.h>
#include <fstream>
#include <QtGui>
#include "widget.h"
#include "algorithms.h"

Draw::Draw(QWidget *parent) : QWidget(parent)
{
    //Initialize random number generator
    srand (time(NULL));
}

void Draw::loadPoints(std::string &path, int height, int width)
{
    int id;
    double x, y, z;

    //Random numbers
    double x_max = 1.0e1;
    double y_max = 1.0e1;
    double x_min = 1.0e10;
    double y_min = 1.0e10;


    //Load data from file
    std::ifstream coords(path);

    if(coords.is_open())
    {
        while(coords >> id >> y >> x >> z)
        {
            //Set coordinates point by point
            QPoint3D point;
            point.setX(x);
            point.setY(y);
            point.setZ(z);
            points.push_back(point);

            //Set min-max values
            if(x > x_max)
                x_max = x;
            if(y > y_max)
                y_max = y;
            if(x < x_min)
                x_min = x;
            if(y < y_min)
                y_min = y;
        }
        coords.close();
    }

    //Transformation coefficient
    double kx = (width - 10)/fabs(x_max - x_min);
    double ky = (height - 10)/fabs(y_max - y_min);

    //Scale points to the size of Canvas
    for (int i = 0; i < points.size(); i++)
    {
        double px = points[i].x();
        double py = points[i].y();

        //Rewrite coords
        points[i].setX(-kx*(py - y_max));
        points[i].setY(ky*(px - x_min));
    }

    repaint();
}

void Draw::paintEvent(QPaintEvent *event)
{
    QPainter qp(this);
    qp.begin(this);

    //Draw points
    int r=4;
    QPolygon pol;

    for (int i=0; i<points.size(); i++)
    {
        qp.drawEllipse(points[i].x()-r,points[i].y()-r,2*r,2*r);
        pol.append(QPoint(points[i].x(), points[i].y()));
    }

    //Draw triangulation
    for(Edge e : dt)
    {
        //Get start point, get end point
        QPoint3D s_point = e.getStart();
        QPoint3D e_point = e.getEnd();

        //Draw line
        qp.setPen(QPen(Qt::cyan, 1));
        qp.drawLine(s_point,e_point);
    }

    //Draw slope
    double k = 255/M_PI;

    for (Triangle t:triangles)
    {
        //Get vertices of each triangle
        QPoint3D p1 = t.getP1();
        QPoint3D p2 = t.getP2();
        QPoint3D p3 = t.getP3();

        //Get slope
        double slope = t.getSlope();

        if (grayscale == TRUE)
        {
        //Convert to color
        int col = 255 - k * slope;
        QColor color(col, col, col);

        //Set pen and brush
        qp.setBrush(color);
        qp.setPen(color);
        }

        if (yelred == TRUE)
        {
        //Convert to color
        int col = 255 - k * slope;
        int colg = k * slope;
        QColor color(255, colg, col);

        //Set pen and brush
        qp.setBrush(color);
        qp.setPen(color);
        }

        //Create polygon for triangle
        QPolygon pol_slope;
        pol_slope.push_back(QPoint(p1.x(), p1.y()));
        pol_slope.push_back(QPoint(p2.x(), p2.y()));
        pol_slope.push_back(QPoint(p3.x(), p3.y()));

        //Draw triangle
        qp.drawPolygon(pol_slope);
    }

    //Draw exposition
    for (Triangle t:triangles_exp)
    {
        //Get vertices of each triangle
        QPoint3D p1 = t.getP1();
        QPoint3D p2 = t.getP2();
        QPoint3D p3 = t.getP3();

        //Get exposition
        double exp = t.getExposition();

        if (kmcol == TRUE)
        {
            if (exp >= M_PI/8 && exp < M_PI/4+M_PI/8)
            {
                QColor color(128, 255, 0); //Light green
                //Set pen and brush
                qp.setBrush(color);
                qp.setPen(color);
            }
            else if (exp >= M_PI/4+M_PI/8 && exp < M_PI/2+M_PI/8)
            {
                QColor color(0, 128, 128); //Dark green
                //Set pen and brush
                qp.setBrush(color);
                qp.setPen(color);
            }
            else if (exp >= M_PI/2+M_PI/8 && exp < 3*M_PI/4+M_PI/8)
            {
                QColor color(0, 0, 100); //Blue
                //Set pen and brush
                qp.setBrush(color);
                qp.setPen(color);
            }
            else if ((exp >= 3*M_PI/4+M_PI/8 && exp <= M_PI) || (exp >= -M_PI && exp < -3*M_PI/4-M_PI/8 ))
            {
                QColor color(80, 31, 200); //Dark blue
                //Set pen and brush
                qp.setBrush(color);
                qp.setPen(color);
            }

            else if (exp >= -3*M_PI/4-M_PI/8 && exp < -M_PI/2-M_PI/8)
            {
                QColor color(128, 0, 128); //Purple
                //Set pen and brush
                qp.setBrush(color);
                qp.setPen(color);
            }
            else if (exp >= -M_PI/2-M_PI/8 && exp < -M_PI/4-M_PI/8)
            {
                QColor color(255, 0, 0); //Red
                //Set pen and brush
                qp.setBrush(color);
                qp.setPen(color);
            }
            else if (exp >= -M_PI/4-M_PI/8 && exp < -M_PI/8)
            {
                QColor color(255, 128, 0); //Orange
                //Set pen and brush
                qp.setBrush(color);
                qp.setPen(color);
            }
            else if (exp >= -M_PI/8 && exp < M_PI/8)
            {
                QColor color(255, 255, 0); //Yellow
                //Set pen and brush
                qp.setBrush(color);
                qp.setPen(color);
            }
        }

        if (esricol == TRUE)
        {
            if (exp >= M_PI/8 && exp < M_PI/4+M_PI/8)
            {
                QColor color(0, 255, 0); //Southeast
                //Set pen and brush
                qp.setBrush(color);
                qp.setPen(color);
            }
            else if (exp >= M_PI/4+M_PI/8 && exp < M_PI/2+M_PI/8)
            {
                QColor color(0, 255, 255); //South
                //Set pen and brush
                qp.setBrush(color);
                qp.setPen(color);
            }
            else if (exp >= M_PI/2+M_PI/8 && exp < 3*M_PI/4+M_PI/8)
            {
                QColor color(0, 166, 255); //Southwest
                //Set pen and brush
                qp.setBrush(color);
                qp.setPen(color);
            }
            else if ((exp >= 3*M_PI/4+M_PI/8 && exp <= M_PI) || (exp >= -M_PI && exp < -3*M_PI/4-M_PI/8 ))
            {
                QColor color(0, 0, 255); //West
                //Set pen and brush
                qp.setBrush(color);
                qp.setPen(color);
            }

            else if (exp >= -3*M_PI/4-M_PI/8 && exp < -M_PI/2-M_PI/8)
            {
                QColor color(255, 0, 255); //Northwest
                //Set pen and brush
                qp.setBrush(color);
                qp.setPen(color);
            }
            else if (exp >= -M_PI/2-M_PI/8 && exp < -M_PI/4-M_PI/8)
            {
                QColor color(255, 0, 0); //North
                //Set pen and brush
                qp.setBrush(color);
                qp.setPen(color);
            }
            else if (exp >= -M_PI/4-M_PI/8 && exp < -M_PI/8)
            {
                QColor color(255, 166, 0); //Northeast
                //Set pen and brush
                qp.setBrush(color);
                qp.setPen(color);
            }
            else if (exp >= -M_PI/8 && exp < M_PI/8)
            {
                QColor color(255, 255, 0); //East
                //Set pen and brush
                qp.setBrush(color);
                qp.setPen(color);
            }
        }

        //Create polygon for triangle
        QPolygon pol_exp;
        pol_exp.push_back(QPoint(p1.x(), p1.y()));
        pol_exp.push_back(QPoint(p2.x(), p2.y()));
        pol_exp.push_back(QPoint(p3.x(), p3.y()));

        //Draw triangle
        qp.drawPolygon(pol_exp);
    }

    //Draw hypsometry - not working
    for (Edge h:main_contours)
    {
        QPoint3D p1 = h.getStart();
        QPoint3D p2 = h.getEnd();

        if (p1.getZ() > 0 && p1.getZ() < 600)
        {
        QColor color(255, 0, 0);
        //Set pen and brush
        qp.setBrush(color);
        qp.setPen(color);
        }

        QPolygon pol_hyps;
        pol_hyps.push_back(QPoint(p1.x(), p1.y()));
        pol_hyps.push_back(QPoint(p2.x(), p2.y()));

        //Draw polygon
        qp.drawPolygon(pol_hyps);
    }

    //Draw contour lines
       for (Edge c:contours)
       {
           //Get start point, get end point
           QPoint3D s_point = c.getStart();
           QPoint3D e_point = c.getEnd();

           //Color set
           QColor col(139, 69, 19);

           //Set pen and brush
           qp.setBrush(col);
           qp.setPen(col);

           //Draw line
           qp.drawLine(s_point,e_point);
        }

       //Draw main contour lines
       for (Edge c:main_contours)
       {
           //Get start point, get end point
           QPoint3D s_point = c.getStart();
           QPoint3D e_point = c.getEnd();

           //Color set
           QColor col(139, 69, 19);
           QPen p (col, 2);

           //Set pen and brush
           qp.setBrush(col);
           qp.setPen(p);

           //Draw line
           qp.drawLine(s_point,e_point);
        }

       //Draw main contours label
       for (Edge mcl : main_contours_label)
       {
          //Start and end point of the contour edge
          QPoint3D sl_point = mcl.getStart();
          QPoint3D el_point = mcl.getEnd();

          //Get label coordintes
          QPoint3D label_point( (sl_point.x()+el_point.x())/2, (sl_point.y()+el_point.y())/2);

          //Draw Z coordinate
          QString z = QString::number(sl_point.getZ());
          qp.drawText(label_point, z);
       }

    //Stop drawing
    qp.end();
}

void Draw::mousePressEvent(QMouseEvent *event)
{
    //Get coordinates
    int x = event->pos().x();
    int y = event->pos().y();
    int z = rand() % 1000;

    //Create point
    QPoint3D p(x, y, z);

    //Add point to the vector
    points.push_back(p);

    //Update screen
    repaint();
}

void Draw::clear()
{
    points.clear();
    repaint();
}

void Draw::clearDT()
{
    dt.clear();
    repaint();
}

void Draw::clearAll()
{
    points.clear();
    dt.clear();
    contours.clear();
    main_contours.clear();
    main_contours_label.clear();
    triangles.clear();
    triangles_exp.clear();
    repaint();
}
