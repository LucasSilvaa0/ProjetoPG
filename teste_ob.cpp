#include <iostream>
#include "includes/Point.h"
#include "includes/Plane.h"
#include "includes/Vector.h"
#include "includes/Sphere.h"
#include "includes/Line.h"
#include "includes/Camera.h"
#include "includes/Scene.h"
#include "objetificador.cpp"

int main()
{

    Scene *cena = new Scene();

    objReader obj("input/cubo.obj");

    obj.transladar(0,2,2);

    cena->addObj(obj);


    //obj.print_faces();

    Camera camera = Camera(Point3D(-10, 0, 0), Point3D(1, 0, 0), (double)1, 500, 500, cena);

    camera.render("palao.ppm");

    return 0;
}
