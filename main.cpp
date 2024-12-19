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

    Point3D centro1 = Point3D(200, 0, 20);
    Point3D centro2 = Point3D(200, 0, -20);
    Point3D centro3 = Point3D(150, 0, 0);
    

    Sphere palao1 = Sphere(centro1, (double)25, 255,0,0);
    Sphere palao2 = Sphere(centro2, (double)25, 0,0,255);
    Sphere palao3 = Sphere(centro3, (double)12.5, 0,255,0);

    cena->esferas.push_back(palao1);cena->esferas.push_back(palao2); cena->esferas.push_back(palao3);

    Camera camera = Camera(Point3D(0, 0, 0), Point3D(1, 0, 0), (double)2, 1000, 1000, cena);

    camera.render();

    return 0;
}
