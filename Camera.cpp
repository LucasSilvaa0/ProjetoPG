#ifndef CAMERAHEADER
#define CAMERAHEADER
#include <Point.cpp>
#include <Vector.cpp>
#include <Sphere.cpp>
#include <Line.cpp>
#include <iostream>


class Camera {
public:
    Point3D C; // Localização da câmera
    Point3D M; // Ponto para onde a câmera aponta
    Vector3D Vup; // Vetor para cima
    Vector3D W, U, V; // Vetores ortonormais
    float d; // Distância entre a câmera e a tela
    int v_res; // Altura da tela
    int h_res; // Largura da tela

    Camera(Point3D C, Point3D M, Vector3D Vup, float d, int v_res, int h_res)
        : C(C), M(M), Vup(Vup), d(d), v_res(v_res), h_res(h_res) {
        updateOrthonormalVectors();
    }

    void updateOrthonormalVectors() {
        W = C - M;
        W.normalize();
        U = Vup.cross(W);
        U.normalize();
        V = W.cross(U);
    }

    void print() const {
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
        std::cout << "  Screen height: " << v_res << "\n";
        std::cout << "  Screen width: " << h_res << "\n";
    }


};


#endif


