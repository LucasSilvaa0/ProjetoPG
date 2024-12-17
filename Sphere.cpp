#ifndef SPHEREHEADER
#define SPHEREHEADER

#include <Point.cpp>
#include <Vector.cpp>

class Sphere
{
public:
    Point3D C; // Centro
    float r;   // Raio

    Sphere(Point3D &centro, float raio = 0) : C(centro), r(raio) {}

    // Criação do vetor normal da esfera com o ponto de intercessão de uma linha
    Vector3D NormalVector(Point3D &p)
    {
        return Vector3D(p.getX() - C.x, p.getY() - C.y, p.getZ() - C.z);
    };

    // Cálculo do vetor de reflexão de uma linha com a esfera
    Vector3D ReflectionVector(Vector3D &D, Vector3D &N)
    {
        return (D - (float(2) * (N * D)) * D);
    };
};

#endif