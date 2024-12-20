
#ifndef CAMERAHEADER
#define CAMERAHEADER
#include "Point.h"
#include "Vector.h"
#include "Sphere.h"
#include "Line.h"
#include "Scene.h"
#include <iostream>
#include <fstream>

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

    std::pair<Vector3D, double> raycolor(Line& ray){

            double min_t = INFINITY;
            Vector3D color;

            // interpolação do background, só pra ficar bonito mesmo

            auto a = 0.5*(ray.line_vector.getY() + 1.0);
            color = Vector3D(1.0, 1.0, 1.0)*(1.0-a) + Vector3D(0.5, 0.7, 1.0)*a;

            // fazemos a checagem de interseção com cada tipo de objeto na cena

            for (Plane plane : scene_ptr->planos){

                double t = ray.l_p_intersection(plane);

                if (t != -1){
                       if(t<min_t){
                        
                        min_t = t;
                        color = plane.cor;

                       }
                    }
                }

            for (Sphere sphere : scene_ptr->esferas)
            {
                    double t = ray.l_s_intersection(sphere);

                    if (t != -1){
                       if(t<min_t){

                        /*

                            muita coisa acontece aqui, vamos por partes:

                            Lambert's cosine law diz que a luz que reflete de um objeto é inversamente proporcional ao angulo entre a normal do objeto e raio
                            Aqui, calculamos a normal da bola e o cosseno do angulo de incidencia com a normal
                            Pra deixar a transição da cor mais "smooth", a cor foi multiplicada pelo cosseno da metade do angulo
                            Cos(x/2) = 1-sqrt((1+cos(x))/2)
                        
                        */
                        Vector3D N = ray.at(t) - sphere.C; N.normalize();
                        min_t = t;
                        float degrade = 1-sqrt((1+N.cos(ray.line_vector))/2);
                        color = sphere.cor*degrade;

                       }
                    }
                }  

            // retorna a cor e o t
            
            return {color,min_t};          
    }

    void render(const std:: string& filename)
    {

        std::ofstream file(filename, std::ios::out | std::ios::trunc);
        // header do ppm
        file << "P3\n" << h_res << ' ' << w_res << "\n255\n";


        // para cada linha de pixels
        for (int i = 0; i < h_res; i++)
        {

            // para cada pixel da linha
            for (int j = 0; j < w_res; j++)
            {

                /* 
                    pegamos o primeiro pixel, somamos com quantas vezes queremos ir pra direita + quantas vezes queremos ir pra baixo
                    isto é, P11 + direita*j + up*-i = P(i-1)(j-1)
                    note que como (i,j) começa como (0,0), o primeiro pixel tá contado 
                */

                Point3D pixel_que_estamos = primeiro_pixel + (direita_1 * j) + (subir_1 * (-1 * i));

                // formamos o raio que parte do centro da camera e vai pro pixel

                Line linha_centro_pixel = Line(C, pixel_que_estamos);

                Vector3D cor_do_pixel; float t;

                // pegamos a cor do pixel do objeto que intersecta mais perto (retorna um par (cor, t))

                auto temp = raycolor(linha_centro_pixel);

                cor_do_pixel = temp.first; t = temp.second;
               
                // manda pro ppm

                file << cor_do_pixel.getX()*255 << " " << cor_do_pixel.getY()*255 << " " << cor_do_pixel.getZ()*255 << '\n';

            }
        }
    }

    void updateVectors()
    {

        // Cria a base + up vector
        Vup = Vector3D(0, 1, 0);
        W = (M - C);
        W.normalize();
        U = W.cross(Vup);
        U.normalize();
        V = U.cross(W);
        V.normalize();
        W = W * -1;

        // Calcula a tela com os pixels
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
