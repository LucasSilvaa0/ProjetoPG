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
    Scene *cena = new Scene(Vector3D(0.2, 0.2, 0.2));
    Luz *luz = new Luz(Point3D(5, 0, 2), 1, 0, 0);

    cena->objetos.push_back(obj);
    cena->luzes.push_back(luz);

    obj->escalar(2);
    obj->transladar(5, 4, 2);

    auto antes = camera.render(cena);
    Renderer windowA = Renderer(800, 600, antes, "Antes"); // ANTES

    windowA.run(); // ANTES

    return 0;
}
