#ifndef SPHEREHEADER
#define SPHEREHEADER

#include "Point.h"
#include "Vector.h"
#include "Colormap.h"

class Sphere
{
public:
    Point3D C; // Centro
    double r;  // Raio

    MaterialProperties material;

    Sphere(Point3D &centro, double raio, double R, double G, double B) : C(centro), r(raio)
    {
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