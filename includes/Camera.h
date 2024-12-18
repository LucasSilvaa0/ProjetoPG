
#ifndef CAMERAHEADER
#define CAMERAHEADER
#include "Point.h"
#include "Vector.h"
#include "Sphere.h"
#include "Line.h"
#include "Scene.h"
#include <iostream>

class Camera
{
public:
    Point3D C;        // Localização da câmera
    Point3D M;        // Ponto para onde a câmera aponta
    Vector3D Vup;     // Vetor para cima
    Vector3D W, U, V; // Vetores ortonormais
    Point3D centro_tela;
    Point3D primeiro_pixel;
    double d;   // Distância entre a câmera e a tela
    int h_res; // Altura da tela
    int w_res; // Largura da tela
    Vector3D subir_1;
    Vector3D direita_1;
    Scene *scene_ptr;

    Camera(const Point3D C, const Point3D M, const double d, const int w_res, const int h_res, Scene *scene_ptr)
        : C(C), M(M), d(d), w_res(w_res), h_res(h_res), scene_ptr(scene_ptr)
    {
        updateVectors();
    }

    void updateCenter(const Point3D c)
    {
        C = c;
        updateVectors();
    }

    void updateAim(const Point3D m)
    {
        M = m;
        updateVectors();
    }

    std::tuple<Vector3D, Vector3D, Vector3D> gramSchmidt(Vector3D &v1)
    {

        Vector3D u1 = v1;

        u1.normalize();

        Vector3D arbitraryVector = (u1.x != 0 || u1.y == 0) ? Vector3D(0, 1, 0) : Vector3D(1, 0, 0);

        Vector3D u2 = arbitraryVector - u1 * (arbitraryVector.dot(u1));

        u2.normalize();

        Vector3D u3 = u1.cross(u2);

        u3.normalize();

        return {u1, u2, u3};
    }

    void render()
    {

        std::cout << "P3\n" << h_res << ' ' << w_res << "\n255\n";

        for (int i = 0; i < h_res; i++)
        {
            for (int j = 0; j < w_res; j++)
            {
                bool achou = false;
                // std::cout<<i*3+j+1<<'\n';
                Point3D pixel_que_estamos = primeiro_pixel + (direita_1 * j) + (subir_1 * (-1 * i));
                // pixel_que_estamos.print();

                Line linha_centro_pixel = Line(C, pixel_que_estamos);

                for (Plane plane : scene_ptr->planos)
                {
                    double t = linha_centro_pixel.l_p_intersection(plane);
                    if (t != -1)
                    {
                        std::cout << plane.cor.getX()*255 << ' ' << plane.cor.getY()*255 << ' ' << plane.cor.getZ()*255 << '\n';
                        achou=true; break;
                    }
                }

                if(!achou){
                for (Sphere sphere : scene_ptr->esferas)
                {
                    double t = linha_centro_pixel.l_s_intersection(sphere);

                    if (t != -1)
                    {
                        std::cout << sphere.cor.getX()*255 << ' ' << sphere.cor.getY()*255 << ' ' << sphere.cor.getZ()*255 << '\n';
                        achou = true; break;
                    }
                }
                }
                if(!achou){
                    std::cout << 0 << ' ' << 0 << ' '  << 0 << ' '  << '\n';
                }
            }
        }
    }

    void updateVectors()
    {

        Vup = Vector3D(0, 1, 0);
        W = (M - C);
        W.normalize();
        U = W.cross(Vup);
        U.normalize();
        V = U.cross(W);
        V.normalize();
        W = W * -1;

        centro_tela = C + (W * (d * -1));
        Point3D topo_tela = centro_tela + V;
        Point3D esquerda_tela = centro_tela + (U * -1);

        double p_up = (double)1 / double(h_res);
        double p_dir = (double)1 / double(w_res);

        subir_1 = V * p_up;
        direita_1 = U * (p_dir);
        Vector3D esquerda_1 = direita_1 * -1;
        double qtdup = (h_res - 1) / 2;
        double qtdesq = (w_res - 1) / 2;
        primeiro_pixel = centro_tela + ((subir_1 * qtdup) + (esquerda_1 * qtdesq));
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
