#include <SFML/Graphics.hpp>
#include <iostream>

typedef struct Particle : public sf::Transformable {

    sf::Vector2f *pos = new sf::Vector2f();
    sf::Vector2f *vel = new sf::Vector2f();
    sf::Vector2f *acc = new sf::Vector2f();
    sf::CircleShape drawable;
    float mass;

    Particle() {};

    Particle(float x, float y, float mass, float radius) {
        if ( ! pos || ! vel || ! acc ) {
            // figure out how to handle errors!
            return;
        }
        pos->x = x; pos->y = y;
        drawable.setFillColor(sf::Color::White);
        drawable.setRadius(radius);
        drawable.setPosition(*pos);
        vel->x = 1; vel->y = -1;
        mass = mass;
    }

} particle;