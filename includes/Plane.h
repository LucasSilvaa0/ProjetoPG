#ifndef PLANEHEADER
#define PLANEHEADER

#include <iostream>
#include "Point.h"
#include "Vector.h"
#include "Matrix.h"

class Plane
{
public:
    Point3D point;   // Ponto
    Vector3D normal; // Vetor normal
    Vector3D cor;

    Plane(Point3D point, Vector3D normal, int R, int G, int B) : point(point), normal(normal)
    {
        this->normal.normalize();
        cor = Vector3D(R / (double)255, G / (double)255, B / (double)255);
    }

    void print() const
    {
        std::cout << "Plane:\n";
        std::cout << "  Point: ";
        point.print();
        std::cout << "  Normal Vector: ";
        normal.print();
    }

    void transladar(double x, double y, double z)
    {
        point.x += x;
        point.y += y;
        point.z += z;
    }

    void rotacionar(double angle, char axis)
    {
        Matrix4x4 r;

        if (axis == 'x')
        {
            r = Matrix4x4().rotationX(angle);
        }
        else if (axis == 'y')
        {
            r = Matrix4x4().rotationY(angle);
        }
        else if (axis == 'z')
        {
            r = Matrix4x4().rotationZ(angle);
        }

        normal = r * normal;
    }
};

#endif
