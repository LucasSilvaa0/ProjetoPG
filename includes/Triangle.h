#ifndef TRIANGLEHEADER
#define TRIANGLEHEADER

#include "Point.h"
#include "Vector.h"
#include "Line.h"

class Triangle
{
public:
    Point3D v0, v1, v2; // Vértices do triângulo
    Vector3D cor;        // Cor do triângulo (RGB normalizado)
    Vector3D normal_v0, normal_v1, normal_v2;

    // Construtor
    Triangle(Point3D &vertice0, Point3D &vertice1, Point3D &vertice2, Vector3D& normal1, Vector3D& normal2, Vector3D& normal3, double R, double G, double B)
        : v0(vertice0), v1(vertice1), v2(vertice2), normal_v0(normal1), normal_v1(normal2), normal_v2(normal3)
    {
        cor = Vector3D(R, G, B);
    }

    // Calcula o vetor normal do triângulo
    Vector3D NormalVector()
    {
        Vector3D edge1 = v1 - v0; // Vetor do vértice 0 ao vértice 1
        Vector3D edge2 = v2 - v0; // Vetor do vértice 0 ao vértice 2
        Vector3D normal = edge1.cross(edge2); // Produto vetorial para obter a normal
        normal.normalize(); // Normaliza o vetor
        return normal;
    }

    /* Calcula o vetor de reflexão
    Vector3D ReflectionVector(Vector3D &D, const Vector3D &N)
    {
        //double produtoEscalar = N.dot(D);
        //return Vector3D(D - (N * double(2 * produtoEscalar)));
    }
    */

    
};

#endif