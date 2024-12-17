#include <iostream>
#include "includes/Point.h"
#include "includes/Plane.h"
#include "includes/Vector.h"
#include "includes/Sphere.h"
#include "includes/Line.h"

int main()
{

    Point3D p = Point3D(0, 0, 0);

    Sphere s = Sphere(p, 1);

    Point3D p1 = Point3D(1, 1, 0);
    Point3D p2 = Point3D(2, 2, 1);

    Line l = Line(p1, p2);
    float t = l.l_s_intersection(s);
    Point3D intersec = l.at(t);

    std::cout << t << "\n";

    intersec.print();

    // Vector3D R = s.ReflectionVector(v1, s.NormalVector(p2));

    // R.print();

    /*
    Point3D x = Point3D(0, 0, 0);
    Vector3D norm = Vector3D(1, 0, 0);
    Point3D p1 = Point3D(0, 0, 0);
    Point3D p2 = Point3D(0, 1, 0);
    Plane plano = Plane(x, norm);
    Line linha = Line(p1, p2);
    auto t = linha.l_p_intersection(plano);
    auto intersec = linha.at(t);
    */

    return 0;
}
