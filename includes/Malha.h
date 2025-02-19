#ifndef MALHAHEADER
#define MALHAHEADER

#include "Point.h"
#include "Vector.h"
#include "Line.h"
#include "Triangle.h"
#include <vector>
#include <tuple>


class Malha
{
public:
    
    int numero_triangulos;
    int numero_vertices;
    std::vector<Point3D> vertices;
    std::vector<std::tuple<int,int,int>> indices_triangulo;
    std::vector<Triangle> triangulos;
    std::vector<Vector3D> normais_triangulo;
    std::vector<Vector3D> normais_vertices;
    Vector3D cor;

    // Construtor
    Malha(
        
        int numero_triangulos, int numero_vertices, 
        std::vector<Point3D> &vertices, 
        std::vector<std::tuple<int,int,int>> &indices_triangulo,
        std::vector<Vector3D>& normais_triangulo,
        int R, int G, int B

        )

        :

        numero_triangulos(numero_triangulos),
        numero_vertices(numero_vertices),
        vertices(vertices), 
        indices_triangulo(indices_triangulo),
        normais_triangulo(normais_triangulo)

        {

            cor = Vector3D(R / (double)255, G / (double)255, B / (double)255);
            for(auto tupla : indices_triangulo){
                triangulos.push_back(

                    Triangle(vertices[std::get<0>(tupla)],
                    vertices[std::get<1>(tupla)],
                    vertices[std::get<2>(tupla)], 
                    cor.x, cor.y, cor.z)

                );
            }

        }


    
};

#endif