#include <iostream>
#include "includes/Point.h"
#include "includes/Plane.h"
#include "includes/Vector.h"
#include "includes/Sphere.h"
#include "includes/Line.h"

int main()
{

    Point3D c = Point3D(0, 0, 0);

    Sphere s = Sphere(c, 5);

    Point3D p1 = Point3D(-8, 3, 0);
    Point3D p2 = Point3D(-4, 0, 0);

    Line l = Line(p1, p2);

    l.point1.print();
    l.line_vector.print();

    float t = l.l_s_intersection(s);
    Point3D intersec = l.at(t);

    Vector3D v = Vector3D(intersec.x, intersec.y, intersec.z);

    std::cout << t << "\n";

    v.normalize();
    intersec.print();
    v.print();

    Vector3D R = s.ReflectionVector(l.line_vector, s.NormalVector(intersec));

    R.print();

    return 0;
}
