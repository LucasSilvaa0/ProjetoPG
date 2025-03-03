#include "includes/Vector.h"

int main()
{
    Vector3D v = Vector3D(5, -3, 2);
    v.normalize();

    Vector3D N = Vector3D(1, 1, 1);
    N.normalize();

    Vector3D r = v.refletir(N);
    r.print();

    return 1;
}