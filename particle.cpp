#include <SFML/Graphics.hpp>
#include <cmath>

extern const int c_screenheight;
extern const int c_screenwidth;
extern const float g;

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
        if ( ! pos || ! vel || ! acc ) {
            // figure out how to handle errors!
            return;
        }
        pos->x = x; pos->y = y;
        vel->x = 0; vel->y = 0;
        acc->x = 0; acc->y = -g;
        drawable.setFillColor(sf::Color::White);
        drawable.setRadius(radius);
        drawable.setPosition(*pos);
        this->radius = radius;
        this->mass = mass;
    }

    void resolveWallCollision() {
        if (pos->x + radius > c_screenwidth || pos->x - radius < 0) {
            vel->x = -vel->x;
        }
        if (pos->y + radius > c_screenheight || pos->y - radius < 0) {
            vel->y = -vel->y;
        }
    }
    int resolveCollision(Particle &other) {
        float dst = getDistance(*other.pos);
        if (dst < radius + other.radius) {
            calculateForce(other);
            return 1;
        }
        return 0;
    }

    void calculateForce(Particle &other) {}

    void applyForce(Particle &other) {}
    
    float getDistance(sf::Vector2f &point) {
        float x, y;
        x = pos->x - point.x;
        y = pos->y - point.y;
        return sqrtf((x * x) + (y * y));
    }

} particle;