#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include "particle.cpp"

// num entities should be divisible by numrows
int c_numentities = 2000, c_screenwidth = 3850, c_screenheight = 2300;
const int c_numrows = 20;
const float c_framerate = 60.f;
const float c_timestep = 1 / c_framerate;
const float g = 9.8 * 20;
const float uniG = 10;
//const float collisionDamp = 0.00f;
const float offset = 200.f;
const float maxVelocity = 500;
float mouseMass = 200;




int main() {
    particle entities[c_numentities];
    int radius = 5;
    bool gravityActive = false;
    /* THERE WILL BE MULTIPLE WAYS TO INSTANTIATE OBJECTS
    *  ONE WILL BE TO CREATE THEM IN ROWS AND APPLY A 
    *  SMALL RANDOM FORCE AT THE START, ANOTHER WILL BE 
    *  TO INSTANTIATE THEM FROM A SMALL POINT IN SPACE
    *  AND SEND THEM OFF
    */

    // method 1, rows and columns
    // int numPerRow = c_numentities / c_numrows;
    // float xSpacing = c_screenwidth / (numPerRow + 1);
    // float ySpacing = c_screenheight / (c_numrows + 1);
    // for (int i = 0; i < numPerRow; ++i) {
    //     for (int j = 0; j < c_numrows; ++j) {
    //         entities[(i * c_numrows) + j] = * (new particle(xSpacing * (i + 1), ySpacing * (j + 1), 1, radius));
    //     }
    // }

    //method 2, point in space
    int currIndex = 0;
    sf::Vector2f origin = { 50 + offset , 50 + offset };
    sf::Vector2f gravityOrigin;
    sf::RenderWindow window(sf::VideoMode(c_screenwidth, c_screenheight), "2D Physics Engine");
    window.setPosition({0, 0});
    window.setFramerateLimit(c_framerate);



    // define borders

    sf::Vertex border[] = 
    {
        sf::Vertex(sf::Vector2f(offset, offset)),
        sf::Vertex(sf::Vector2f(c_screenwidth - offset, offset)),
        sf::Vertex(sf::Vector2f(c_screenwidth - offset, c_screenheight - offset)),
        sf::Vertex(sf::Vector2f(offset, c_screenheight - offset))
    };

    border->color = sf::Color(255, 255, 255, 0);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                gravityOrigin.x = sf::Mouse::getPosition(window).x;
                gravityOrigin.y = sf::Mouse::getPosition(window).y;
                gravityActive = true;
            } else {
                gravityActive = false;
            }
        }

        window.clear();

        window.draw(border, 4, sf::Quads);
        //method 2 continued, origin point
        srand (currIndex);
        float randOffsetY = rand() % 20; 
        float randOffsetX = rand() % 20;
        if (currIndex == 0 || (currIndex != c_numentities && entities[currIndex - 1].getDistance(origin) >= 2 * radius)) { 
            entities[currIndex] =  * (new particle(origin.x + randOffsetX, origin.y + randOffsetY, 1, radius));
            entities[currIndex].vel->x = ((randOffsetX - 10) * radius * (20 - radius)) != 0 ? 
                (randOffsetX - 10) * radius * (20 - radius) : (randOffsetY - 10) * radius * (20 - radius);
            entities[currIndex++].vel->y = ((randOffsetY - 10) * radius * (20 - radius)) != 0 ? 
                (randOffsetY - 10) * radius * (20 - radius) : (randOffsetX - 10) * radius * (20 - radius);
            
        }

        for (int i = 0; i < currIndex; i++) {

            // CHECK ENTITY WITHIN BOUNDS
            entities[i].resolveWallCollision(offset);
            if (gravityActive) {
                entities[i].acc->x = uniG * mouseMass / (gravityOrigin.x - entities[i].pos->x);
                entities[i].acc->y = uniG * mouseMass / (gravityOrigin.y - entities[i].pos->y);
            } else {
                *entities[i].acc = {0, g};
            }

            for (int j = i + 1; j < currIndex; j++) {
               
                // RESOLVE COLLISIONS
                entities[i].resolveCollision(entities[j]);

            }
            // UPDATE VELOCITY AND POSITION
            *entities[i].vel += *entities[i].acc * c_timestep;
            *entities[i].pos += *entities[i].vel * c_timestep;
            entities[i].drawable.setPosition(*entities[i].pos);

            if (entities[i].vel->x > maxVelocity) entities[i].vel->x = maxVelocity;
            if (entities[i].vel->y > maxVelocity) entities[i].vel->y = maxVelocity;

            // DRAW
            unsigned int shade = entities[i].getMagnitude(*entities[i].vel) / 5;
            shade = shade > 255 ? 255 : shade;
            entities[i].drawable.setFillColor(sf::Color(0, shade, (255 - shade), 255));
            window.draw(entities[i].drawable);
        }

        window.display();
    }

    return 0;
}


