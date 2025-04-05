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

    RetanguloIluminado(double comprimento, double largura, Vector3D normal, Vector3D direcao, Vector3D color)
    {
        this->normal = normal;
        this->normal.normalize();
        this->color = color;
        this->direcao = direcao;

        this->calcularPontos(comprimento, largura);
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

    void calcularPontos(double comprimento, double largura)
    {
        this->p1 = Point3D(0, 0, 0);

        // Calcular os outros três pontos do retângulo
        Vector3D v1 = normal.cross(Vector3D(1, 0, 0));
        if (v1.magnitude() == 0)
            v1 = normal.cross(Vector3D(0, 1, 0));
        v1.normalize();

        Vector3D v2 = normal.cross(v1);
        v2.normalize();

        this->p2 = this->p1 + v1 * comprimento;
        this->p3 = this->p2 + v2 * largura;
        this->p4 = this->p1 + v2 * largura;
    }

    Point3D getP1()
    {
        return p1;
    }

    Point3D getP2()
    {
        return p2;
    }

    Point3D getP3()
    {
        return p3;
    }

    Point3D getP4()
    {
        return p4;
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

        direcao = r * direcao;
    }
};

#endif
