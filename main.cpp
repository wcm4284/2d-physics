#include <SFML/Graphics.hpp>
#include <iostream>
#include "particle.cpp"

const int c_numentities = 1, c_screenwidth = 1280, c_screenheight = 720;
const float c_framerate = 60.f;
const float c_timestep = 1 / c_framerate;



void updatePos(sf::Vector2f &pos) {
    pos.x += 1;
    pos.y += 1;
}

int main() {
    particle entities[c_numentities];

    for (int i = 0; i < c_numentities; ++i) {
        entities[i] = * (new particle(100, 100, 1, 5));
    }
    
    sf::RenderWindow window(sf::VideoMode(c_screenwidth, c_screenheight), "Physics Engine");
    window.setFramerateLimit(c_framerate);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear();

        for (particle entity1 : entities) {
            entity1.pos->x += entity1.vel->x;
            entity1.pos->y += entity1.vel->y;
            entity1.drawable.setPosition(*entity1.pos);
            for (particle entity2: entities) {
                if (&entity1 == &entity2) continue;
            }
            window.draw(entity1.drawable);
        }

        window.display();

    }

    return 0;
}


