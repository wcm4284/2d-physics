#ifndef GRAVITYSOURCE_CPP
#define GRAVITYSOURCE_CPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include "gravitySource.hpp"

extern float univG;

void applyGravity(gravity_source_t &src, Particle &dst) {
    float theta = atan2((src.pos->y - dst.pos->y), (src.pos->x - dst.pos->x));
    float force = univG * src.iMass / pow(dst.getDistance(*src.pos), 1.25);
    dst.acc->x += force * cosf(theta);
    dst.acc->y += force * sinf(theta);
}

float getDistance(sf::Vector2f &point1, sf::Vector2f &point2) {
    float x, y;
    x = point1.x - point2.x;
    y = point1.y - point2.y;
    return sqrtf((x * x) + (y * y));
}

bool checkCollision(gravity_source_t &src1, gravity_source_t &src2) {
    return getDistance(*src1.pos, *src2.pos) < src1.drawable.getRadius() + src2.drawable.getRadius();
}

#endif