#include "draw.h"
#include <QtGui>
#include <fstream>
#include <QWidget>
#include <iostream>



Draw::Draw(QWidget *parent) : QWidget(parent)
{
    q.setX(-100);
    q.setY(-100);
    enable_draw = true;
}

void Draw::loadPolygon(std::string &path)
{
    int id;
    double x, y;
    QPolygon polygon;


    //Load data from file
    std::ifstream coords(path);

    if (coords.is_open())
    {
        while(coords >> id >> x >> y)
        {
            if (id == 1)
            {
                if (polygon.isEmpty() == FALSE)
                {
                    polygons.push_back(polygon);
                }

                polygon.clear();
                polygon << QPoint(x, y);
            }
            else
                polygon << QPoint(x,y);
        }

        polygons.push_back(polygon);
        coords.close();
    }
    repaint();
}




void Draw::mousePressEvent(QMouseEvent *event)
{
    //Get cursor coordinates
    int x = event->pos().x();
    int y = event->pos().y();

    //Add new vertex
    if (enable_draw)
    {
        //Create new point
        QPoint p(x,y);

        //Add point to vector
        vertices.push_back(p);
    }

    //Modify coordinates of point Q
    else
    {
        q.setX(x);
        q.setY(y);
    }

    //Repaint screen
    repaint();
}

void Draw::paintEvent(QPaintEvent *event)
{

    // Create graphic object
    QPainter painter(this);
    painter.begin(this);

    //Draw point q
    painter.drawEllipse(q.x()-4, q.y()-4, 8, 8);

    //Improvements
    //for( QPoint vertex : vertices)
    //    pol.append(vertex)

    //Draw loaded polygons
    for(int i = 0; i < polygons.size(); i++)
    {
        QPolygon draw_pol = polygons[i];
        painter.drawPolygon(draw_pol);
    }

    //set color of highlighted polygon
    QBrush brush;
    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);
    QPainterPath path;

    QPolygon highlight;

    for(int i = 0; i < position.size(); i++)
    {
        if(position[i] == 1 || position[i] == -1 || position[i] == -2)
        {
            //Add selected polygon for highlighting
            highlight << polygons[i];
            path.addPolygon(highlight);
            painter.fillPath(path, brush);

            //Draw highlighted polygon
            painter.drawPolygon(highlight);

            highlight.clear();
        }
    }

    //Redraw point q
    painter.drawEllipse(q.x()-4, q.y()-4, 8, 8);

    painter.end();

}

void Draw::clear()
{
    //Clear and repaint
    vertices.clear();
    polygons.clear();
    position.clear();
    repaint();
}
