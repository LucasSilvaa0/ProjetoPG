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
    objReader obj("input/cubo.obj");

    Camera camera = Camera(Point3D(-10, 0, 0), Point3D(1, 0, 0), (double)1, 800, 600);

    /*-----------------------------------------------------*/

    Scene *cenaA = new Scene();

    /*-----------------------------------------------------*/

    obj.transladar(0, 0, 1);

    /*-----------------------------------------------------*/

    cenaA->addObj(obj);
    auto antes = camera.render(cenaA);
    Renderer windowA = Renderer(800, 600, antes);

    /*-----------------------------------------------------*/
    /*-----------------------------------------------------*/
    /*-----------------------------------------------------*/
    /*-----------------------------------------------------*/
    /*-----------------------------------------------------*/

    Scene *cenaD = new Scene();

    /*-----------------------------------------------------*/

    obj.refletir('x');

    /*-----------------------------------------------------*/

    cenaD->addObj(obj);
    auto depois = camera.render(cenaD);
    Renderer windowD = Renderer(800, 600, depois);

    /*-----------------------------------------------------*/
    /*-----------------------------------------------------*/
    /*-----------------------------------------------------*/
    /*-----------------------------------------------------*/
    /*-----------------------------------------------------*/

    windowA.run(); // ANTES
    windowD.run(); // DEPOIS

    return 0;
}
