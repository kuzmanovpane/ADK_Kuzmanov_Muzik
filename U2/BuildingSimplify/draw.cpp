#include "draw.h"
#include <QtGui>

Draw::Draw(QWidget *parent) : QWidget(parent)
{

}

void Draw::paintEvent(QPaintEvent *event)
{
    QPainter qp(this);
    qp.begin(this);

    //Draw points
    int r = 4;
    QPolygon pol;

    //Draw polygons
    for (QPolygon polygon : Draw::polygons)
    {
        qp.setBrush(Qt::yellow);
        qp.drawPolygon(polygon);
    }

    qp.setBrush(Qt::NoBrush);

    for (int i=0; i<points.size(); i++)
    {
        qp.drawEllipse(points[i].x()-r, points[i].y()-r, 2*r, 2*r);
        pol.append(points[i]);
    }

    //Draw polygon
    qp.setBrush(Qt::yellow);
    qp.drawPolygon(pol);

    //Draw convex hull
    qp.setBrush(Qt::NoBrush);
    qp.setPen(Qt::red);
    if (chs.size() > 0)
        for (QPolygon chull : chs)
            qp.drawPolygon(chull);


    //Draw enclosing rectangle
    qp.setBrush(Qt::NoBrush);
    qp.setPen(Qt::blue);
    if (ers.size() > 0)
        for (QPolygon enrect : ers)
            qp.drawPolygon(enrect);

    qp.end();
}

void Draw::mousePressEvent(QMouseEvent *event)
{
    //Get coordinates
    int x = event->pos().x();
    int y = event->pos().y();

    //Create points
    QPoint p(x, y);
    //Add point to the vector
    points.push_back(p);

    //Update screem
    repaint();
}

void Draw::clearDrawing()
{
    points.clear();
    chs.clear();
    ers.clear();

    repaint();
}

void Draw::clearAddedData()
{
    polygons.clear();
    chs.clear();
    ers.clear();

    repaint();
}
void Draw::drawPolygons(std::vector<QPolygon> &data)
{
    Draw::polygons.clear();
    for (QPolygon data_ : data)
        Draw::polygons.push_back(data_);

    repaint();
}
