#include "algorithms.h"
#include <cmath>
#include <iostream>
#include "sortbyy.h"
#include "sortbyx.h"


Algorithms::Algorithms()
{

}

double Algorithms::get2LinesAngle(QPoint &p1, QPoint &p2, QPoint &p3, QPoint &p4)
{
    //Compute angle formed by two lines

    //Coordinate differences
    double ux = p2.x() - p1.x();
    double uy = p2.y() - p1.y();

    double vx = p4.x() - p3.x();
    double vy = p4.y() - p3.y();

    //Dot product
    double dp = ux*vx + uy*vy;

    //Norms
    double nu = sqrt(ux*ux + uy*uy);
    double nv = sqrt(vx*vx + vy*vy);

    //Angle
    return fabs(acos(dp/(nu*nv)));

}

int Algorithms::getPointLinePosition(QPoint &a,QPoint &p1,QPoint &p2)
{
    //Analyze point and line position
    double eps = 1.0e-10;

    //Coordinate differences
    double ux=p2.x()-p1.x();
    double uy=p2.y()-p1.y();

    double vx=a.x()-p1.x();
    double vy=a.y()-p1.y();

    //Half plane test(cross product)
    double t = ux*vy-vx*uy;

    //Point in the left halfplane
    if (t > eps)
        return 1;

    //Point in the right halfplane
    if (t < -eps)
        return 0;

    //Point on the line
    if(fabs(t) < eps)
        return -1;
}

double Algorithms::getPointLineDistance(QPoint &a, QPoint &p1, QPoint &p2)
{
    double du = a.x()*(p1.y()-p2.y()) + p1.x()*(p2.y()-a.y()) + p2.x()*(a.y()-p1.y());
    double dl = sqrt((p2.x()-p1.x())*(p2.x()-p1.x()) + (p2.y()-p1.y())*(p2.y()-p1.y()));

    return fabs(du)/dl;
}

QPolygon Algorithms::cHullJarvisScan(std::vector <QPoint> &points)
{
    QPolygon ch;

    //Sort points by Y and find pivot
    QPoint q=*std::min_element(points.begin(), points.end(), sortByY());

    //Add pivot to convex hull
    ch.append(q);

    //Create pj, pjj
    QPoint pj = q;
    QPoint pjj(0, q.y());

    do
    {
        int i_max = -1;
        double om_max = 0;

        //Find next point
        for (int i=0; i<points.size(); i++)
        {
            double om = get2LinesAngle(pj, pjj, pj, points[i]);

            //Update maximum
            if(om > om_max)
            {
                om_max = om;
                i_max = i;
            }
        }

        //Add point to convex hull
        ch.append(points[i_max]);

        //Update pj to pjj
        pjj = pj;
        pj = points [i_max];

    } while(pj != q);

    return ch;
}

std::vector<QPoint> Algorithms::rotate(std::vector<QPoint> &points, double sigma)
{
    //Rotate dataset by angle
    std::vector<QPoint> r_points;

    for (int i = 0; i < points.size(); i++)
    {
        //Rotate point
        double x_r = points[i].x() * cos(sigma) - points[i].y() * sin(sigma);
        double y_r = points[i].x() * sin(sigma) + points[i].y() * cos(sigma);

        //Create point
        QPoint rp(x_r, y_r);
        r_points.push_back(rp);
    }
    return r_points;
}

std::tuple<std::vector<QPoint>, double> Algorithms::minMaxBox(std::vector<QPoint> &points)
{
    //Return vertices minMaxBox and area
    double area = 0;

    //Return min/max vertices
    QPoint pxmin = *std::min_element(points.begin(), points.end(), sortByX());
    QPoint pxmax = *std::max_element(points.begin(), points.end(), sortByX());
    QPoint pymin = *std::min_element(points.begin(), points.end(), sortByY());
    QPoint pymax = *std::max_element(points.begin(), points.end(), sortByY());

    //Create min/max box vertices
    QPoint v1(pxmin.x(), pymin.y());
    QPoint v2(pxmax.x(), pymin.y());
    QPoint v3(pxmax.x(), pymax.y());
    QPoint v4(pxmin.x(), pymax.y());

    //Create minmax box polygon
    std::vector<QPoint> mmb{v1, v2, v3, v4};

    //Calculate minmax box area
    area = (pxmax.x() - pxmin.x()) * (pymax.y() - pymin.y());

    return {mmb, area};
}

QPolygon Algorithms::minAreaEnclosingRectangle(std::vector<QPoint> &points)
{
    //Create minimum area enclosing rectangle
    QPolygon ch = cHullJarvisScan(points);

    //Searching for minmaxbox with min area
    int n = points.size();
    double sigma_min = 0;
    std::vector<QPoint> mmb_min;

    //Initializing area_min
    auto [mmb, area_min] = minMaxBox(points);

    for (int i = 0; i < n; i++)
    {
        //Coordinate differences
        double dx = ch[(i+1)%n].x() - ch[i].x();
        double dy = ch[(i+1)%n].y() - ch[i].y();

        double sigma = atan2(dy, dx);

        //Rotate by -sigma
        std::vector<QPoint> r_points = rotate(points, -sigma);

        //Create minmaxbox
        auto [mmb, area] = minMaxBox(r_points);

        //Update minimum
        if (area < area_min)
        {
            area_min = area;
            sigma_min = sigma;
            mmb_min = mmb;
        }
    }

    //Create enclosing rectangle
    std::vector<QPoint> er = rotate(mmb_min, sigma_min);

    //Resize rectangle, preserve area of the building
    std::vector<QPoint> err = resizeRectangle(points, er);

    //Convert to QPolygon
    QPolygon er_pol = {err[0], err[1], err[2], err[3]};

    return er_pol;

}


QPolygon Algorithms::wallAverage(std::vector<QPoint> &points)
{
    //Create enclusing rectangle using wall average
    double sigma = 0, si_sum = 0;
    QPolygon pol;

    //Compute initial direction
    double dx = points[1].x() - points[0].x();
    double dy = points[1].y() - points[0].y();
    double sigma_ = atan2(dy, dx);

    //Compute directions for segments
    int n = points.size();
    for (int i = 0; i<n; i++)
    {
        //Compute direction and length
        double dxi = points[(i+1)%n].x() - points[i].x();
        double dyi = points[(i+1)%n].y() - points[i].y();

        double sigmai = atan2(dyi, dxi);
        double lengthi = sqrt(dxi*dxi + dyi*dyi);

        //Compute direction differences
        double dsigmai = sigmai - sigma_;
        if (dsigmai < 0)
            dsigmai += 2*M_PI;

        //Compute fraction
        double ki = round(dsigmai / (M_PI/2));

        //Compute reminder
        double ri = dsigmai - ki*M_PI/2;

        //Weighted average
        sigma += ri*lengthi;
        si_sum += lengthi;
    }
    //Weighted average
    sigma = sigma_ + sigma/si_sum;

    //Rotate by -sigma
    std::vector<QPoint> r_points = rotate(points, -sigma);

    //Create minmaxbox
    auto [mmb, area] = minMaxBox(r_points);

    //Create enclosing rectangle
    std::vector<QPoint> er = rotate(mmb, sigma);

    //Resize rectangle
    std::vector<QPoint> err = resizeRectangle(points, er);

    //Convert to QPolygon
    QPolygon er_pol = {err[0], err[1], err[2], err[3]};

    return er_pol;
}

double Algorithms::LH(std::vector<QPoint> &points)
{
    //Get area of building by LH algorithm
    double area = 0;
    int n = points.size();

    for (int i = 0; i<n; i++)
    {
        area += points[i].x() * (points[(i+1)%n].y() - points[(i-1+n)%n].y());
    }

    return 0.5 * fabs(area);
}

std::vector<QPoint> Algorithms::resizeRectangle(std::vector<QPoint> &points, std::vector<QPoint> &er)
{
    //Resize rectangle to given area

    //Building area
    double AB = LH(points);

    //Rectangle area
    double AR = LH(er);

    //Fraction of areas
    double k = AB / AR;

    //Center of mass
    double xc = (er[0].x() + er[1].x() + er[2].x() + er[3].x()) / 4;
    double yc = (er[0].y() + er[1].y() + er[2].y() + er[3].y()) / 4;

    //Compute vector components
    double u1x = er[0].x() - xc;
    double u1y = er[0].y() - yc;
    double u2x = er[1].x() - xc;
    double u2y = er[1].y() - yc;
    double u3x = er[2].x() - xc;
    double u3y = er[2].y() - yc;
    double u4x = er[3].x() - xc;
    double u4y = er[3].y() - yc;

    //Create new rectangle vertices
    QPoint v1_(xc + sqrt(k)*u1x, yc + sqrt(k)*u1y);
    QPoint v2_(xc + sqrt(k)*u2x, yc + sqrt(k)*u2y);
    QPoint v3_(xc + sqrt(k)*u3x, yc + sqrt(k)*u3y);
    QPoint v4_(xc + sqrt(k)*u4x, yc + sqrt(k)*u4y);

    //Add to polygon
    std::vector<QPoint> er_res = {v1_, v2_, v3_, v4_};

    return er_res;

}

QPolygon Algorithms::longestEdge(std::vector<QPoint> &points)
{

    //Set maxmum edge lenght
    double edge_max = 0;

    //Compute directions for segments
    int n = points.size();
    double dx_max, dy_max;

    for (int i = 0; i < n; i++)
    {
        //Coordinate differences
        double dx = points[(i+1)%n].x() - points[i].x();
        double dy = points[(i+1)%n].y() - points[i].y();

        //Edge length
        double edge_len = sqrt(dx*dx + dy*dy);

        //Find the longest edge and its vertices
        if(edge_len > edge_max)
        {
            edge_max = edge_len;
            dx_max = dx;
            dy_max = dy;
        }
    }

    //Compute angle
    double sigma = atan2(dy_max, dx_max);

    //Rotate polygon (points)
    std::vector<QPoint> r_points = rotate(points, -sigma);

    //Minmax box
    auto [mmb, area] = minMaxBox(r_points);

    //Create enclosing rectangle
    std::vector<QPoint> er = rotate(mmb, sigma);

    //Resize rectangle, preserve area of the building
    std::vector<QPoint> err = resizeRectangle(points, er);

    //Convert to QPolygon
    QPolygon err_pol = {err[0], err[1], err[2], err[3]};
    return err_pol;

}

QPolygon Algorithms::weightedBisector(std::vector<QPoint> &points)
{
    //Calculate all diagonals
    int n = points.size();
    int diag_count = n*(n-3)/2;
    double diag_max1 = 0, diag_max2 = 0, dx_max1, dy_max1, dx_max2, dy_max2;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < diag_count; j++)
        {
            //Coordinate differences
            double dx = points[(j+2)%n].x() - points[i].x();
            double dy = points[(j+2)%n].y() - points[i].y();

            //Diagonal length
            double diag = sqrt(dx*dx + dy*dy);

            //Find the longest diagonal and its vertices
            if(diag > diag_max1)
            {
                diag_max2 = diag_max1;
                diag_max1 = diag;

                dx_max2 = dx_max1;
                dy_max2 = dy_max1;
                dx_max1 = dx;
                dy_max1 = dy;
            }
        }
    }
    /*
    //Diagonal length check
    std::cout << "diag_max1: " << diag_max1 << std::endl;
    std::cout << "diag_max2: " << diag_max2 << std::endl;
    */

    //Compute angles of diagonals
    double sigma1 = atan2(dy_max1, dx_max1);
    double sigma2 = atan2(dy_max2, dx_max2);

    //Compute main angle
    double sigma = (diag_max1*sigma1 + diag_max2*sigma2)/(diag_max1+diag_max2);

    /*
    std::cout << "sigma1: " << sigma1 << std::endl;
    std::cout << "sigma2: " << sigma2 << std::endl;
    std::cout << "sigma: " << sigma << std::endl;
    */

    //Rotate polygon (points)
    std::vector<QPoint> r_points = rotate(points, -sigma);

    //Minmax box
    auto [mmb, area] = minMaxBox(r_points);

    //Create enclosing rectangle
    std::vector<QPoint> er = rotate(mmb, sigma);

    //Resize rectangle, preserve area of the building
    std::vector<QPoint> err = resizeRectangle(points, er);

    //Convert to QPolygon
    QPolygon err_pol = {err[0], err[1], err[2], err[3]};
    return err_pol;
}

QPolygon Algorithms::cHullQuickHull(std::vector <QPoint> &points)
{
    QPolygon ch;
    std::vector<QPoint> su, sl;

    //Sort by x and find q1 and q3
    QPoint q1 =*std::min_element(points.begin(), points.end(), sortByX());
    QPoint q3 =*std::max_element(points.begin(), points.end(), sortByX());

    //Add q1, q3 to su, sl
    su.push_back(q1);
    su.push_back(q3);
    sl.push_back(q1);
    sl.push_back(q3);

    int n = points.size();
    //Distribution of points to upper or lower segment
    for(int i = 0; i < n;i++)
    {
        //Left half-plane
        if(getPointLinePosition(points[i], q1, q3) == 1)
            su.push_back(points[i]);

        //Right half-plane
        else if(getPointLinePosition(points[i], q1, q3) == 0)
            sl.push_back(points[i]);
    }

    //Add q3 to chull
    ch.push_back(q3);

    //Compute su
    quickHullLocal(1, 0, su, ch);

    //Add q1 to chull
    ch.push_back(q1);

    //Compute sl
    quickHullLocal(0, 1, sl, ch);

    return ch;
}

void Algorithms::quickHullLocal(int ps, int pe, std::vector<QPoint> &points, QPolygon &ch)
{
    int i_max = -1;
    double dist_max = 0;

    //Does the point  exists on the right from the edge?
    for(int i = 2; i < points.size(); i++)
    {
        if(getPointLinePosition(points[i], points[ps], points[pe]) == 0)
        {
            double dist = getPointLineDistance(points[i], points[ps], points[pe]);

            //Point with maximum distance
            if(dist > dist_max)
            {
                dist_max = dist;
                i_max = i;
            }
        }
    }

    //When point in the right half-plane exists
    if(i_max > -1)
    {
        //Compute chull - upper hull
        quickHullLocal(ps, i_max, points, ch);

        //Add point to chull
        ch.push_back(points[i_max]);

        //Compute chull - lower hull
        quickHullLocal(i_max, pe, points, ch);
    }
}






