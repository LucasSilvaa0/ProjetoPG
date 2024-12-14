#include <Point.h>
#include <Plane.cpp>
#include <Vector.cpp>
#include <Sphere.cpp>
#include <Line.cpp>

int main() {

    Point3D x = Point3D(0,0,0);
    Vector3D norm = Vector3D(1,0,0);
    Point3D p1 = Point3D(0,0,0);
    Point3D p2 = Point3D(0,1,0);
    Plane plano = Plane(x,norm);
    Line linha = Line(p1,p2);
    auto t = linha.l_p_intersection(plano);
    auto intersec = linha.at(t);

    return 0;
}
