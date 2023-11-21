#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "gravitySource.hpp"


extern int c_screenheight;
extern int c_screenwidth;
extern const float g;
//extern const float collisionDamp;

typedef struct Particle : public sf::Transformable {

    sf::Vector2f *pos;
    sf::Vector2f *vel;
    sf::Vector2f *acc;
    sf::CircleShape drawable;
    float radius;
    float mass;

    Particle() {};

    Particle(float x, float y, float mass, float radius) {
        pos = new sf::Vector2f();
        vel = new sf::Vector2f();
        acc = new sf::Vector2f();
        
        pos->x = x; pos->y = y;
        vel->x = 0; vel->y = 0;
        acc->x = 0; acc->y = g;
        drawable.setFillColor(sf::Color::White);
        drawable.setRadius(radius);
        drawable.setPosition(*pos);
        this->radius = radius;
        this->mass = mass;
    }

    void resolveWallCollision(float offset) {
        if (pos->x + radius >= c_screenwidth - offset) {
            vel->x = -abs(vel->x);
        } else if (pos->x - radius <= offset) {
            vel->x = abs(vel->x);
        }
        if (pos->y + radius >= c_screenheight - offset) {
            vel->y = -abs(vel->y);
        } else if (pos->y - radius <= offset) {
            vel->y = abs(vel->y);
        }
    }

    void resolveCollision(Particle &other) {
        float dst = getDistance(*other.pos);
        if (dst < radius + other.radius) {
            calculateResultantVelocities(other);
        }
    }

    void resolveCollision(gravity_source_t &other) {
        float dst = getDistance(*other.pos);
        if (dst < radius + other.drawable.getRadius()) {
            calculateResultantVelocities(other);
        }
    }


    // this process comes from https://www.vobarian.com/collisions/2dcollisions2.pdf, credit to the author

    void calculateResultantVelocities(Particle &other) {
        float normal1, tangent1, normal2, tangent2; 
        sf::Vector2f unitNormal = { pos->x - other.pos->x, pos->y - other.pos->y };

        unitNormal /= getMagnitude(unitNormal);

        sf::Vector2f unitTangent = {-unitNormal.y, unitNormal.x};

        normal1 = dotProduct(*vel, unitNormal);
        normal2 = dotProduct(*other.vel, unitNormal);
        tangent1 = dotProduct(*vel, unitTangent);
        tangent2 = dotProduct(*other.vel, unitTangent); 

        float newNormal1, newNormal2; 

        newNormal1 = (normal1 * (mass - other.mass) + (2 * other.mass * normal2)) / (mass + other.mass);
        newNormal2 = (normal2 * (other.mass - mass) + (2 * mass * normal1)) / (mass + other.mass);

        sf::Vector2f normalVec1, normalVec2, tangentVec1, tangentVec2;

        normalVec1 = {newNormal1 * unitNormal.x, newNormal1 * unitNormal.y};
        normalVec2 = {newNormal2 * unitNormal.x, newNormal2 * unitNormal.y};
        tangentVec1 = {tangent1 * unitTangent.x, tangent1 * unitTangent.y};
        tangentVec2 = {tangent2 * unitTangent.x, tangent2 * unitTangent.y};


        *vel = normalVec1 + tangentVec1;
        *other.vel = normalVec2 + tangentVec2;
    }


    // same process as above repeated for gravity_source_t
    void calculateResultantVelocities(gravity_source_t &other) {
        float normal1, tangent1, normal2, tangent2; 
        sf::Vector2f unitNormal = { pos->x - other.pos->x, pos->y - other.pos->y };

        unitNormal /= getMagnitude(unitNormal);

        sf::Vector2f unitTangent = {-unitNormal.y, unitNormal.x};

        sf::Vector2f otherVel = {0, 0};

        normal1 = dotProduct(*vel, unitNormal);
        normal2 = dotProduct(otherVel, unitNormal);
        tangent1 = dotProduct(*vel, unitTangent);

        float newNormal1, newNormal2; 

        newNormal1 = (normal1 * (mass - other.iMass) + (2 * other.iMass * normal2)) / (mass + other.iMass);

        sf::Vector2f normalVec1, tangentVec1;

        normalVec1 = {newNormal1 * unitNormal.x, newNormal1 * unitNormal.y};
        tangentVec1 = {tangent1 * unitTangent.x, tangent1 * unitTangent.y};


        *vel = normalVec1 + tangentVec1;
    }
    
    float getDistance(sf::Vector2f &point) {
        float x, y;
        x = pos->x - point.x;
        y = pos->y - point.y;
        return sqrtf((x * x) + (y * y));
    }

    float getMagnitude(sf::Vector2f &vector) {
        return sqrt(vector.x * vector.x + vector.y * vector.y);
    }

    float dotProduct(sf::Vector2f &vector1, sf::Vector2f &vector2) {
        return vector1.x * vector2.x + vector1.y * vector2.y;
    }

} particle;