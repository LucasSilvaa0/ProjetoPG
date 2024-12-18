#include <iostream>
#include "includes/Point.h"
#include "includes/Plane.h"
#include "includes/Vector.h"
#include "includes/Sphere.h"
#include "includes/Line.h"
#include "includes/Camera.h"
#include "includes/Scene.h"

int main()
{

    Scene *cena = new Scene();

    Point3D centro1 = Point3D(200, 22, 40);
    Point3D centro2 = Point3D(200, 22, -40);
    Point3D centro3 = Point3D(200, -25, 0);

    Sphere palao = Sphere(centro1, (float)35);
    Sphere henrique = Sphere(centro2, (float)35);
    Sphere paulo = Sphere(centro3, (float)35);

    cena->esferas.push_back(palao);
    cena->esferas.push_back(henrique);
    cena->esferas.push_back(paulo);

    Camera camera = Camera(Point3D(0, 0, 0), Point3D(1, 0, 0), (float)2, 60, 15, cena);

    camera.render();

    return 0;
}
