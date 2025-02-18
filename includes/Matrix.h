#ifndef MATRIXHEADER
#define MATRIXHEADER

#include <iostream>
#include <vector>
#include <cmath>
#include "Vector.h"
#include "Point.h"

class Matrix4x4
{
public:
    std::vector<std::vector<double>> data;

    // Construtor padrão (identidade)
    Matrix4x4() : data(4, std::vector<double>(4, 0))
    {
        for (int i = 0; i < 4; i++)
            data[i][i] = 1;
    }

    // Construtor a partir de vetor bidimensional
    Matrix4x4(const std::vector<std::vector<double>> &values) : data(values) {}

    // Soma de matrizes
    Matrix4x4 operator+(const Matrix4x4 &other) const
    {
        Matrix4x4 result;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    // Subtração de matrizes
    Matrix4x4 operator-(const Matrix4x4 &other) const
    {
        Matrix4x4 result;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                result.data[i][j] = data[i][j] - other.data[i][j];
        return result;
    }

    Vector3D operator*(const Vector3D &vec) const
    {
        double x = data[0][0] * vec.x + data[0][1] * vec.y + data[0][2] * vec.z + data[0][3] * 0;
        double y = data[1][0] * vec.x + data[1][1] * vec.y + data[1][2] * vec.z + data[1][3] * 0;
        double z = data[2][0] * vec.x + data[2][1] * vec.y + data[2][2] * vec.z + data[2][3] * 0;
        return Vector3D(x, y, z);
    }
    // Multiplicação de matriz por ponto 3D (convertendo para coordenadas homogêneas)
    Point3D operator*(const Point3D &pt) const
    {
        double x = data[0][0] * pt.x + data[0][1] * pt.y + data[0][2] * pt.z + data[0][3];
        double y = data[1][0] * pt.x + data[1][1] * pt.y + data[1][2] * pt.z + data[1][3];
        double z = data[2][0] * pt.x + data[2][1] * pt.y + data[2][2] * pt.z + data[2][3];
        double w = data[3][0] * pt.x + data[3][1] * pt.y + data[3][2] * pt.z + data[3][3];
        
        if (w != 0) {
            x /= w;
            y /= w;
            z /= w;
        }
        return Point3D(x, y, z);
    }

    // Multiplicação de matrizes
    Matrix4x4 operator*(const Matrix4x4 &other) const
    {
        Matrix4x4 result;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                result.data[i][j] = 0;
                for (int k = 0; k < 4; k++)
                {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // Forma escalonada
    Matrix4x4 rowEchelonForm() const
    {
        Matrix4x4 result = *this;
        for (int i = 0; i < 4; i++)
        {
            if (result.data[i][i] == 0)
            {
                for (int j = i + 1; j < 4; j++)
                {
                    if (result.data[j][i] != 0)
                    {
                        std::swap(result.data[i], result.data[j]);
                        break;
                    }
                }
            }
            if (result.data[i][i] != 0)
            {
                for (int j = i + 1; j < 4; j++)
                {
                    double factor = result.data[j][i] / result.data[i][i];
                    for (int k = 0; k < 4; k++)
                        result.data[j][k] -= factor * result.data[i][k];
                }
            }
        }
        return result;
    }

    // Criar matriz de rotação
    Matrix4x4 rotationX(double angle)
    {
        Matrix4x4 rot;
        rot.data[1][1] = cos(angle);
        rot.data[1][2] = -sin(angle);
        rot.data[2][1] = sin(angle);
        rot.data[2][2] = cos(angle);
        return rot;
    }

    Matrix4x4 rotationY(double angle)
    {
        Matrix4x4 rot;
        rot.data[0][0] = cos(angle);
        rot.data[0][2] = sin(angle);
        rot.data[2][0] = -sin(angle);
        rot.data[2][2] = cos(angle);
        return rot;
    }

    Matrix4x4 rotationZ(double angle)
    {
        Matrix4x4 rot;
        rot.data[0][0] = cos(angle);
        rot.data[0][1] = -sin(angle);
        rot.data[1][0] = sin(angle);
        rot.data[1][1] = cos(angle);
        return rot;
    }

    // Reflexão em relação ao eixo X
    Matrix4x4 reflectionX()
    {
        return Matrix4x4({
            {1,  0,  0, 0},
            {0, -1,  0, 0},
            {0,  0, -1, 0},
            {0,  0,  0, 1}
        });
    }

    // Reflexão em relação ao eixo Y
    Matrix4x4 reflectionY()
    {
        return Matrix4x4({
            {-1, 0,  0, 0},
            { 0, 1,  0, 0},
            { 0, 0, -1, 0},
            { 0, 0,  0, 1}
        });
    }

    // Reflexão em relação ao eixo Z
    Matrix4x4 reflectionZ()
    {
        return Matrix4x4({
            {-1,  0, 0, 0},
            { 0, -1, 0, 0},
            { 0,  0, 1, 0},
            { 0,  0, 0, 1}
        });
    }

    // Translação por (tx, ty, tz)
    Matrix4x4 translation(double tx, double ty, double tz)
    {
        return Matrix4x4({
            {1, 0, 0, tx},
            {0, 1, 0, ty},
            {0, 0, 1, tz},
            {0, 0, 0, 1}
        });
    }

    // Exibir matriz
    void print() const
    {
        for (const auto &row : data)
        {
            std::cout << "| ";
            for (double val : row)
            {
                std::cout << val << " ";
            }
            std::cout << "|\n";
        }
    }
};

#endif
