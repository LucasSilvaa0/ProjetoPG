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
    float d;   // Distância entre a câmera e a tela
    int h_res; // Altura da tela
    int w_res; // Largura da tela
    Vector3D subir_1;
    Vector3D direita_1;
    Scene *scene_ptr;

    Camera(const Point3D C, const Point3D M, const float d, const int w_res, const int h_res, Scene *scene_ptr)
        : C(C), M(M), d(d), w_res(w_res), h_res(h_res), scene_ptr(scene_ptr)
    {

        Vup = Vector3D(0, 1, 0);

        updateOrthonormalVectors();

        W = (C - M);
        W.normalize();
        U = W.cross(Vup);
        U.normalize();
        V = W.cross(U);
        V.normalize();

        centro_tela = C + (W * (d * -1));
        Point3D topo_tela = centro_tela + V;
        Point3D esquerda_tela = centro_tela + (U * -1);

        float p_up = (float)1 / float(h_res);
        float p_dir = (float)1 / float(w_res);

        subir_1 = V * p_up;
        direita_1 = U * (p_dir);
        Vector3D esquerda_1 = direita_1 * -1;
        float qtdup = (h_res - 1) / 2;
        float qtdesq = (w_res - 1) / 2;
        primeiro_pixel = centro_tela + ((subir_1 * qtdup) + (esquerda_1 * qtdesq));
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
        std::string lucas = "";

        for (int i = 0; i < w_res; i++)
        {

            for (int j = 0; j < h_res; j++)
            {

                bool achou = false;

                Point3D pixel_que_estamos = primeiro_pixel + ((direita_1 * i) + (subir_1 * (j * -1)));
                Line linha_centro_pixel = Line(C, pixel_que_estamos);

                for (Plane plane : scene_ptr->planos)
                {

                    float t = linha_centro_pixel.l_p_intersection(plane);

                    if (t != -1)
                    {
                        achou = true;
                    }
                }

                for (Sphere sphere : scene_ptr->esferas)
                {

                    float t = linha_centro_pixel.l_s_intersection(sphere);

                    if (t != -1)
                    {
                        achou = true;
                    }
                }
                if (achou)
                {
                    lucas.push_back('x');
                }
                else
                {
                    lucas.push_back(' ');
                }
            }
            lucas.push_back('\n');
        }
        std::cout << lucas;
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
