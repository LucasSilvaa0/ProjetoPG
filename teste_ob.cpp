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

    Scene *cena = new Scene();
 
    /*-----------------------------------------------------*/
 
    objReader obj("input/cubo.obj");
 
    /*-----------------------------------------------------*/
 
    obj.transladar(0, 1, 0);
    obj.rotacionar(0.78, 'y');
    obj.rotacionar(0.78, 'z');
    cena->addObj(obj);
 
    /*-----------------------------------------------------*/
 
    Camera camera = Camera(Point3D(-10, 0, 0), Point3D(1, 0, 0), (double)1, 500, 500, cena);
 
    /*-----------------------------------------------------*/
 
    auto palao = camera.render();
 
    /*-----------------------------------------------------*/
    int count = 0;
 
    Renderer window = Renderer(500,500,palao);
 
    window.run();

    return 0;
}
