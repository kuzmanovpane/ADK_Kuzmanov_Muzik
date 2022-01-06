#include "draw.h"
#include <fstream>

Draw::Draw(QWidget *parent) : QWidget(parent)
{
    addA = true;
}


void Draw::loadData(std::string &path, int height, int width)
{
    A.clear();
    B.clear();
    res.clear();
    int id;
    double x, y;
    QPointFBO point;

    //Random numbers
    double x_max = 1.0e1;
    double y_max = 1.0e1;
    double x_min = 1.0e10;
    double y_min = 1.0e10;


    //Load data from file
    std::ifstream coords(path);

    if (coords.is_open())
    {
        while(coords >> id >> y >> x)
        {
            //Set min-max values
            if(x > x_max)
                x_max = x;
            if(y > y_max)
                y_max = y;
            if(x < x_min)
                x_min = x;
            if(y < y_min)
                y_min = y;

            if (id == 1)
            {
                point.setX(x);
                point.setY(y);
                A.push_back(point);
            }
            if (id == 2)
            {
                point.setX(x);
                point.setY(y);
                B.push_back(point);
            }
        }
        coords.close();
    }

    //Transformation coefficient
    double dy = fabs(y_max-y_min);
    double dx = fabs(x_max-x_min);

    //Find longer minmax axis difference
    double k;
    if (dy > dx)
        k = width/dy;
    else
        k = height/dx;

    //Scale points to the size of Canvas
    for (int i = 0; i < A.size(); i++)
    {
        double pxa = A[i].x();
        double pya = A[i].y();

    //Rewrite coords
    A[i].setX(-k*(pya - y_max));
    A[i].setY(k*(pxa - x_min));
    }

    for (int j = 0; j < B.size(); j++)
    {
        double pxb = B[j].x();
        double pyb = B[j].y();

    //Rewrite coords
    B[j].setX(-k*(pyb - y_max));
    B[j].setY(k*(pxb - x_min));
    }
    repaint();
}


void Draw::paintEvent(QPaintEvent *event)
{
    QPainter qp(this);
    qp.begin(this);

    //Draw polygons
    //Polygon A
    qp.setPen(Qt::blue);
    drawPolygon(A, qp);

    //Polygon B
    qp.setPen(Qt::green);
    drawPolygon(B, qp);

    //Draw edges
    QPen pen_e(Qt::red, 3);
    qp.setPen(pen_e);
    for(Edge e:res)
        qp.drawLine(e.getStart(), e.getEnd());

    qp.end();
}

void Draw::mousePressEvent(QMouseEvent *event)
{
    //Get coordinates
    int x = event->pos().x();
    int y = event->pos().y();

    //Create point
    QPointFBO p(x,y);

    //Add point to A, B
    if (addA)
        A.push_back(p);

    else
        B.push_back(p);


    //Update screen
    repaint();
}

void Draw::drawPolygon(TPolygon &polygon, QPainter &qp)
{
    //Draw polygon on canvas
    int r=4;
    QPolygon pol;

    //Convert polygon to QPolygon
    for (int i=0; i<polygon.size(); i++)
    {
       qp.drawEllipse(polygon[i].x()-r,polygon[i].y()-r,2*r,2*r);
       pol.append(QPoint(polygon[i].x(),polygon[i].y()));
    }

    //Draw polygon
    qp.drawPolygon(pol);
}

