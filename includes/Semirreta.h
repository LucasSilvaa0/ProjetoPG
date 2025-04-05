#ifndef SEMIRRETA_H
#define SEMIRRETA_H

#include "Point.h"
#include "Vector.h"

class Semirreta
{
public:
    Point3D point1; // Primeiro ponto da semirreta
    Point3D point2; // Último ponto da semirreta

    Semirreta(Point3D p1, Point3D p2)
    {
        point1 = p1;
        point2 = p2;
    }

    void print() const
    {
        std::cout << "Semirreta:\n";
        std::cout << "  Point 1: ";
        point1.print();
        std::cout << "  Point 2: ";
        point2.print();
    }

    bool sr_sr_intersection(Semirreta sr2) const
    {
        double x0 = point1.getX();
        double y0 = point1.getY();
        double z0 = point1.getZ();

        double a = point2.x - point1.x;
        double b = point2.y - point1.y;
        double c = point2.z - point1.z;

        double i = sr2.point1.getX();
        double j = sr2.point1.getY();
        double k = sr2.point1.getZ();

        double u = sr2.point2.getX() - sr2.point1.getX();
        double v = sr2.point2.getY() - sr2.point1.getY();
        double w = sr2.point2.getZ() - sr2.point1.getZ();

        Vector3D v1 = Vector3D(point2 - point1);
        Vector3D v2 = Vector3D(sr2.point2 - sr2.point1);
        Vector3D verificacaoalinhamento = Vector3D(sr2.point1 - point1);
        verificacaoalinhamento.normalize();
        v2.normalize();

        if (v1.cross(v2).magnitude() == 0 && verificacaoalinhamento.cross(v2).magnitude() != 0)
            return false;

        double denominador = (a * v - b * u);
        if (b == 0 || denominador == 0)
            return false;
        double t2 = ((a * y0 + b * i - a * j - b * x0) / denominador);
        double t1 = ((j + v * t2 - y0) / b);

        double x1 = x0 + a * t1;
        double x2 = i + u * t2;

        double y1 = y0 + b * t1;
        double y2 = j + v * t2;

        double z1 = z0 + c * t1;
        double z2 = k + w * t2;

        if (x1 == x2 && y1 == y2 && z1 == z2 && t1 >= 0 && t2 >= 0 && t1 <= 1 && t2 <= 1 ||
            (((x0 >= sr2.point1.x && x0 <= sr2.point2.x) || (x0 <= sr2.point1.x && x0 >= sr2.point2.x)) &&
             ((y0 >= sr2.point1.y && y0 <= sr2.point2.y) || (y0 <= sr2.point1.y && y0 >= sr2.point2.y)) &&
             ((z0 >= sr2.point1.z && z0 <= sr2.point2.z) || (z0 <= sr2.point1.z && z0 >= sr2.point2.z))))
        {
            return true;
        }

        return false;
    }
};

#endif