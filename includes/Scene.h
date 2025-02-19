#ifndef SCENE_H
#define SCENE_H

#include "Plane.h"
#include "Sphere.h"
#include "Vector.h"
#include "Point.h"
#include "Triangle.h"
#include <vector>
#include <map>

class Scene{
public:

    // normal_ponto[ponto]=(normal_ponto[ponto]*qtd_average_ponto[ponto] + vetor_normal_novo)/(qtd_average_ponto[ponto]+1)
    
    std::map<Point3D,Vector3D> normal_ponto;
    std::map<Point3D,int> qtd_average_ponto;
    std::vector<Plane> planos;
    std::vector<Sphere> esferas;
    std::vector<Triangle> triangulos;
};

#endif