//
// Created by ptdave on 12/22/16.
//

#include "Inner.h"

#ifndef INNER_PARTICLEENGINE_H
#define INNER_PARTICLEENGINE_H

class Particle : public sf::Vector2f {

};

class ParticleEngine : public sf::Drawable {
public:
    static void Register(sel::State &state) {

    }

    ParticleEngine(unsigned int size) : particles(size) {
        for (int i = 0; i < size; i++) {
            particles[i] = Particle();
        }
    }

    void setTexture(TextureResource texture) {
        this->texture = texture;
    }

    void update(const float &time) {
        for (auto &particle : particles) {

        }
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        auto xform = states.transform * xform;
        for (const auto &v : particles) {

        }
    }

private:
    std::vector<Particle> particles;
    TextureResource texture;
    sf::Transform xform;
};


#endif //INNER_PARTICLEENGINE_H
