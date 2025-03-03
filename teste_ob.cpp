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
    Scene *cena = new Scene(Vector3D(0, 0, 0.2));
    Luz *luz = new Luz(Point3D(5, 0, 2), 1, 0, 0);
    Luz *luz2 = new Luz(Point3D(0, 0, 0), 1, 0, 0);

    cena->objetos.push_back(obj);
    cena->luzes.push_back(luz);

    obj->escalar(2);
    obj->transladar(5, 4, 2);
    obj->rotacionar(0.7, 'y');

    auto antes = camera.render(cena);
    Renderer windowA = Renderer(800, 600, antes, "Antes"); // ANTES

    cena->luzes.push_back(luz2);

    auto depois = camera.render(cena);
    Renderer windowD = Renderer(800, 600, depois, "Depois"); // DEPOIS

    windowA.run(); // ANTES
    windowD.run(); // DEPOIS

    return 0;
}
