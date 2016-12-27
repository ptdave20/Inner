//
// Created by ptdave on 12/22/16.
//

#include "Inner.h"

#ifndef INNER_PARTICLEENGINE_H
#define INNER_PARTICLEENGINE_H

class Particle : public sf::Sprite {

};

class ParticleEngine : public sf::Drawable, sf::Transformable {
public:
    static void Register(sel::State &state) {
        state["ParticleEngine"].SetClass<ParticleEngine, int>(
                "setTexture", &ParticleEngine::setTexture,
                "setUpdateParticle", &ParticleEngine::setUpdateParticle,
                "setPosition", &ParticleEngine::setPosition
        );
    }

    ParticleEngine(int size) : particles(size) {
        for (int i = 0; i < size; i++) {
            particles[i] = Particle();
            particles[i].setTexture(*texture);
        }
    }

    void setTexture(TextureResource texture) {
        this->texture = texture;
    }

    void update(const float &time) {
        for (auto &particle : particles) {

        }
    }

    void setUpdateParticle(sel::function<void(Particle *)> *fun) {
        updateParticle = fun;
    }

    void setPosition(float x, float y) {
        sf::Transformable::setPosition(sf::Vector2f(x, y));
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        sf::Transform xform = states.transform * xform;
        for (const auto &v : particles) {
            target.draw(v, xform);
        }
    }

private:
    std::vector<Particle> particles;
    TextureResource texture;
    sf::Transform xform;
    sf::Vector2f high, low;
    sel::function<void(Particle *)> *updateParticle;
};


#endif //INNER_PARTICLEENGINE_H
