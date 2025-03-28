#ifndef PLANEHEADER
#define PLANEHEADER

#include <iostream>
#include "Point.h"
#include "Vector.h"
#include "Matrix.h"
#include "Colormap.h"

class Plane
{
public:
    Point3D point;   // Ponto
    Vector3D normal; // Vetor normal
    MaterialProperties material;

    Plane(Point3D point, Vector3D normal) : point(point), normal(normal)
    {
        this->normal.normalize();
        this->material.kd = Vector3D(0.5, 0.5, 0.5); // Difuso
        this->material.ks = Vector3D(0.5, 0.5, 0.5); // Specular
        this->material.ke = Vector3D(0.5, 0.5, 0.5); // Emissivo
        this->material.ka = Vector3D(0.5, 0.5, 0.5); // Ambiente
        this->material.ns = 0.5;                     // Brilho
        this->material.ni = 1;                       // Índice de refração
        this->material.d = 1;                        // Opacidade
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
