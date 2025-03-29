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
    int height = 1000;
    int width = 1000;
    objReader *obj = new objReader("input/cubo.obj");
    // objReader *obj2 = new objReader("input/cubo.obj");
    Camera camera = Camera(Point3D(-120, 60, 0), Point3D(0, 0, 0), (double)10, height, width);
    Scene *cena = new Scene(Vector3D(0.2, 0.2, 0.2));
    Luz *luz = new Luz(Point3D(2, 30, 0), 0.2, 0.2, 0.2);
    // Luz *luz2 = new Luz(Point3D(0, 0, -10), 0, 0.3, 0.3);
    Plane *plano = new Plane(Point3D(20, 0, 0), Vector3D(1, 0, 0));
    Plane *teto = new Plane(Point3D(20, 200, 0), Vector3D(0, 1, 0));
    Plane *plano3 = new Plane(Point3D(-200, 0, 0), Vector3D(1, 0, 0));

    Plane *chao = new Plane(Point3D(0, -3, 0), Vector3D(0, 1, 0));
    chao->material.ka = chao->material.kd = Vector3D(1, 0, 0);

    Point3D ce = Point3D(3.5, -2.5, 2);
    Sphere *esfera = new Sphere(ce, 2);
    esfera->material.d = 0.4;

    cena->objetos.push_back(obj);
    cena->luzes.push_back(luz);
    cena->planos.push_back(plano);
    cena->planos.push_back(teto);
    cena->esferas.push_back(esfera);
    cena->planos.push_back(chao);
    // cena->luzes.push_back(luz2);

    // obj->escalar(2);
    obj->rotacionar(0.7, 'y');

    // obj2->escalar(2);
    // obj2->transladar(5, -3, 0);
    // obj2->rotacionar(-0.7, 'z');
    // obj2->rotacionar(0.7, 'y');

    cena->planos.push_back(plano3);
    obj->curMaterial.ks = esfera->material.ks = plano->material.kd = plano->material.ka = plano3->material.kd = plano3->material.ka = Vector3D(0.1, 0.1, 0.1);
    plano->material.ks = plano3->material.ks = Vector3D(1, 1, 1);

    auto antes = camera.render(cena);
    Renderer windowA = Renderer(height, width, antes, "Antes"); // ANTES

    // cena->planos.pop_back();
    // auto depois = camera.render(cena);
    // Renderer windowB = Renderer(height, width, depois, "Depois"); // depois

    windowA.run(); // ANTES
    // windowB.run(); // Depois

    return 0;
}