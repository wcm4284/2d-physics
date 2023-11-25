#ifndef _GRAVITY_SOURCE_H_
#define _GRAVITY_SOURCE_H_

#include <SFML/Graphics.hpp>
#include "particle.h"

const int universalGrav = 500;

typedef struct {
    sf::Vector2f *pos;
    sf::CircleShape drawable;
    float ir;
    float im;
} grav_source_t;

void applyGravity(particle_t &dst, grav_source_t &src);

/* 
function to detect collisions between two gravity sources
returns true if a collision is detected 
*/
// implemented in gravity_source.cpp
bool detectCollision(grav_source_t &old, grav_source_t &newsrc);

grav_source_t create(const int x, const int y, float mass, float radius);
    
#endif
