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
#include "includes/RetanguloIluminado.h"

int main()
{
    int height = 900;
    int width = 900;
    Camera camera = Camera(Point3D(-10, 5, 0), Point3D(-2, 0, 0), (double)1, height, width);
    Scene *cena = new Scene(Vector3D(0.1, 0.1, 0.1));

    Luz *luz = new Luz(Point3D(-5, 19, 0), 0.2, 0.2, 0.2);
    cena->luzes.push_back(luz);

    RetanguloIluminado *retangulo = new RetanguloIluminado(Point3D(-3, -3, -19.99), Point3D(3, 3, -19.99), Vector3D(0, 0, 1), Vector3D(0, 0, 1), Vector3D(0, 0.5, 0));
    cena->retangulosiluminados.push_back(retangulo);

    Plane *paredefrente = new Plane(Point3D(20, 0, 0), Vector3D(1, 0, 0));
    Plane *paredetraz = new Plane(Point3D(-20, 0, 0), Vector3D(1, 0, 0));
    Plane *paredeesquerda = new Plane(Point3D(0, 0, -20), Vector3D(0, 0, 1));
    Plane *parededireita = new Plane(Point3D(0, 0, 20), Vector3D(0, 0, 1));
    Plane *teto = new Plane(Point3D(0, 20, 0), Vector3D(0, 1, 0));
    Plane *piso = new Plane(Point3D(0, -5, 0), Vector3D(0, 1, 0));
    cena->planos.push_back(paredefrente);
    cena->planos.push_back(paredetraz);
    cena->planos.push_back(paredeesquerda);
    cena->planos.push_back(parededireita);
    cena->planos.push_back(teto);
    cena->planos.push_back(piso);

    objReader *cubo = new objReader("input/cubo.obj");
    cena->objetos.push_back(cubo);
    cubo->rotacionar(0.7, 'y');

    auto antes = camera.render(cena);
    Renderer windowA = Renderer(height, width, antes, "ANTES"); // ANTES

    windowA.run(); // ANTES

    return 0;
}