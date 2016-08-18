#include "Vector2D.h"
#include <cmath>       /* acos */
bool intersect(Point2D p, Point2D p1, Point2D p2)
{
    // 點與線段共線，而且點要在線段之間。
    return cross(p, p1, p2) == 0
        && dot(p, p1, p2) <= 0;
}
//點到線段的距離
double distance(Point2D p, Point2D n1, Point2D n2)
{
    // 建立向量求點積，以判斷點在哪一區。
    Vector v = n2 - n1;
    Vector v1 = p - n1;
    Vector v2 = p - n2;

    // 端點距離區：點到點距離
    // 等於=可以省略
    if (dot(v, v1) <= 0) return length(v1);
    if (dot(v, v2) >= 0) return length(v2);
    // 垂直距離區：點到線距離
    return fabs(cross(v, v1)) / length(v);
}

//判斷兩線段是否相交
bool intersect(Point2D a1, Point2D a2, Point2D b1, Point2D b2)
{
    double c1 = cross(a1, a2, b1);
    double c2 = cross(a1, a2, b2);
    double c3 = cross(b1, b2, a1);
    double c4 = cross(b1, b2, a2);
    // 端點不共線
    if (c1 * c2 < 0 && c3 * c4 < 0) return true;
    // 端點共線
    if (c1 == 0 && intersect(a1, a2, b1)) return true;
    if (c2 == 0 && intersect(a1, a2, b2)) return true;
    if (c3 == 0 && intersect(b1, b2, a1)) return true;
    if (c4 == 0 && intersect(b1, b2, a2)) return true;
    return false;
}

//確定相交->求交點(Line & Line)
Point2D intersection(Point2D a1, Point2D a2, Point2D b1, Point2D b2)
{
    Point2D a = a2 - a1, b = b2 - b1, s = b1 - a1;
    double c1 = cross(a, b), c2 = cross(s, b);

    if (c1 == 0)
        if (c2 == 0)
            return INF; // 兩線重疊
        else
            return INF; // 兩線平行但不重疊
    else
        return a1  + (a1a2 * (c2 / c1));
}

//判斷線段(a)與弧(b)是否相交
/*
 * from and to are points at the start and end of the convex polygons edge.
 * This function is called for every edge in the convex polygon until a
 * collision is detected.
 */
bool pointOnLine(Vector2D p, Vector2D from, Vector2D to)
{
    if (p.x >= min(from.x, to.x) && p.x <= max(from.x, to.x) &&
        p.y >= min(from.y, to.y) && p.y <= max(from.y, to.y))
        return true;
    return false;
}

bool circleLineCollision(Point2D from, Point2D to, Point2D centre, double radius, Point2D& intersectPt1, Point2D& intersectPt2, int& NUM)
{
    Vector2D lFrom, lTo, lLine;
    Vector2D line, normal;
    double a, b, c, disc, sqrt_disc, u, v, nn, vn;
    bool one = false, two = false;

    // set line vectors
    lFrom = from - centre;      // localised
    lTo = to - centre;          // localised
    lLine = lFrom - lTo;        // localised //d

    // calculate a, b & c values
    a = lLine.dot(lLine); //d
    b = 2 * (lLine.dot(lFrom));
    c = (lFrom.dot(lFrom)) - (radius * radius);

    // discriminant
    disc = (b * b) - (4 * a * c);

    if (disc < 0.0f)
    {
        // no intersections
        return false;
    }
    else if (disc == 0.0f)
    {
        // one intersection
        u = -b / (2 * a);

        intersectPt1 = from + u*lLine;
        one = pointOnLine(intersectPt1, from, to);

        if (!one)
            return false;
        NUM=1;
        return true;
    }
    else
    {
        // two intersections
        sqrt_disc = sqrt(disc);
        u = (-b + sqrt_disc) / (2 * a);
        v = (-b - sqrt_disc) / (2 * a);
        intersectPt1 = from + u*lLine;
        intersectPt2 = from + v*lLine;

        one = pointOnLine(intersectPt1, from, to);
        two = pointOnLine(intersectPt2, from, to);

        if (!one && !two)
            return false;
        NUM=2;
        return true;
    }
}

bool intersect(Point2D a1, Point2D a2, Point2D b1, Point2D b2, double r, Point2D c)
{
    Point2D interPt1, interPt2;//at last true intersection points
    Vector2D key={c.x,c.y};
    int caseNum=-1;
    double a11,a1_arc,a22,a2_arc,int1,int1_arc,int2,int2_arc;

    if((a1.y-c.y)/r > 1) a11=1;
    else if((a1.y-c.y)/r < -1) a11=-1;
    else a11=(a1.y-c.y)/r;
    a1_arc=asin(a11);//arc
    if((a2.y-c.y)/r > 1) a22=1;
    else if((a2.y-c.y)/r < -1) a22=-1;
    else a22=(a2.y-c.y)/r;
    a2_arc=asin(a22);

    circleLineCollision(a1-key,a2-key,c,r,interPt1,interPt2,caseNum);

    if(caseNum==1){
        if((interPt1.y-c.y)/r > 1) int1=1;
        else if((interPt1.y-c.y)/r < -1) int1=-1;
        else int1=(interPt1.y-c.y)/r;
        int1_arc=asin(int1);

        if(a2_arc<a1_arc){
            if(int1_arc>=a1_arc){
                if(int1_arc>=a1_arc && -int1_arc<=a2_arc){
                    interPt1=interPt1+key;
                    return true;
                }
            }
            else {
                if(int1_arc>=-a1_arc && int1_arc<=a2_arc){
                    interPt1=interPt1+key;
                    return true;
                }
            }
        }
        else{
            if(int1_arc>=a1_arc && int1_arc<=a2_arc){
                interPt1=interPt1+key;
                return true;
            }
        }
        return false;
    }
    else if(caseNum==2){
        if((interPt1.y-c.y)/r > 1) int1=1;
        else if((interPt1.y-c.y)/r < -1) int1=-1;
        else int1=(interPt1.y-c.y)/r;
        int1_arc=asin(int1);
        if((interPt2.y-c.y)/r > 1) int2=1;
        else if((interPt2.y-c.y)/r < -1) int2=-1;
        else int2=(interPt2.y-c.y)/r;
        int2_arc=asin(int2);

        if(a2_arc<a1_arc){
            if(int1_arc>=a1_arc){
                if(int1_arc>=a1_arc && -int1_arc<=a2_arc){
                    interPt1=interPt1+key;
                }
                else return false;
            }
            else {
                if(int1_arc>=-a1_arc && int1_arc<=a2_arc){
                    interPt1=interPt1+key;
                }
                else return false;
            }
            if(int2_arc>=a1_arc){
                if(int2_arc>=a1_arc && -int2_arc<=a2_arc){
                    interPt2=interPt2+key;
                    return true;
                }
            }
            else {
                if(int2_arc>=-a1_arc && int2_arc<=a2_arc){
                    interPt2=interPt2+key;
                    return true;
                }
            }
        }
        else{
            if(int1_arc>=a1_arc && int1_arc<=a2_arc && int1_arc>=a1_arc && int1_arc<=a2_arc){
                interPt1=interPt1+key;
                interPt2=interPt2+key;
                return true;
            }
        }
        return false;
    }
    else return false;
}
