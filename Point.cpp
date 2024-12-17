#ifndef POINTHEADER
#define POINTHEADER
#include <iostream>
#include <cmath>
#include <Vector.cpp>

class Point3D
{
public:
    // Valores
    float x, y, z;

    // Constructor
    Point3D(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    // Operações
    Vector3D operator-(const Point3D &other) const
    {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    Point3D operator+(const Vector3D &vec) const
    {
        return Point3D(x + vec.x, y + vec.y, z + vec.z);
    }

    // Print
    void print() const
    {
        std::cout << "Point3D(" << x << ", " << y << ", " << z << ")\n";
    }

    // Getters
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }
};

#endif