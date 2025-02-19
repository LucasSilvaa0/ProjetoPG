#ifndef SCENE_H
#define SCENE_H

#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include <vector>

class Scene{
public:
    std::vector<Plane> planos;
    std::vector<Sphere> esferas;
    std::vector<Triangle> triangulos;
};

#endif