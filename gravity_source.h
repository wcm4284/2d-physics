#ifndef _GRAVITY_SOURCE_H_
#define _GRAVITY_SOURCE_H_

#include <SFML/Graphics.hpp>

typedef struct {
    sf::Vector2f *pos;
    sf::CircleShape drawable;
    float im;
} grav_source_t;

    
#endif
