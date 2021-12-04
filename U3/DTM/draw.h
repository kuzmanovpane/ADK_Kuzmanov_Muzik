#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include "qpoint3d.h"
#include <QtGui>
#include "edge.h"
#include "triangle.h"


class Draw : public QWidget
{
    Q_OBJECT
private:
    std::vector<QPoint3D> points;
    std::vector<Edge> dt;
    std::vector<Edge> contours, main_contours, main_contours_label;
    std::vector<Triangle> triangles, triangles_exp;
    std::vector<QPolygon> pol_hyps;
    bool grayscale, yelred, kmcol, esricol;

public:
    explicit Draw(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void clear();
    void setPoints(std::vector<QPoint3D> &points_){points = points_;}
    std::vector<QPoint3D> getPoints(){return points;}
    void setDT(std::vector<Edge> &dt_){dt = dt_;}
    std::vector<Edge> getDT(){return dt;}
    void setContours(std::vector<Edge> &contours_){contours = contours_;}
    std::vector<Edge> getContours(){return contours;}
    std::vector<Triangle> getTriangles(){return triangles;}
    void setTriangles(std::vector<Triangle> &triangles_){triangles = triangles_;}
    void clearDT();
    void clearAll();
    std::vector<Triangle> getTrianglesExp(){return triangles_exp;}
    void setTrianglesExp(std::vector<Triangle> &triangles_exp_){triangles_exp = triangles_exp_;}
    void clearSlope(){triangles.clear();}
    void clearExposition(){triangles_exp.clear();}
    void loadPoints(std::string &path, int height, int width);
    void setMainContours(std::vector<Edge> &main_contours_){main_contours = main_contours_;}
    std::vector<Edge> getMainContours(){return main_contours;}
    void setMainContoursLabel(std::vector<Edge> &main_contours_label_){main_contours_label = main_contours_label_;}
    std::vector<Edge> getMainContoursLabel(){return main_contours_label;}
    void setGrayscale(bool &grayscale_){grayscale = grayscale_;}
    void setYelRed(bool &yelred_){yelred = yelred_;}
    void setKMCol(bool &kmcol_){kmcol = kmcol_;}
    void setEsriCol(bool &esricol_){esricol = esricol_;}
    void setHypsometry(std::vector<QPolygon> &pol_hyps_){pol_hyps = pol_hyps_;}
    std::vector<QPolygon> getHypsometry(){return pol_hyps;}

signals:

public slots:
};

#endif // DRAW_H
