#ifndef SCENE_H
#define SCENE_H

#include "Plane.h"
#include "Sphere.h"
#include "Vector.h"
#include "Point.h"
#include "Triangle.h"
#include "Malha.h"
#include <vector>
#include <map>

class Scene{
public:

    std::vector<Malha> malhas;
    std::vector<Plane> planos;
    std::vector<Sphere> esferas;
    std::vector<Triangle> triangulos;
    
};

#endif