#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include "types.h"
#include "edge.h"

class Draw : public QWidget
{
    Q_OBJECT

private:
    TPolygon A, B, C;
    TEdges res;
    bool addA;
    std::vector<TPolygon> polygons;

public:
    explicit Draw(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void switchSource(){addA = !addA;}
    void drawPolygon(TPolygon &pol, QPainter &qp);
    TPolygon getA(){return A;}
    TPolygon getB(){return B;}
    std::vector<TPolygon> getPolygons(){return polygons;}
    void setEdges(TEdges &edg){res = edg;}
    void clear(){res.clear();}
    void clearAll(){A.clear(); B.clear(); C.clear(); res.clear(); polygons.clear();}
    void loadData(std::string &path, int height, int width);
    void drawPolygons(std::vector<QPolygon> &data);

signals:

public slots:
};

#endif // DRAW_H
