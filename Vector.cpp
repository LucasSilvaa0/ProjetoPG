#ifndef VECTORHEADER
#define VECTORHEADER
#include <iostream>
#include <math.h>

class Vector3D
{
public:
    // Valores
    float x, y, z;

    // Constructor
    Vector3D(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    // Operações
    Vector3D operator+(const Vector3D &other) const
    {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    Vector3D operator-(const Vector3D &other) const
    {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    float operator*(const Vector3D &other) const
    {
        return (other.x * x + other.y * y + other.z * z);
    }

    float dot(const Vector3D &other) const
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

    float magnitude() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    void normalize()
    {
        float mag = magnitude();
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

Vector3D operator*(const float scalar, const Vector3D &vector)
{
    return Vector3D(vector.x * scalar, vector.y * scalar, vector.z * scalar);
}

int main()
{
    Vector3D x;
    x = (float(5) * Vector3D(4, 5, 6));
    x.print();

    return 0;
}

#endif