#include "draw.h"
#include <fstream>

Draw::Draw(QWidget *parent) : QWidget(parent)
{
    addA = true;
}

void Draw::loadData(std::string &path)
{
    A.clear();
    B.clear();
    res.clear();
    int id;
    double x, y;
    QPointFBO point;


    //Load data from file
    std::ifstream coords(path);

    if (coords.is_open())
    {
        while(coords >> id >> x >> y)
        {
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

