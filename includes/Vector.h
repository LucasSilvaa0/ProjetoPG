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

    Vector3D operator*(double scalar) const
    {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    double dot(const Vector3D &other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    float cos(const Vector3D &other) const
    {

        return (other.dot(*this)) / (this->magnitude() * other.magnitude());
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

    Vector3D refletir(Vector3D *N) const
    {
        double cos = (N->dot(*this));
        Vector3D r = Vector3D(*this - ((Vector3D(N->x, N->y, N->z) * cos) * 2));

        return r;
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