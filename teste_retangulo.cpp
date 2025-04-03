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
    RetanguloIluminado r = RetanguloIluminado(Point3D(0, 0, 0), Point3D(1, 1, 0), Vector3D(0, 0, 1), Vector3D(1, 0 0), Vector3D(1, 0, 0));
    r.print();

    return 0;
}
