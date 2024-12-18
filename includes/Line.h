#ifndef LINE_H
#define LINE_H

#include "Point.h"
#include "Vector.h"
#include "Sphere.h"
#include "Plane.h"

class Line
{
public:
    Point3D point1;       // Primeiro ponto da linha
    Vector3D line_vector; // Vetor diretor da reta
    Vector3D cor;

    Line(const Point3D &p1, const Point3D &p2) : point1(p1), line_vector(p2 - p1) {
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

    Point3D at(float t)
    {
        return point1 + line_vector * t;
    }

    float l_s_intersection(Sphere &s)
    {

        float i, j, k, u, v, w, a, b, c, r, dois = 2;

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

        float A = u * u + v * v + w * w, B = dois * (i * u + j * v + k * w - a * i - a * u - b * j - b * v * -c * k - c * w), C = i * i + j * j + k * k + a * a + b * b + c * c - r * r;

        float DELTA = B * B - 4 * A * C;
        if(DELTA<0){
            return -1;
        }

        float t1 = (-1 * B + sqrt(B * B - 4 * A * C)) / (2 * A);
        float t2 = (-1 * B - sqrt(B * B - 4 * A * C)) / (2 * A);

        std::cout << "t1 = " << t1 << " t2 = " << t2 << std::endl;

        if (t1 >= 0 && t1 <= abs(t2))
        {
            return t1;
        }
        return t2;

    }

    float l_p_intersection(Plane &p)
    {
        float x0, y0, z0, a, b, c, i, j, k, u, v, w;

        x0 = p.point.getX();
        y0 = p.point.getY();
        z0 = p.point.getZ();

        a = p.normal.getX();
        b = p.normal.getY();
        a = p.normal.getZ();

        i = point1.getX();
        j = point1.getY();
        k = point1.getZ();

        u = line_vector.getX();
        v = line_vector.getY();
        w = line_vector.getZ();

        float t = -1 * ((a * i + b * j + c * k) + (-a * x0 - b * y0 - c * z0)) / (a * u + b * v + c * w);
        return t;
    }
};

#endif