#ifndef SCENE_H
#define SCENE_H

#include "Plane.h"
#include "Sphere.h"
#include "Vector.h"
#include "Point.h"
#include "Triangle.h"
#include "objetificador.h"
#include "Luz.h"
#include <vector>
#include <map>

class Scene
{
public:
    std::vector<Plane *> planos;
    std::vector<Sphere *> esferas;
    std::vector<Triangle *> triangulos;
    std::vector<objReader *> objetos;
    std::vector<Luz *> luzes;
    colormap cmap;

    Vector3D Ia;

    Scene(Vector3D Ia) { this->Ia = Ia; }
};

#endif