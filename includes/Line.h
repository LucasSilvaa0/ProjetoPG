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

        double i, j, k, u, v, w, a, b, c, r, dois = 2;

        a = s.C.getX();
        b = s.C.getY();
        c = s.C.getZ();
        r = s.r;

        i = point1.getX();
        j = point1.getY();
        k = point1.getZ();

        u = line_vector.getX();
        v = line_vector.getY();
        w = line_vector.getZ();

        double A = u * u + v * v + w * w;
        double B = dois * (i * u + j * v + k * w - a * i - a * u - b * j - b * v - c * k - c * w);
        double C = i * i + j * j + k * k + a * a + b * b + c * c - r * r;

        double DELTA = B * B - 4 * A * C;
        if (DELTA < 0)
        {
            return -1;
        }

        double t1 = (-1 * B + sqrt(B * B - 4 * A * C)) / (2 * A);
        double t2 = (-1 * B - sqrt(B * B - 4 * A * C)) / (2 * A);

        if (t1 >= 0 && t1 <= abs(t2))
        {
            return t1;
        }
        return t2;
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

        if (a > -EPSILON && a < EPSILON) {
            return -1;
        }

        double f = 1.0 / a;
        Vector3D s = point1 - v0;
        double u = f * s.dot(h);

        if (u < 0.0 || u > 1.0) {
            return -1; 
        }

        Vector3D q = s.cross(edge1);
        double v = f * line_vector.dot(q);

        if (v < 0.0 || u + v > 1.0) {
            return -1; 
        }

        double t = f * edge2.dot(q);

        if (t > EPSILON) {
            return t; 
        } else {
            return -1;
        }
    }

};

#endif