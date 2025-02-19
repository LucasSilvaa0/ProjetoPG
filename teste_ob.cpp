#include <iostream>
#include "includes/Point.h"
#include "includes/Plane.h"
#include "includes/Vector.h"
#include "includes/Sphere.h"
#include "includes/Line.h"
#include "includes/Camera.h"
#include "includes/Scene.h"
#include "objreader.cpp"

int main()
{

    Scene *cena = new Scene();

    objReader obj("input/cubo.obj");


    Camera camera = Camera(Point3D(0, 0, 0), Point3D(1, 0, 0), (double)4, 500, 500, cena);

    camera.render("palao.ppm");

    return 0;
}
