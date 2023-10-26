#include <SFML/Graphics.hpp>

struct Particle : public sf::Transformable {

    sf::Vector2f pos, vel, acc;


    float mass, radius;

    Particle() {
        vel.x = 0;
        vel.y = 0;
        acc.x = 0;
        acc.y = 0;
        mass = 1;
    }
    
    Particle(float x, float y) {
        pos.x = x;
        pos.y = y;
        Particle();
    }
    
    Particle(float x, float y, float mass, float radius) {
        Particle(x, y);
        radius = radius;
        mass = mass;
    }
};