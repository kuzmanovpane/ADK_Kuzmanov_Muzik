#include "algorithms.h"
#include <cmath>
#include <iostream>
using namespace std;

Algorithms::Algorithms()
{

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

    //Point is on the vertex
    if (((a.x()==p1.x()) && (a.y()==p1.y())) || ((a.x()==p2.x()) && (a.y()==p2.y())))
        return -2;

    //Point in the left halfplane
    else if (t > eps)
        return 1;

    //Point in the right halfplane
    else if (t < -eps)
        return 0;

    //Point on the line and making sure that the point a is between point p1 and point p2
    else if((fabs(t) < eps) && ((a.x() > p1.x()) && (a.x() < p2.x()) && (a.y() > p1.y()) && (a.y() < p2.y())))
        return -1;
}

double Algorithms::get2LinesAngle(QPoint &p1, QPoint &p2, QPoint &p3, QPoint &p4)
{
    //Compute angle formed by two lines

    //Coordinate differences
    double ux=p2.x()-p1.x();
    double uy=p2.y()-p1.y();

    double vx=p4.x()-p3.x();
    double vy=p4.y()-p3.y();

    //Dot product
    double dp=ux*vx+uy*vy;

    //Norms
    double nu = sqrt(ux*ux + uy*uy);
    double nv = sqrt(vx*vx + vy*vy);

    //Angle
    return fabs(acos(dp/(nu*nv)));
}


int Algorithms::getPositionWinding(QPoint &q, std::vector<QPoint> &pol)
{
    //Analyze position of point and polygon
    int n = pol.size();
    double omega_sum=0;

    //Process all segments of polygon
    for (int i = 0; i<n; i++)
    {
        // Angle between two line segments
        double omega = get2LinesAngle(pol[i], q, pol[(i+1)%n], q);

        // Point and line segment position
        int pos = getPointLinePosition(q, pol[i], pol[(i+1)%n]);

        //Point on the vertex
        if (pos == -2)
            return -2;

        //Point in the left halfplane
        else if (pos==1)
            omega_sum += omega;
        else if (pos == 0)
            omega_sum -= omega;

        //Point on the line
        else if(pos == -1)
            return -1;
    }

    //Point inside polygon
    double eps = 1.0e-5;
    if (fabs(fabs(omega_sum) - 2*M_PI) < eps)
        return 1;

    //Point outside polygon
    else
        return 0;
}

int Algorithms::getPositionRayCrossing(QPoint &q, std::vector<QPoint> &pol)
{
    int k = 0;
    double eps = 1.0e-10;
    int n = pol.size();

    for (int i = 1; i < n+1; i++)
    {
        //Point is on the vertex
        if (((q.x()==pol[i].x()) && (q.y()==pol[i].y())) || ((q.x()==pol[i].x()) && (q.y()==pol[i].y())))
            return -2;

        double xi = pol[i].x() - q.x();
        double yi = pol[i].y() - q.y();

        double xr = pol[i-1].x() - q.x();
        double yr = pol[i-1].y() - q.y();

        double d = sqrt((xr-xi)*(xr-xi) + (yr-yi)*(yr-yi));
        double dq = sqrt((xr*xr + yr*yr)) + sqrt((xi*xi + yi*yi));

        //Point is on the border
        if(fabs(d-dq) < eps)
            return -1;


        //Find point position
        if (((yr > 0) && (yi <= 0)) || ((yi > 0) && (yr <= 0)))
        {
            double xm = (xi * yr - xr * yi) / (yi - yr);

            //Point is in the right halfplane
            if (xm > eps)
                k += 1;
        }
    }
    return k% 2;
}
