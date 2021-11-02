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
    bool enable_draw;
    std::vector<int> position;

public:
    explicit Draw(QWidget *parent = nullptr);
    void loadPolygon(std::string &path);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void clear();
    void changeStatus(){enable_draw = !enable_draw;}
    QPoint getPoint(){return q;}
    std::vector<QPolygon> getPolygons(){return polygons;}
    void setPosition(std::vector<int> pos){position = pos;}

signals:

public slots:
};

#endif // DRAW_H
