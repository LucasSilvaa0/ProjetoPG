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

    cena->objetos.push_back(obj);

    obj->transladar(0, 2, 0);

    Plane *plano = new Plane(Point3D(0, 0, 0), Vector3D(-1, 0, -1), 0, 0, 255);

    cena->planos.push_back(plano);

    auto antes = camera.render(cena);
    Renderer windowA = Renderer(800, 600, antes); // ANTES

    plano->rotacionar(1.57, 'y');

    auto depois = camera.render(cena);
    Renderer windowD = Renderer(800, 600, depois); // DEPOIS

    windowA.run(); // ANTES
    windowD.run(); // DEPOIS

    return 0;
}
