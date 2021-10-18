#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <vector>
#include <QtGui>

class Draw : public QWidget
{
    Q_OBJECT

private:
    std::vector<QPoint> vertices;
    QPoint q;
    std::vector<QPolygon> polygons;
    bool add_vertex;

public:
    explicit Draw(QWidget *parent = nullptr);
    void loadPolygon(std::string &path);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void clear();
    void changeStatus(){add_vertex = !add_vertex;}
    QPoint getPoint(){return q;}
    std::vector<QPolygon> getPolygons(){return polygons;}
  //  std::vector<QPoint> getPolygon(){return vertices;}

signals:

public slots:
};

#endif // DRAW_H
