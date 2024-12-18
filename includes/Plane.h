#ifndef PLANEHEADER
#define PLANEHEADER

#include <iostream>
#include "Point.h"
#include "Vector.h"

class Plane
{
public:
    Point3D point;   // Ponto
    Vector3D normal; // Vetor normal
    Vector3D cor;

    Plane(Point3D point, Vector3D normal, int R, int G, int B) : point(point), normal(normal)
    {
        this->normal.normalize();
        cor = Vector3D(R/(double)255, G/(double)255, B/(double)255);
    }

    void print() const
    {
        std::cout << "Plane:\n";
        std::cout << "  Point: ";
        point.print();
        std::cout << "  Normal Vector: ";
        normal.print();
    }
};

#endif
