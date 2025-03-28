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
    int height = 600;
    int width = 600;
    objReader *obj = new objReader("input/cubo.obj");
    objReader *obj2 = new objReader("input/cubo.obj");
    Camera camera = Camera(Point3D(-12, 0, 0), Point3D(0, 0, 0), (double)1, height, width);
    Scene *cena = new Scene(Vector3D(0.8, 0.2, 0.2));
    Luz *luz = new Luz(Point3D(0, 10, 2), 0, 1, 0);
    Luz *luz2 = new Luz(Point3D(0, 0, -10), 0, 1, 0);

    Plane *plano = new Plane(Point3D(200, 0, 0), Vector3D(1, 0, 0));
    Sphere *esfera = new Sphere(Point3D(0, 0, 0), 2);

    Point3D ce = Point3D(0, 0, 0);

    plano->material.ka = Vector3D(0.1, 0.1, 0.1);

    // cena->objetos.push_back(obj);
    // cena->objetos.push_back(obj2);
    cena->luzes.push_back(luz);
    cena->esferas.push_back(esfera);
    esfera->material = obj->curMaterial;
    auto palao

        cena->planos.push_back(plano);

    obj->escalar(2);
    obj->transladar(5, 4, 2);
    obj->rotacionar(0.7, 'y');

    obj2->escalar(2);
    obj2->transladar(5, -3, 0);
    obj2->rotacionar(-0.7, 'z');
    obj2->rotacionar(0.7, 'y');

    auto antes = camera.render(cena);
    Renderer windowA = Renderer(height, width, antes, "Antes"); // ANTES

    windowA.run(); // ANTES

    return 0;
}
