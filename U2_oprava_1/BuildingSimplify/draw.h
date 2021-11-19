#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <vector>
#include <QtGui>

class Draw : public QWidget
{
    Q_OBJECT

private:
    std::vector<QPoint> points;
    QPolygon ch, er;
    std::vector<QPolygon> polygons, chs, ers;

public:
    explicit Draw(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void clearAddedData();
    void clearDrawing();
    std::vector<QPoint> getPoints() {return points;}
    std::vector<QPolygon> getPolygons(){return polygons;}
    void setCh(QPolygon &ch_) {chs.push_back(ch_);}
    void setEr(QPolygon &er_) {ers.push_back(er_);}
    void clearChs(){chs.clear();}
    void clearErs(){ers.clear();}
    void drawPolygons(std::vector<QPolygon> &data);

signals:

public slots:
};

#endif // DRAW_H
