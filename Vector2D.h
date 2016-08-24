#include <stdio.h>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;
ofstream outfile("intersect_c.txt");
class Vector2D {
public:
    double x, y;
    Vector2D();
    ~Vector2D();
    Vector2D(double,double);
    Vector2D operator*(double);
    double dot(Vector2D);
    double cross(Vector2D);
    Vector2D operator+(Vector2D);
    Vector2D operator-(Vector2D);
    double length();
};  // �G���V�q����Ƶ��c
inline Vector2D::Vector2D(){}
inline Vector2D::~Vector2D(){}
inline Vector2D::Vector2D(double a,double b): x(a),y(b){}
inline Vector2D Vector2D::operator*(double t){ return {t*this->x,t*this->y}; }
inline Vector2D Vector2D::operator+(Vector2D v){ return {this->x+v.x,this->y+v.y}; }
inline Vector2D Vector2D::operator-(Vector2D v){ return {this->x-v.x,this->y-v.y}; }
// �V�q������
inline double Vector2D::length()
{
    return sqrt(this->x * this->x + this->y * this->y);
}
inline double Vector2D::dot(Vector2D v)// �I�n�B��
{
    // �S�����k�A���q�קK�~�t�C
    return this->x * v.x + this->y * v.y;
}
inline double Vector2D::cross(Vector2D v)// �e�n�B��A�^�ǯ¶q�]���h��V�^
{
    // �S�����k�A���q�קK�~�t�C
    return this->x * v.y - this->y * v.x;
}
//���Τe�n�P�_�I�P�u�q�O�_�@�u�A�A���I�n�P�_�I�O�_���u�q���I�����C

class Point2D {
public:
    double x, y;
    Point2D();
    ~Point2D();
    Point2D(double,double);
    double dot(Point2D,Point2D);
    double cross(Point2D,Point2D);
    Point2D operator+(Vector2D);
    Point2D operator-(Vector2D);
    Vector2D operator-(Point2D);
};  // �G���I����Ƶ��c
inline Point2D::Point2D(){}
inline Point2D::~Point2D(){}
inline Point2D::Point2D(double a,double b): x(a),y(b){}
inline Point2D Point2D::operator+(Vector2D v){ return {this->x+v.x,this->y+v.y}; }
inline Point2D Point2D::operator-(Vector2D v){ return {this->x-v.x,this->y-v.y}; }
inline Vector2D Point2D::operator-(Point2D p){ return {this->x-p.x,this->y-p.y}; }
inline double Point2D::dot(Point2D a,Point2D b)// �I�n�B��
{
    // �S�����k�A���q�קK�~�t�C
    return (a.x-this->x) * (b.x-this->x) + (a.y-this->y) * (b.y-this->y);
}

inline double Point2D::cross(Point2D a,Point2D b)// �e�n�B��A�^�ǯ¶q�]���h��V�^
{
    // �S�����k�A���q�קK�~�t�C
    return (a.x-this->x) * (b.y-this->y) - (a.y-this->y) * (b.x-this->x);
}

bool intersect_(Point2D p, Point2D p1, Point2D p2)
{
    // �I�P�u�q�@�u�A�ӥB�I�n�b�u�q�����C
    return p.cross(p1, p2) == 0
        && p.dot(p1, p2) <= 0;
}
//�I��u�q���Z��
double distance(Point2D p, Point2D n1, Point2D n2)
{
    // �إߦV�q�D�I�n�A�H�P�_�I�b���@�ϡC
    Vector2D v = n2 - n1;
    Vector2D v1 = p - n1;
    Vector2D v2 = p - n2;

    // ���I�Z���ϡG�I���I�Z��
    // ����=�i�H�ٲ�
    if (v.dot(v1) <= 0) return v1.length();
    if (v.dot(v2) >= 0) return v2.length();
    // �����Z���ϡG�I��u�Z��
    return fabs(v.cross(v1)) / v.length();
}

//�P�_��u�q�O�_�ۥ�
bool intersect(Point2D a1, Point2D a2, Point2D b1, Point2D b2, Point2D& intersectionPt)
{
    bool inter_bool=false;
    double c1 = a1.cross(a2, b1);
    double c2 = a1.cross(a2, b2);
    double c3 = b1.cross(b2, a1);
    double c4 = b1.cross(b2, a2);
    // ���I���@�u
    if (c1 * c2 < 0 && c3 * c4 < 0) {
        inter_bool=true;
        goto tag;
    }
    // ���I�@�u
    if (c1 == 0 && intersect_(a1, a2, b1)) {
        inter_bool=true;
        goto tag;
    }
    if (c2 == 0 && intersect_(a1, a2, b2)) {
        inter_bool=true;
        goto tag;
    }
    if (c3 == 0 && intersect_(b1, b2, a1)) {
        inter_bool=true;
        goto tag;
    }
    if (c4 == 0 && intersect_(b1, b2, a2)) {
        inter_bool=true;
        goto tag;
    }
    if (inter_bool==false)
        return false;
    tag:
    //�T�w�ۥ�->�D���I(Line & Line)
    Vector2D a = a2 - a1, b = b2 - b1, s = b1 - a1;
    double d1 = a.cross(b), d2 = s.cross(b);

    if (d1 == 0)
        if (d2 == 0)
            return false; // ��u���|
        else
            return false; // ��u����������|
    else{
        intersectionPt= a1  + (a * (d2 / d1));
        return true;
    }
}

//�P�_��(a)�P�u�q(b)�O�_�ۥ�
/*
 * from and to are points at the start and end of the convex polygons edge.
 * This function is called for every edge in the convex polygon until a
 * collision is detected.
 */
bool pointOnLine(Point2D p, Point2D from, Point2D to)
{
    if (p.x >= min(from.x, to.x) && p.x <= max(from.x, to.x) &&
        p.y >= min(from.y, to.y) && p.y <= max(from.y, to.y))
        return true;
    return false;
}

int circleLineCollision(Point2D from, Point2D to, double radius, Point2D& intersectPt1, Point2D& intersectPt2)
{
    Vector2D lFrom, lTo, lLine;
    Vector2D line, normal;
    double a, b, c, disc, sqrt_disc, u, v;
    bool one = false, two = false;

    // set line vectors
    Point2D centre(0.0,0.0);
    lFrom = from-centre;      // localised
    lTo = to-centre;          // localised
    lLine = lTo-lFrom ;        // localised //d
    //cout<<"line-data: ("<<lFrom.x<<","<<lFrom.y<<"), ("<<lTo.x<<","<<lTo.y<<"), ("<<lLine.x<<","<<lLine.y<<")"<<endl;
    // calculate a, b & c values
    a = lLine.dot(lLine); //d
    b = 2 * (lLine.dot(lFrom));
    c = (lFrom.dot(lFrom)) - (radius * radius);
    //cout<<"formula-data: ("<<a<<","<<b<<","<<c<<")"<<endl;

    // discriminant
    disc = (b * b) - (4 * a * c);

    if (disc < 0.0f)
    {
        // no intersections
        return 0;
    }
    else if (disc == 0.0f)
    {
        // one intersection
        u = -b / (2 * a);

        intersectPt1 = from + lLine*u;
        one = pointOnLine(intersectPt1, from, to);

        if (!one)
            return 0;
        return 1;
    }
    else
    {
        // two intersections
        sqrt_disc = sqrt(disc);
        u = (-b + sqrt_disc) / (2 * a);
        v = (-b - sqrt_disc) / (2 * a);
        intersectPt1 = from + lLine*u;
        intersectPt2 = from + lLine*v;

        one = pointOnLine(intersectPt1, from, to);
        two = pointOnLine(intersectPt2, from, to);

        if (!one && !two)
            return 0;
        return 2;
    }
}

void intersect(Point2D a1, Point2D a2, Point2D b1, Point2D b2, long double r, Point2D c, vector<Point2D*>& vecPt)
{
    //a:arc, b:line
    //at last true intersection points
    Vector2D key={c.x,c.y};
    int caseNum=0;
    double a11,a1_arc,a22,a2_arc,int1,int1_arc,int2,int2_arc;
    Point2D interPt1(0.0,0.0), interPt2(0.0,0.0);

    if((a1.y-c.y)/r > 1) a11=1;
    else if((a1.y-c.y)/r < -1) a11=-1;
    else a11=(a1.y-c.y)/r;
    a1_arc=asin(a11);//arc
    if((a2.y-c.y)/r > 1) a22=1;
    else if((a2.y-c.y)/r < -1) a22=-1;
    else a22=(a2.y-c.y)/r;
    a2_arc=asin(a22);

    caseNum=circleLineCollision(b1-key,b2-key,r,interPt1,interPt2);
    //cout<<"caseNum: "<<caseNum<<endl;

    switch(caseNum){
    case 1:
        if(interPt1.y/r > 1) int1=1;
        else if(interPt1.y/r < -1) int1=-1;
        else int1=interPt1.y/r;
        int1_arc=asin(int1);

        if(a2_arc<a1_arc){
            if(int1_arc>=a1_arc){
                if(int1_arc>=a1_arc && -int1_arc<=a2_arc){
                    interPt1=interPt1+key;
                    vecPt.push_back(&interPt1);
                    outfile<<interPt1.x<<" "<<interPt1.y<<endl;
                }
            }
            else {
                if(int1_arc>=-a1_arc && int1_arc<=a2_arc){
                    interPt1=interPt1+key;
                    vecPt.push_back(&interPt1);
                    outfile<<interPt1.x<<" "<<interPt1.y<<endl;
                }
            }
        }
        else{
            if(int1_arc>=a1_arc && int1_arc<=a2_arc){
                interPt1=interPt1+key;
                vecPt.push_back(&interPt1);
                outfile<<interPt1.x<<" "<<interPt1.y<<endl;
            }
        }
        return;
    case 2:
        if(interPt1.y/r > 1) int1=1;
        else if(interPt1.y/r < -1) int1=-1;
        else int1=interPt1.y/r;
        int1_arc=asin(int1);
        if(interPt2.y/r > 1) int2=1;
        else if(interPt2.y/r < -1) int2=-1;
        else int2=interPt2.y/r;
        int2_arc=asin(int2);

        if(a2_arc<a1_arc){
            if(int1_arc>=a1_arc){
                if(int1_arc>=a1_arc && -int1_arc<=a2_arc){
                    interPt1=interPt1+key;
                    vecPt.push_back(&interPt1);
                    outfile<<interPt1.x<<" "<<interPt1.y<<endl;
                }
            }
            else {
                if(int1_arc>=-a1_arc && int1_arc<=a2_arc){
                    interPt1=interPt1+key;
                    vecPt.push_back(&interPt1);
                    outfile<<interPt1.x<<" "<<interPt1.y<<endl;
                }
            }
            if(int2_arc>=a1_arc){
                if(int2_arc>=a1_arc && -int2_arc<=a2_arc){
                    interPt2=interPt2+key;
                    vecPt.push_back(&interPt2);
                    outfile<<interPt2.x<<" "<<interPt2.y<<endl;
                }
            }
            else {
                if(int2_arc>=-a1_arc && int2_arc<=a2_arc){
                    interPt2=interPt2+key;
                    vecPt.push_back(&interPt2);
                    outfile<<interPt2.x<<" "<<interPt2.y<<endl;
                }
            }
        }
        else{
            if(int1_arc>=a1_arc && int1_arc<=a2_arc){
                interPt1=interPt1+key;
                vecPt.push_back(&interPt1);
                outfile<<interPt1.x<<" "<<interPt1.y<<endl;
            }
            if(int2_arc>=a1_arc && int2_arc<=a2_arc){
                interPt2=interPt2+key;
                vecPt.push_back(&interPt2);
                outfile<<interPt2.x<<" "<<interPt2.y<<endl;
            }
        }
        return;
    default:
        return;
    }
}
