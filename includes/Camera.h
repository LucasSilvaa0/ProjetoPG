
#ifndef CAMERAHEADER
#define CAMERAHEADER
#include "Point.h"
#include "Vector.h"
#include "Sphere.h"
#include "Line.h"
#include "Scene.h"
#include <iostream>
#include <fstream>
#include <cmath>

class Camera
{
public:
    Point3D C;        // Localização da câmera
    Point3D M;        // Ponto para onde a câmera aponta
    Vector3D Vup;     // Vetor para cima
    Vector3D W, U, V; // Vetores ortonormais
    Point3D centro_tela;
    Point3D primeiro_pixel;
    double d;  // Distância entre a câmera e a tela
    int h_res; // Altura da tela
    int w_res; // Largura da tela
    Vector3D subir_1;
    Vector3D direita_1;

    Camera(const Point3D C, const Point3D M, const double d, const int w_res, const int h_res)
        : C(C), M(M), d(d), w_res(w_res), h_res(h_res)
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

    std::pair<Vector3D, double> raycolor(Line &ray, Scene *scene_ptr, int contador, double ni1)
    {
        double min_t = INFINITY;
        Vector3D color;

        // interpolação do background, só pra ficar bonito mesmo

        color = Vector3D(0, 0, 0);

        // fazemos a checagem de interseção com cada tipo de objeto na cena

        Vector3D ka;
        Vector3D kd;
        Vector3D normal;
        Vector3D ks;
        double d;
        int ns;
        double ni2;

        for (Plane *plane_ptr : scene_ptr->planos)
        {
            Plane plane = *plane_ptr;
            double t = ray.l_p_intersection(plane);

            if (t > 0 && t < min_t)
            {
                min_t = t;
                ka = plane.material.ka;
                kd = plane.material.kd;
                normal = plane.normal;
                ks = plane.material.ks;
                ns = plane.material.ns;
                ni2 = plane.material.ni;
                d = plane.material.d;
            }
        }

        for (Sphere *sphere_ptr : scene_ptr->esferas)
        {
            Sphere sphere = *sphere_ptr;
            double t = ray.l_s_intersection(sphere);

            if (t > 0 && t < min_t)
            {
                Vector3D N = ray.at(t) - sphere.C;
                N.normalize();
                min_t = t;
                ka = sphere.material.ka;
                kd = sphere.material.kd;
                normal = N;
                ks = sphere.material.ks;
                ns = sphere.material.ns;
                ni2 = sphere.material.ni;
                d = sphere.material.d;
            }
        }

        for (objReader *object_ptr : scene_ptr->objetos)
        {
            for (Face face : object_ptr->getFaces())
            {
                Triangle triangulo = object_ptr->faceToTriangulo(face);
                double t = ray.l_t_intersection(triangulo);

                if (t > 0 && t < min_t)
                {
                    Vector3D N = triangulo.NormalVector();
                    min_t = t;

                    // color = triangulo.cor;
                    ka = face.ka;
                    kd = face.kd;
                    normal = N;
                    ks = face.ks;
                    ns = face.ns;
                    ni2 = face.ni;
                    d = face.d;
                }
            }
        }

        color = colorPhong(&ka, scene_ptr, &kd, &normal, &ks, &ray.line_vector, ray.at(min_t), ns);

        if (contador < 2 && min_t < INFINITY)
        {
            double kreflexao = d;
            double krefracao = 1 - d;

            // REFLEXÃO
            Vector3D reflexao = ray.line_vector.refletir(&normal);
            Line linhareflexao = Line(ray.at(min_t), ray.at(min_t) + reflexao);
            auto tempreflexao = raycolor(linhareflexao, scene_ptr, contador + 1, ni2);
            Vector3D correfletida;
            correfletida = tempreflexao.first;

            // REFRAÇÃO
            Vector3D refracao = ray.line_vector.refratar(ni1, ni2, &normal);
            Line linharefracao = Line(ray.at(min_t), ray.at(min_t) + refracao);
            auto temprefracao = raycolor(linharefracao, scene_ptr, contador + 1, ni2);
            Vector3D correfracao;
            correfracao = temprefracao.first;

            if (tempreflexao.second != INFINITY || temprefracao.second != INFINITY)
            {
                if (tempreflexao.second != INFINITY)
                {
                    color.x += correfletida.x * kreflexao;
                    color.y += correfletida.y * kreflexao;
                    color.z += correfletida.z * kreflexao;
                }

                if (temprefracao.second != INFINITY)
                {
                    color.x += correfracao.x * krefracao;
                    color.y += correfracao.y * krefracao;
                    color.z += correfracao.z * krefracao;
                }
            }
        }

        // retorna a cor e o t

        return {color, min_t};
    }

    std::vector<Point3D> render(Scene *scene_ptr)
    {
        std::vector<Point3D> retornar;
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

                Vector3D cor_do_pixel;
                float t;

                // pegamos a cor do pixel do objeto que intersecta mais perto (retorna um par (cor, t))

                auto temp = raycolor(linha_centro_pixel, scene_ptr, 0, 1);

                cor_do_pixel = temp.first;
                t = temp.second;

                // manda pro ppm

                retornar.push_back(Point3D(cor_do_pixel.getX(), cor_do_pixel.getY(), cor_do_pixel.getZ()));
            }
        }
        return retornar;
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

        double p_up = (double)1 / double(h_res);
        double p_dir = (double)1 / double(w_res);

        subir_1 = V * p_up;
        direita_1 = U * (p_dir);
        Vector3D esquerda_1 = direita_1 * -1;
        double qtdup = (h_res - 1) / 2;
        double qtdesq = (w_res - 1) / 2;
        primeiro_pixel = centro_tela + ((subir_1 * qtdup) + (esquerda_1 * qtdesq));
    }

    int lightRender(Luz *luz, Point3D *Pintercessao, Scene scene_ptr)
    {
        Line ray = Line(luz->p, *Pintercessao);

        // fazemos a checagem de interseção com cada tipo de objeto na cena

        double t_inicial = (Pintercessao->x - luz->p.x) / ray.line_vector.getX();

        for (Plane *plane_ptr : scene_ptr.planos)
        {
            Plane plane = *plane_ptr;
            double t = ray.l_p_intersection(plane);

            if (t > 0 && t < t_inicial - 0.001)
            {
                return 0;
            }
        }

        for (Sphere *sphere_ptr : scene_ptr.esferas)
        {
            Sphere sphere = *sphere_ptr;
            double t = ray.l_s_intersection(sphere);

            if (t > 0 && t < t_inicial - 0.001)
            {
                return 0;
            }
        }

        for (objReader *object_ptr : scene_ptr.objetos)
        {
            for (Face face : object_ptr->getFaces())
            {
                Triangle triangulo = object_ptr->faceToTriangulo(face);
                double t = ray.l_t_intersection(triangulo);

                if (t > 0 && t < t_inicial - 0.001)
                {
                    return 0;
                }
            }
        }

        return 1;
    }

    Vector3D colorPhong(Vector3D *ka, Scene *scene_ptr, Vector3D *kd, Vector3D *N, Vector3D *ks, Vector3D *V, Point3D Pintercessao, int n)
    {
        Vector3D cor = Vector3D(0, 0, 0);

        // Luz ambiente
        Vector3D *Ia = &scene_ptr->Ia;

        cor.x = Ia->x * ka->x;
        cor.y = Ia->y * ka->y;
        cor.z = Ia->z * ka->z;

        Vector3D somatotal = Vector3D(0, 0, 0);
        for (Luz *luz : scene_ptr->luzes)
        {
            Vector3D soma = Vector3D(0, 0, 0);
            if (lightRender(luz, &Pintercessao, *scene_ptr) == 1)
            {
                // Luz difusa
                Vector3D L = Pintercessao - luz->p;
                L.normalize();
                N->normalize();

                double cosNL = N->dot(L);

                if (cosNL < 0)
                    cosNL *= -1;

                soma.x += kd->x * cosNL;
                soma.y += kd->y * cosNL;
                soma.z += kd->z * cosNL;

                // Luz especular
                Vector3D le = Vector3D(0, 0, 0);

                Vector3D r = L.refletir(N);
                double vrn = pow(V->dot(r), n);

                if (vrn < 0)
                    vrn *= -1;

                soma.x += ks->x * vrn;
                soma.y += ks->y * vrn;
                soma.z += ks->z * vrn;

                // Intensidade da luz
                somatotal.x += soma.x * luz->cor.x;
                somatotal.y += soma.y * luz->cor.y;
                somatotal.z += soma.z * luz->cor.z;
            }
        }

        cor.x += somatotal.x;
        cor.y += somatotal.y;
        cor.z += somatotal.z;

        if (cor.x > 1)
            cor.x = 1;
        if (cor.y > 1)
            cor.y = 1;
        if (cor.z > 1)
            cor.z = 1;

        return cor;
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