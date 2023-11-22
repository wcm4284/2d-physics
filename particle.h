#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <SFML/Graphics.hpp>

typedef struct {
    sf::CircleShape drawable;
    sf::Vector2f *pos;
    sf::Vector2f *vel;
    sf::Vector2f *acc;
    float im;
    float ir;

} particle_t;

float getDistance(particle_t &p1, particle_t &p2);

float getMagnitude(sf::Vector2f &vec);

float dotProduct(sf::Vector2f &vec1, sf::Vector2f &vec2);

void resolveWallCollision(particle_t &p, const float offset);

void resolveParticleCollision(particle_t &p1, particle_t &p2);

void calculateNewVelocities(particle_t &p1, particle_t &p2);

#endif
