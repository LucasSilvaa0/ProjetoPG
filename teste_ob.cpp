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
#include "includes/Luz.h"

int main()
{
    objReader *obj = new objReader("input/cubo.obj");
    Camera camera = Camera(Point3D(-12, 0, 0), Point3D(0, 0, 0), (double)1, 800, 600);
    Scene *cena = new Scene(Vector3D(0, 0, 0));
    Luz *luz = new Luz(Point3D(0, 7, 2), 1, 0, 1);
    Plane *plano = new Plane(Point3D(200, -200, 0), Vector3D(-1, 1, 0), 255, 255, 0);

    Point3D ce = Point3D(0, 0, 0);
    Sphere *esfera = new Sphere(ce, 2, 0, 0, 255);

    cena->objetos.push_back(obj);
    cena->luzes.push_back(luz);
    cena->planos.push_back(plano);
    cena->esferas.push_back(esfera);

    obj->escalar(2);
    obj->transladar(5, 4, 2);
    obj->rotacionar(0.7, 'y');

    auto antes = camera.render(cena);
    Renderer windowA = Renderer(800, 600, antes, "Antes"); // ANTES

    windowA.run(); // ANTES

    return 0;
}
