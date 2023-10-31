#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "particle.cpp"

// num entities should be divisible by numrows
const int c_numentities = 20, c_screenwidth = 3800, c_screenheight = 2400;
const int c_numrows = 20;
const float c_framerate = 60.f;
const float c_timestep = 1 / c_framerate;
const float g = 9.8;



int main() {
    particle entities[c_numentities];
    int radius = 3;
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
    sf::Vector2f origin = { 100, 100 };
    
    sf::RenderWindow window(sf::VideoMode(c_screenwidth, c_screenheight), "2D Physics Engine");
    window.setFramerateLimit(c_framerate);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }

        window.clear();

        // method 2 continued, origin point
        srand (time(NULL));
        float randOffsetY = rand() % 5; 
        float randOffsetX = rand() % 5;
        if (currIndex == 0 || (currIndex != c_numentities && entities[currIndex - 1].getDistance(origin) > 2 * radius)) { 
            entities[currIndex] =  * (new particle(origin.x + randOffsetX, origin.y + randOffsetY, 1, radius));
        }

        for (particle entity1 : entities) {
            if ( ! entity1.pos ) continue;
            // CHECK ENTITY WITHIN BOUNDS
            entity1.resolveWallCollision();

            for (particle entity2: entities) {
                if (! entity2.pos );
                if (&entity1 == &entity2) continue;

                // RESOLVE COLLISIONS
                entity1.resolveCollision(entity2);
            }
            // UPDATE VELOCITY AND POSITION
            *entity1.vel += *entity1.acc * c_timestep;
            *entity1.pos += *entity1.vel * c_timestep;
            entity1.drawable.setPosition(*entity1.pos);

            // DRAW
            window.draw(entity1.drawable);
        }

        window.display();
    }

    return 0;
}


