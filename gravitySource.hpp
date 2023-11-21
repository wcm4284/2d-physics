#ifndef GRAVITYSOURCE_HPP
#define GRAVITYSOURCE_HPP

#include <SFML/Graphics.hpp>
#include "particle.cpp"

typedef struct {
    float iMass;
    sf::Vector2f *pos;
    sf::CircleShape drawable;
} gravity_source_t;


//apply gravity based on F = m1 * m2 / r^2 to each particle from each src
void applyGravity(gravity_source_t &src, Particle &dst);

// check collisions with other sources to avoid creating sources on top of each other
void checkCollision(gravity_source_t &src1, gravity_source_t &src2);

float getDistance(sf::Vector2f &point1, sf::Vector2f &point2);

#endif