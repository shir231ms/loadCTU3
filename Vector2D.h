#include <stdio.h>
struct Vector2D {
    double x, y;
    Vector2D(double,double);
    Vector2D operator*(double);
    double dot(Vector2D,Vector2D);
    double cross(Vector2D,Vector2D);
};  // �G���V�q����Ƶ��c
inline Vector2D::Vector2D(double a,double b): x(a),y(b){}
inline Vector2D Vector::operator*(double t){ return {t*this.x,t*this.y}; }
inline double Vector2D::dot(Vector2D v1, Vector2D v2)// �I�n�B��
{
    // �S�����k�A���q�קK�~�t�C
    return v1.x * v2.x + v1.y * v2.y;
}
inline double Vector2D::cross(Vector2D v1, Vector2D v2)// �e�n�B��A�^�ǯ¶q�]���h��V�^
{
    // �S�����k�A���q�קK�~�t�C
    return v1.x * v2.y - v1.y * v2.x;
}
//���Τe�n�P�_�I�P�u�q�O�_�@�u�A�A���I�n�P�_�I�O�_���u�q���I�����C

struct Point2D {
    double x, y;
    Point2D(double,double);
    Point2D operator+(Vector2D);
    Point2D operator-(Vector2D);
    Vector2D operator-(Point2D);
};  // �G���I����Ƶ��c
inline Point2D::Point2D(double a,double b): x(a),y(b){}
inline Point2D Point2D::operator+(Vector2D v){ return {this.x+v.x,this.y+v.y}; }
inline Point2D Point2D::operator-(Vector2D v){ return {this.x-v.x,this.y-v.y}; }
inline Vector2D Point2D::operator-(Point2D p){ return {this.x-p.x,this.y-p.y}; }


