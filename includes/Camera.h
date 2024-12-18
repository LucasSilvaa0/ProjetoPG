#ifndef CAMERAHEADER
#define CAMERAHEADER
#include "Point.h"
#include "Vector.h"
#include "Sphere.h"
#include "Line.h"
#include <iostream>

class Camera
{
public:
    Point3D C;        // Localização da câmera
    Point3D M;        // Ponto para onde a câmera aponta
    Vector3D Vup;     // Vetor para cima
    Vector3D W, U, V; // Vetores ortonormais
    Plane tela;
    Point3D centro_tela;
    Point3D topo_tela;
    Point3D esquerda_tela;
    Point3D primeiro_pixel;
    float d;          // Distância entre a câmera e a tela
    int w_res;        // Altura da tela
    int h_res;        // Largura da tela

    Camera(const Point3D C, const Point3D M, const float d, const int w_res, const int h_res)
        : C(C), M(M), d(d), w_res(w_res), h_res(h_res)
    {
        updateOrthonormalVectors();
        
        auto temp = M-C; temp = temp*(float)-1;

        std::tie(W,U,V) = gramSchmidt(temp);

        Vup = Vector3D(0,1,0);

        centro_tela = C+W*((float)-1*d);
        topo_tela = centro_tela+U;
        esquerda_tela = centro_tela+V;

    }

    std::tuple<Vector3D,Vector3D,Vector3D> gramSchmidt(Vector3D& v1){
    
        Vector3D u1 = v1;

        u1.normalize();


        Vector3D arbitraryVector = (u1.x != 0 || u1.y == 0) ? Vector3D(0, 1, 0) : Vector3D(1, 0, 0);

        Vector3D u2 = arbitraryVector - u1 * (arbitraryVector.dot(u1));

        u2.normalize();

        Vector3D u3 = u1.cross(u2);

        u3.normalize();

        return {u1,u2,u3};
    
    }

    void updateOrthonormalVectors()
    {
        W = C - M;
        W.normalize();
        U = Vup.cross(W);
        U.normalize();
        V = W.cross(U);
    }

    void print() const
    {
        std::cout << "Camera:\n";
        std::cout << "  Location: ";
        C.print();
        std::cout << "  Pointing to: ";
        M.print();
        std::cout << "  Up Vector: ";
        Vup.print();
        std::cout << "  W Vector: ";
        W.print();
        std::cout << "  U Vector: ";
        U.print();
        std::cout << "  V Vector: ";
        V.print();
        std::cout << "  Distance to screen: " << d << "\n";
        std::cout << "  Screen height: " << h_res << "\n";
        std::cout << "  Screen width: " << h_res << "\n";
    }
};

#endif
