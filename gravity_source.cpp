#include <cmath>
#include <iostream>
#include "gravity_source.h"


void applyGravity(particle_t &dst, grav_source_t &src) {
    float theta = atan2((src.pos->y - dst.pos->y), (src.pos->x - dst.pos->x));
    float force = universalGrav * src.im / pow(getDistance(*src.pos, *dst.pos), 2);
    dst.acc->x += force * cosf(theta);
    dst.acc->y += force * sinf(theta);
}

bool detectCollision(grav_source_t &old, grav_source_t& newsrc) {
    return getDistance(*old.pos, *newsrc.pos) <= old.ir + newsrc.ir;
}

grav_source_t create(const int x, const int y, float mass, float radius) {
    grav_source_t newSource;
    newSource.pos = (sf::Vector2f *) malloc(sizeof(sf::Vector2f));
    *newSource.pos = {(float) x, (float) y};
    newSource.ir = radius;
    newSource.im = mass;
    newSource.drawable.setFillColor(sf::Color::Black);
    newSource.drawable.setPosition(newSource.pos->x - radius, newSource.pos->y - radius);
    newSource.drawable.setRadius(newSource.ir);

    return newSource;
}