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
    int height = 800;
    int width = 800;
    Camera camera = Camera(Point3D(-90, 90, -10), Point3D(7, 0, 0.8), (double)8, height, width);
    Scene *cena = new Scene(Vector3D(0.1, 0.2, 0.1));
    Luz *luz = new Luz(Point3D(-20, 10, 5), 0.1, 0.2, 0.1);
    RetanguloIluminado *retangulo = new RetanguloIluminado(2, 5, Vector3D(1, -1, 0), Vector3D(1, -1, 0), Vector3D(0.3, 0.3, 0.3));
    retangulo->transladar(-30, 40, -2);
    cena->retangulosiluminados.push_back(retangulo);

    Plane *chao = new Plane(Point3D(0, 0, 0), Vector3D(0, 1, 0));
    chao->material.ka = chao->material.kd = Vector3D(1, 0, 0);
    chao->material.d = 1;
    Plane *teto = new Plane(Point3D(0, 200, 0), Vector3D(0, 1, 0));
    chao->material.ka = chao->material.kd = Vector3D(1, 0, 0);
    chao->material.d = 1;

    Point3D ce = Point3D(4, 0.7, 0);
    Sphere *esfera = new Sphere(ce, 2);
    esfera->material.ka = esfera->material.kd = Vector3D(0, 0.5, 0);

    cena->luzes.push_back(luz);
    cena->esferas.push_back(esfera);
    cena->planos.push_back(chao);
    cena->planos.push_back(teto);

    auto antes = camera.render(cena);
    Renderer windowA = Renderer(height, width, antes, "Antes"); // ANTES

    windowA.run(); // ANTES

    return 0;
}