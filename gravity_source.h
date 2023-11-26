#ifndef _GRAVITY_SOURCE_H_
#define _GRAVITY_SOURCE_H_

#include <SFML/Graphics.hpp>
#include "particle.h"

const int universalGrav = 500;


/* this is extremely similar to the particle_t struct, 
however I wanted them separate in order to differentiate
between the two easily versus using an enum to differentiate */
typedef struct {
    sf::Vector2f *pos;
    sf::CircleShape drawable;
    float ir;
    float im;
} grav_source_t;

/* function to apply gravity to a particle_t dst based 
on the distance between dst and src
no return, acceleration of dst is changed as a result
implemented in gravity_source.cpp */
void applyGravity(particle_t &dst, grav_source_t &src);

/* function to detect collisions between two gravity sources
returns true if a collision is detected, false otherwise
implemented in gravity_source.cpp */
bool detectCollision(grav_source_t &old, grav_source_t &newsrc);

/* function to detect collisions between a grav_source_t
and a particle_t
returns true if a collision is detected, false otherwise
implemented in gravity_source.cpp */
bool detectCollision(grav_source_t &src, particle_t &dst);

/* function to resolve collisions between a particle and gravity source
returns nothing
velocity of ptl is changed as a result
implemented in gravity_source.cpp */
void resolveCollision(grav_source_t &src, particle_t &ptl);

/* function to create a grav_source_t instance 
instantiates all the necessary values of the struct
returns a grav_source_t instance
implemented in gravity_source.cpp */
grav_source_t create(const int x, const int y, float mass, float radius);
    
#endif
