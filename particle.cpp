#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "particle.h"

extern float screenHeight;
extern float screenWidth;
extern float g;

float getDistance(sf::Vector2f &p1, sf::Vector2f &p2) {
    float x, y;
    x = p1.x - p2.x;
    y = p1.y - p2.y;
    return sqrt((x * x) + (y * y));
}

float getMagnitude(sf::Vector2f &vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

float dotProduct(sf::Vector2f &vec1, sf::Vector2f &vec2) {
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

void resolveWallCollision(particle_t &p, const float offset) {
    if (p.pos->x + p.ir >= screenWidth - offset) {
        p.vel->x = -abs(p.vel->x);
    } else if (p.pos->x - p.ir <= offset) {
        p.vel->x = abs(p.vel->x);
    }
    if (p.pos->y + p.ir >= screenHeight - offset) {
        p.vel->y = -abs(p.vel->y);
    } else if (p.pos->y - p.ir <= offset) {
        p.vel->y = abs(p.vel->y);
    }
}

void resolveParticleCollision(particle_t &p1, particle_t &p2) {
    if (getDistance(*p1.pos, *p2.pos) <= p1.ir + p2.ir) {
        calculateNewVelocities(p1, p2);
    }
}

void calculateNewVelocities(particle_t &p1, particle_t &p2) {
    float normal1, tangent1, normal2, tangent2; 
    sf::Vector2f unitNormal = { p1.pos->x - p2.pos->x, p1.pos->y - p2.pos->y };

    unitNormal /= getMagnitude(unitNormal);

    sf::Vector2f unitTangent = {-unitNormal.y, unitNormal.x};

    normal1 = dotProduct(*p1.vel, unitNormal);
    normal2 = dotProduct(*p2.vel, unitNormal);
    tangent1 = dotProduct(*p1.vel, unitTangent);
    tangent2 = dotProduct(*p2.vel, unitTangent); 

    float newNormal1, newNormal2; 

    newNormal1 = (normal1 * (p1.im - p2.im) + (2 * p2.im * normal2)) / (p1.im + p2.im);
    newNormal2 = (normal2 * (p2.im - p1.im) + (2 * p1.im * normal1)) / (p1.im + p2.im);

    sf::Vector2f normalVec1, normalVec2, tangentVec1, tangentVec2;

    normalVec1 = {newNormal1 * unitNormal.x, newNormal1 * unitNormal.y};
    normalVec2 = {newNormal2 * unitNormal.x, newNormal2 * unitNormal.y};
    tangentVec1 = {tangent1 * unitTangent.x, tangent1 * unitTangent.y};
    tangentVec2 = {tangent2 * unitTangent.x, tangent2 * unitTangent.y};


    *p1.vel = normalVec1 + tangentVec1;
    *p2.vel = normalVec2 + tangentVec2;
}

particle_t create(float x, float y, float mass, float radius) {
    particle_t ptl;

    ptl.pos = (sf::Vector2f*) malloc(sizeof(sf::Vector2f));
    ptl.vel = (sf::Vector2f*) malloc(sizeof(sf::Vector2f));
    ptl.acc = (sf::Vector2f*) malloc(sizeof(sf::Vector2f));

    *ptl.pos = {x, y};
    ptl.im = mass;
    ptl.ir = radius;

    *ptl.vel = {0, 0};
    *ptl.acc = {0, g};

    ptl.drawable.setRadius(radius);

    return ptl;
}
