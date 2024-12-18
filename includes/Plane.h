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
    
    Plane(Point3D point, Vector3D normal) : point(point), normal(normal)
    {
        this->normal.normalize();
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
