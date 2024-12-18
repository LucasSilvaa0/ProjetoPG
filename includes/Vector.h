#ifndef VECTORHEADER
#define VECTORHEADER
#include <iostream>
#include <math.h>

class Vector3D
{
public:
    // Valores
    double x, y, z;

    // Constructor
    Vector3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

    // Operações
    Vector3D operator+(const Vector3D &other) const
    {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    Vector3D operator-(const Vector3D &other) const
    {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    Vector3D operator*(const double scalar)
    {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    double operator%(const Vector3D &other) const
    {
        return (other.x * x + other.y * y + other.z * z);
    }

    double dot(const Vector3D &other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3D cross(const Vector3D &other) const
    {
        return Vector3D(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x);
    }

    double magnitude() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    void normalize()
    {
        double mag = magnitude();
        if (mag > 0)
        {
            x /= mag;
            y /= mag;
            z /= mag;
        }
    }

    // Print
    void print() const
    {
        std::cout << "Vector3D(" << x << ", " << y << ", " << z << ")\n";
    }

    // Getters
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }
};

#endif