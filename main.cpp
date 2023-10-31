#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "particle.cpp"

// num entities should be divisible by numrows
const int c_numentities = 1000, c_screenwidth = 3800, c_screenheight = 2000;
const int c_numrows = 20;
const float c_framerate = 60.f;
const float c_timestep = 1 / c_framerate;
const float g = -9.8 * 5;
const float collisionDamp = 0.f;



int main() {
    particle entities[c_numentities];
    int radius = 15;
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
    sf::Vector2f origin = { 50 , 50 };
    
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
        srand (currIndex);
        float randOffsetY = rand() % 20; 
        float randOffsetX = rand() % 20;
        if (currIndex == 0 || (currIndex != c_numentities && entities[currIndex - 1].getDistance(origin) >= 2 * radius)) { 
            entities[currIndex] =  * (new particle(origin.x + randOffsetX, origin.y + randOffsetY, 1, radius));
            entities[currIndex].vel->x = ((randOffsetX - 10) * radius * 3) != 0 ? 
                (randOffsetX - 10) * radius * 3 : (randOffsetY - 10) * radius * 3;
            entities[currIndex++].vel->y = ((randOffsetY - 10) * radius * 3) != 0 ? 
                (randOffsetY - 10) * radius * 3 : (randOffsetX - 10) * radius * 3;
            
        }


        for (int i = 0; i < currIndex; ++i) {

            // CHECK ENTITY WITHIN BOUNDS
            entities[i].resolveWallCollision();

            for (int j = i + 1; j < currIndex; ++j) {
               
                // RESOLVE COLLISIONS
                entities[i].resolveCollision(entities[j]);
            }
            // UPDATE VELOCITY AND POSITION
            *entities[i].vel += *entities[i].acc * c_timestep * (1 - collisionDamp);
            *entities[i].pos += *entities[i].vel * c_timestep;
            entities[i].drawable.setPosition(*entities[i].pos);

            // DRAW
            window.draw(entities[i].drawable);
        }

        window.display();
    }

    return 0;
}


