#ifndef SPHEREHEADER
#define SPHEREHEADER

#include <Point.cpp>

class Sphere {
public:
    Point3D C; //Centro
    float r; //Raio

    Sphere(Point3D& centro, float raio = 0) : C(centro), r(raio) {}

};

#endif