#include "draw.h"
#include <stdlib.h>

Draw::Draw(QWidget *parent) : QWidget(parent)
{
    //Initialize random number generator
    srand (time(NULL));
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

        //Convert to color
        int col = 255 - k * slope;
        QColor color(col, col, col);

        //Set pen and brush
        qp.setBrush(color);
        qp.setPen(color);

        //Create polygon for triangle
        QPolygon pol_exp;
        pol_exp.push_back(QPoint(p1.x(), p1.y()));
        pol_exp.push_back(QPoint(p2.x(), p2.y()));
        pol_exp.push_back(QPoint(p3.x(), p3.y()));

        //Draw triangle
        qp.drawPolygon(pol_exp);
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

        //Create polygon for triangle
        QPolygon pol_exp;
        pol_exp.push_back(QPoint(p1.x(), p1.y()));
        pol_exp.push_back(QPoint(p2.x(), p2.y()));
        pol_exp.push_back(QPoint(p3.x(), p3.y()));

        //Draw triangle
        qp.drawPolygon(pol_exp);
    }

    //Draw contour lines
    for (Edge c:contours)
    {
        //Get start point, get end point
        QPoint3D s_point = c.getStart();
        QPoint3D e_point = c.getEnd();

        //Color set
        QColor blue(0, 0, 255);

        //Set pen and brush
        qp.setBrush(blue);
        qp.setPen(blue);

        //Draw line
        qp.drawLine(s_point,e_point);
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
    triangles.clear();
    triangles_exp.clear();
    repaint();
}
