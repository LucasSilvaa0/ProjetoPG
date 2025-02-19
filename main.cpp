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

    Sphere palao1 = Sphere(centro1, (double)5, 255, 255, 0);

    Point3D v1 = Point3D(100,0,0);
    Point3D v2 = Point3D(100,15,0);
    Point3D v3 = Point3D(100,-15,10);

    

    cena->esferas.push_back(palao1);

    cena->triangulos.push_back(palao2);
    //cena->esferas.push_back(palao1);

    Camera camera = Camera(Point3D(0, 0, 0), Point3D(1, 0, 0), (double)4, 500, 500, cena);

    camera.render("palao.ppm");

    return 0;
}
