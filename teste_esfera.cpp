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


    Point3D centro3 = Point3D(7, 0, 0);
    
    Sphere palao3 = Sphere(centro3, (double)1, 0,0,255);

    cena->esferas.push_back(palao3);

    Camera camera = Camera(Point3D(0, 0, 0), Point3D(1, 0, 0), (double)2, 10, 10, cena);

    camera.render("esfera.ppm");

    return 0;
}
