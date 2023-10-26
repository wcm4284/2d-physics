#include <SFML/Graphics.hpp>
#include <iostream>
#include "particle.cpp"

int c_NUMENTITIES = 100;


int main() {
    Particle entities[c_NUMENTITIES];

    for (int i = 0; i < c_NUMENTITIES; ++i) {
        entities[i] = * (new Particle(i + 2, i + 2, 1, 50));
    }
    
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Physics Engine");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear();

        for (int i = 0; i < c_NUMENTITIES; i++) {
            sf::CircleShape shape(entities[i].radius);
            shape.move(entities[i].pos.x, entities[i].pos.y);
            shape.setFillColor(sf::Color::Green);
            window.draw(shape);
        }
        window.display();
    }

    return 0;
}

