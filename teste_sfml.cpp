#include <iostream>
#include "includes/Point.h"
#include "includes/Plane.h"
#include "includes/Vector.h"
#include "includes/Sphere.h"
#include "includes/Line.h"
#include "includes/Camera.h"
#include "includes/Scene.h"
#include "includes/objetificador.h"
#include "includes/Renderer.h"
#include <SFML/Graphics.hpp>

int main()
{
    objReader *obj = new objReader("input/cubo.obj");
    Camera camera = Camera(Point3D(-10, 0, 0), Point3D(0, 0, 0), (double)1, 800, 600);
    Scene *cena = new Scene();

    obj->transladar(0, 0, 2.9);

    cena->objetos.push_back(obj);

    

    sf::RenderWindow window(sf::VideoMode(500,500), "coito");
    window.setFramerateLimit(60);
    std::vector<sf::Color> colors(500*500);
    sf::VertexArray pixels(sf::Points, 500*500);

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();
        }

        auto palao=camera.render(cena);
        for(int i = 0; i < 500*500; i++){
            colors[i]=sf::Color(palao[i].getX(),palao[i].getY(),palao[i].getZ());
        }
        for (int y = 0; y < 500; y++) {
            for (int x = 0; x < 500; x++) {
                int index = y * 500 + x;
                pixels[index].position = sf::Vector2f(x, y);
                pixels[index].color = colors[index];
            }
        }

        window.clear();
        window.draw(pixels);
        window.display();

    }

    return 0;
}
