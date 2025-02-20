#ifndef SCENE_H
#define SCENE_H

#include "Plane.h"
#include "Sphere.h"
#include "Vector.h"
#include "Point.h"
#include "Triangle.h"
#include "objetificador.h"
#include <vector>
#include <map>

class Scene
{
public:
    std::vector<Plane> planos;
    std::vector<Sphere> esferas;
    std::vector<Triangle> triangulos;

    void addObj(objReader &objeto)
    {
        for (Face face : objeto.getFaces())
        {
            Triangle teste = objeto.faceToTriangulo(face);

            triangulos.push_back(teste);
        }
    }
};

#endif