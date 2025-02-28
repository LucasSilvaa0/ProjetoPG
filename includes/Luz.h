#ifndef LUZHEADER
#define LUZHEADER

#include "Point.h"
#include "Vector.h"
#include "Line.h"

class Luz
{
public:
    Point3D p;    // Vértices do triângulo
    Vector3D cor; // Cor do triângulo (RGB normalizado)

    // Construtor
    Luz(Point3D p, double R, double G, double B)
    {
        this->p = p;
        cor = Vector3D(R, G, B);
    }
};

#endif