#ifndef SPHEREHEADER
#define SPHEREHEADER

#include "Point.h"
#include "Vector.h"

class Sphere
{
public:
    Point3D C; // Centro
    double r;  // Raio
    Vector3D cor;

    Sphere(Point3D &centro, double raio, int R, int G, int B) : C(centro), r(raio)
    {
        cor = Vector3D(R / (double)255, G / (double)255, B / (double)255);
    }

    Vector3D NormalVector(const Point3D &p)
    {
        Vector3D v = Vector3D(p.getX() - C.x, p.getY() - C.y, p.getZ() - C.z);
        v.normalize();
        return v;
    };

    Vector3D ReflectionVector(Vector3D &D, const Vector3D &N)
    {
        double produtoEscalar = (N.dot(D));
        return Vector3D(D - (D * double(2 * produtoEscalar)));
    };

    void transladar(double x, double y, double z)
    {
        C = Point3D(C.getX() + x, C.getY() + y, C.getZ() + z);
    }

    void escalar(double x)
    {
        r = r * x;
    }
};

#endif