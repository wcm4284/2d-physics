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

bool detectCollision(grav_source_t &src, particle_t &dst) {
    return getDistance(*src.pos, *dst.pos) <= src.ir + dst.ir;
}

// reimplementing the math for this from particle.cpp
void resolveCollision(grav_source_t &src, particle_t &dst) {
    if (detectCollision(src, dst)) {

        float normal1, tangent1, normal2; 

        sf::Vector2f unitNormal = { dst.pos->x - src.pos->x, dst.pos->y - src.pos->y };

        // normalize vector
        unitNormal /= getMagnitude(unitNormal);

        sf::Vector2f unitTangent = {-unitNormal.y, unitNormal.x};
        sf::Vector2f tempVel = {0, 0};

        normal1 = dotProduct(*dst.vel, unitNormal);
        normal2 = dotProduct(tempVel, unitNormal);
        tangent1 = dotProduct(*dst.vel, unitTangent);

        float newNormal1;

        newNormal1 = (normal1 * (dst.im - src.im) + (2 * src.im * normal2)) / (dst.im + src.im);

        sf::Vector2f normalVec1, tangentVec1;

        normalVec1 = {newNormal1 * unitNormal.x, newNormal1 * unitNormal.y};
        tangentVec1 = {tangent1 * unitTangent.x, tangent1 * unitTangent.y};


        *dst.vel = normalVec1 + tangentVec1;
    }
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