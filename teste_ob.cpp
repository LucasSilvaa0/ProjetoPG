#include <iostream>
#include "includes/Point.h"
#include "includes/Plane.h"
#include "includes/Vector.h"
#include "includes/Sphere.h"
#include "includes/Line.h"
#include "includes/Camera.h"
#include "includes/Scene.h"
#include "includes/objetificador.h"
#include "includes/Renderer.h"

int main()
{
    objReader *obj = new objReader("input/cubo.obj");
    Camera camera = Camera(Point3D(-10, 0, 0), Point3D(0, 0, 0), (double)1, 800, 600);
    Scene *cena = new Scene();

    obj->transladar(0, 0, 2.9);

    cena->objetos.push_back(obj);

    Point3D pc = Point3D(0, 0, 0);
    Sphere *esfera = new Sphere(pc, 1, 0, 255, 0);
    cena->esferas.push_back(esfera);

    auto antes = camera.render(cena);
    Renderer windowA = Renderer(800, 600, antes); // ANTES

    esfera->transladar(1, 0, 0);
    obj->refletir('x');
    obj->transladar(0.005, 0, 0);

    auto depois = camera.render(cena);
    Renderer windowD = Renderer(800, 600, depois); // DEPOIS

    windowA.run(); // ANTES
    windowD.run(); // DEPOIS

    return 0;
}
