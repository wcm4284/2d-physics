#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include "particle.h"
#include "gravity_source.h"

float screenHeight = 2150;
float screenWidth = 3850;
float framerate = 60;
float timestep = 1 / framerate;
float offset = 200;
int numEntities = 100;
float g = 9.8;
float maxVelocity = 500;

int main()
{
    particle_t ptls[numEntities];
    int radius = 5;

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "2D Engine");
    window.setFramerateLimit(framerate);
    window.setPosition({0, 0});

    int currIndex = 0;

    sf::Vector2f origin = {50 + offset, 50 + offset};

    sf::Vertex border[] = 
    {
        sf::Vertex(sf::Vector2f(offset, offset)),
        sf::Vertex(sf::Vector2f(screenWidth - offset, offset)),
        sf::Vertex(sf::Vector2f(screenWidth - offset, screenHeight - offset)),
        sf::Vertex(sf::Vector2f(offset, screenHeight - offset))
    };

    border->color = sf::Color(255, 255, 255, 0);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }

        window.clear();

        window.draw(border, 4, sf::Quads);

        srand(currIndex);

        if (currIndex == 0 || (getDistance(origin, *ptls[currIndex - 1].pos) > radius + ptls[currIndex - 1].ir && currIndex != numEntities)) {
            ptls[currIndex] = create(origin.x, origin.y, 1, radius);
            ptls[currIndex].vel->x = (rand() % 20 + 5) * 20;
            ptls[currIndex++].vel->y = (rand() % 3 + 1) * 20;
        }


        for (int i = 0; i < currIndex; i++) {

            resolveWallCollision(ptls[i], offset);

            for (int j = i + 1; j < currIndex; j++) {

                resolveParticleCollision(ptls[i], ptls[j]);

            }

            // update vel and pos
            *ptls[i].vel += (*ptls[i].acc * timestep);

            // check if velocity is greater than max, correct if so
            if (ptls[i].vel->x > maxVelocity) ptls[i].vel->x = maxVelocity;
            if (ptls[i].vel->y > maxVelocity) ptls[i].vel->y = maxVelocity;

            *ptls[i].pos += (*ptls[i].vel * timestep);
            ptls[i].drawable.setPosition(*ptls[i].pos);

            // change color and draw
            unsigned int shade = getMagnitude(*ptls[i].vel) / 2;
            shade = shade > 255 ? 255 : shade;
            ptls[i].drawable.setFillColor(sf::Color(0, shade, (255 - shade), 255));
            window.draw(ptls[i].drawable);

        }
        
        window.display();

    }

    return 0;
}