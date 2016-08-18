#include <stdio.h>
struct Vector2D {
    double x, y;
    Vector2D(double,double);
    Vector2D operator*(double);
    double dot(Vector2D,Vector2D);
    double cross(Vector2D,Vector2D);
};  // 二維向量的資料結構
inline Vector2D::Vector2D(double a,double b): x(a),y(b){}
inline Vector2D Vector::operator*(double t){ return {t*this.x,t*this.y}; }
inline double Vector2D::dot(Vector2D v1, Vector2D v2)// 點積運算
{
    // 沒有除法，儘量避免誤差。
    return v1.x * v2.x + v1.y * v2.y;
}
inline double Vector2D::cross(Vector2D v1, Vector2D v2)// 叉積運算，回傳純量（除去方向）
{
    // 沒有除法，儘量避免誤差。
    return v1.x * v2.y - v1.y * v2.x;
}
//先用叉積判斷點與線段是否共線，再用點積判斷點是否位於線段端點之間。

struct Point2D {
    double x, y;
    Point2D(double,double);
    Point2D operator+(Vector2D);
    Point2D operator-(Vector2D);
    Vector2D operator-(Point2D);
};  // 二維點的資料結構
inline Point2D::Point2D(double a,double b): x(a),y(b){}
inline Point2D Point2D::operator+(Vector2D v){ return {this.x+v.x,this.y+v.y}; }
inline Point2D Point2D::operator-(Vector2D v){ return {this.x-v.x,this.y-v.y}; }
inline Vector2D Point2D::operator-(Point2D p){ return {this.x-p.x,this.y-p.y}; }


