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

        //Point in the left halfplane
        if (pos==1)
            omega_sum += omega;
        else if (pos == 0)
            omega_sum -= omega;

        //Point on the line
        else
        {
            return -1;
        }


    }

    //Point inside polygon
    double eps = 1.0e-5;
    if (fabs(fabs(omega_sum) - 2*M_PI) < eps)
    {
        return 1;
    }
    //Point outside polygon
    else
    {
        return 0;
    }
}

int Algorithms::getPositionRayCrossing(QPoint &q, std::vector<QPoint> &pol)
{
    int k = 0;
    double eps = 1.0e-10;

    //Reduce the first point
    double xr = pol[0].x() - q.x();
    double yr = pol[0].y() - q.y();

    int n = pol.size();

    for (int i = 1; i < n+1; i++)
    {
        double xi = pol[i%n].x() - q.x();
        double yi = pol[i%n].y() - q.y();

        double d = sqrt((xr-xi)*(xr-xi) + (yr-yi)*(yr-yi));
        double dq = sqrt((xr*xr + yr*yr)) + sqrt((xi*xi + yi*yi));

        //point on the border
        if(fabs(d-dq) < eps)
        {
            return -1;
        }

        //Upper halfplane
        if (((yr > 0) && (yi <= 0)) || ((yi > 0) && (yr <= 0)))
        {
            double xm = (xr * yi - xi * yr) / (yr - yi);

            if (xm > 0)
                k += 1;
        }

        xr = xi;
        yr = yi;
    }

    return k % 2;
}
