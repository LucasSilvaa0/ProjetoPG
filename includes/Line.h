#ifndef LINE_H
#define LINE_H

#include "Point.h"
#include "Vector.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"

class Line
{
public:
    Point3D point1;       // Primeiro ponto da linha
    Vector3D line_vector; // Vetor diretor da reta
    Vector3D cor;

    Line(const Point3D &p1, const Point3D &p2) : point1(p1), line_vector(p2 - p1)
    {
        line_vector.normalize();
    }

    void print() const
    {
        std::cout << "Line:\n";
        std::cout << "  Point 1: ";
        point1.print();
        std::cout << "  Vetor diretor: ";
        line_vector.print();
    }

    Point3D at(double t)
    {
        return point1 + line_vector * t;
    }

    double l_s_intersection(Sphere &s)
    {
        Vector3D oc = s.C - point1;
        auto a = line_vector.dot(line_vector);
        auto h = line_vector.dot(oc);
        auto c = oc.dot(oc) - s.r*s.r;
        auto discriminant = h*h - a*c;
        if(discriminant<0){
            return -1.0;
        }else{
            return (h-std::sqrt(discriminant))/a;
        }
    }

    double l_p_intersection(Plane &p)
    {
        double x0, y0, z0, a, b, c, i, j, k, u, v, w;

        x0 = p.point.getX();
        y0 = p.point.getY();
        z0 = p.point.getZ();

        a = p.normal.getX();
        b = p.normal.getY();
        c = p.normal.getZ();

        i = point1.getX();
        j = point1.getY();
        k = point1.getZ();

        u = line_vector.getX();
        v = line_vector.getY();
        w = line_vector.getZ();

        double t = -1 * ((a * i + b * j + c * k) + (-a * x0 - b * y0 - c * z0)) / (a * u + b * v + c * w);
        return t;
    }

    double l_t_intersection(Triangle &tr)
    {
        Point3D v0 = tr.v0;
        Point3D v1 = tr.v1;
        Point3D v2 = tr.v2;

        const double EPSILON = 0.00000000001;

        Vector3D edge1 = v1 - v0;
        Vector3D edge2 = v2 - v0;
        Vector3D h = line_vector.cross(edge2);
        double a = edge1.dot(h);

        if (a > -EPSILON && a < EPSILON)
        {
            return -1;
        }

        double f = 1.0 / a;
        Vector3D s = point1 - v0;
        double u = f * s.dot(h);

        if (u < 0.0 || u > 1.0)
        {
            return -1;
        }

        Vector3D q = s.cross(edge1);
        double v = f * line_vector.dot(q);

        if (v < 0.0 || u + v > 1.0)
        {
            return -1;
        }

        double t = f * edge2.dot(q);

        if (t > EPSILON)
        {
            return t;
        }
        else
        {
            return -1;
        }
    }
};

#endif