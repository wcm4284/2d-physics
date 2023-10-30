#include <SFML/Graphics.hpp>

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
        vel->x = 0; vel->y = 0;
        acc->x = 0; acc->y = 0;
        drawable.setFillColor(sf::Color::White);
        drawable.setRadius(radius);
        drawable.setPosition(*pos);
        mass = mass;
    }

} particle;