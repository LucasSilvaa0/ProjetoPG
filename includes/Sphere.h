#ifndef SPHEREHEADER
#define SPHEREHEADER

#include "Point.h"
#include "Vector.h"

class Sphere
{
public:
    Point3D C; // Centro
    float r;   // Raio

    Sphere(Point3D &centro, float raio = 0) : C(centro), r(raio) {}

    // Criação do vetor normal da esfera com o ponto de intercessão de uma linha
    Vector3D NormalVector(const Point3D &p)
    {
        return Vector3D(p.getX() - C.x, p.getY() - C.y, p.getZ() - C.z);
    };

    // Cálculo do vetor de reflexão de uma linha com a esfera
    Vector3D ReflectionVector(Vector3D &D, const Vector3D &N)
    {
        float produtoEscalar = (N % D);
        return (D - D * float(2 * produtoEscalar));
    };
};

#endif