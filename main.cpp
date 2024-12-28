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

    Point3D centro1 = Point3D(200, 0, 0);

    Sphere palao1 = Sphere(centro1, (double)25, 255, 0, 0);

    Point3D point = Point3D(200, 0, 0);
    Vector3D normal = Vector3D(-1, 0, 0);

    cena->esferas.push_back(palao1);

    Camera camera = Camera(Point3D(0, 0, 0), Point3D(1, 0, 0), (double)5, 1000, 1000, cena);

    camera.render("palao.ppm");

    return 0;
}
