#include <SFML/Graphics.hpp>

class Particle : public sf::Transformable {
    struct {
        float x_, y_;
    } pos_, vel_, acc_;

    float mass_, radius_;

    Particle() {
        vel_.x_ = 0;
        vel_.y_ = 0;
        acc_.x_ = 0;
        acc_.y_ = 0;
        radius_ = 1;
        mass_ = 1;
    }

    Particle(float x, float y) {
        pos_.x_ = x;
        pos_.y_ = y;
        Particle();
    }

    Particle(float x, float y, float mass, float radius) {
        radius_ = radius;
        mass_ = mass;
        Particle(x, y);
    }
};