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

    Point3D centro = Point3D(200, 0, 0);

    Sphere palao = Sphere(centro, (float)50);

    cena->esferas.push_back(palao);

    Camera camera = Camera(Point3D(0, 0, 0), Point3D(1, 0, 0), (float)2.2, 20, 60, cena);

    camera.render();

    return 0;
}
