#include <iostream>
#include "includes/Point.h"
#include "includes/Plane.h"
#include "includes/Vector.h"
#include "includes/Sphere.h"
#include "includes/Line.h"
#include "includes/Camera.h"

int main()
{

    Camera camera = Camera(Point3D(0,0,0),Point3D(1,0,0),(float)1,(float)1,(float)1);

    return 0;
}
