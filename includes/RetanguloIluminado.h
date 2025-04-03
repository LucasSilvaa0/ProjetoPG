#ifndef RETANGULOILUMINADOHEADER
#define RETANGULOILUMINADOHEADER

#include <iostream>
#include "Point.h"
#include "Vector.h"
#include "Matrix.h"
#include "Colormap.h"

class RetanguloIluminado
{
public:
    Point3D p1;
    Point3D p2;
    Point3D p3;
    Point3D p4;
    Vector3D normal;
    Vector3D direcao;
    Vector3D color;

    RetanguloIluminado(Point3D p1, Point3D p3, Vector3D normal, Vector3D direcao, Vector3D color)
    {
        this->normal = normal;
        this->normal.normalize();
        this->color = color;
        this->p1 = p1;
        this->p3 = p3;
        this->direcao = direcao;

        this->calcularPontos();
    }

    void print() const
    {
        std::cout << "RETANGULOILUMINADO:\n";
        std::cout << "  Point 1: ";
        p1.print();
        std::cout << "  Point 2: ";
        p2.print();
        std::cout << "  Point 3: ";
        p3.print();
        std::cout << "  Point 4: ";
        p4.print();
        std::cout << "  Normal Vector: ";
        normal.print();
        std::cout << "  Light Vector: ";
        direcao.print();
    }

    void calcularPontos()
    {
        // Calcular os outros dois pontos do retângulo
        Vector3D v1 = p3 - p1;
        Point3D centro_retangulo = p1 + v1 * 0.5;

        double escalar = v1.magnitude();
        v1.normalize();

        Vector3D v2 = v1.cross(normal);

        v2 = v2 * escalar;

        p2 = centro_retangulo + v2 * (-0.5);
        p4 = centro_retangulo + v2 * 0.5;
    }

    void transladar(double x, double y, double z)
    {
        p1.x += x;
        p2.x += x;
        p3.x += x;
        p4.x += x;
        p1.y += y;
        p2.y += y;
        p3.y += y;
        p4.y += y;
        p1.z += z;
        p2.z += z;
        p3.z += z;
        p4.z += z;
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
