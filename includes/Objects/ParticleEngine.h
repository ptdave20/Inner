//
// Created by ptdave on 3/29/17.
//

#include "../Inner.h"

#ifndef INNER_PARTICLEENGINE_H
#define INNER_PARTICLEENGINE_H

class Particle : public sf::Sprite {
public:
    sf::Vector2f vector;
    float life;
    float decay;
    float rotation;
    float vectorRot;

    Particle() {
        life = 0;
        decay = 0;
        rotation = 0;
        vectorRot = 0;
        setColor(sf::Color::White);
    }
    const sf::Color &getColor() {
        return sf::Sprite::getColor();
    }
    void setColor(const sf::Color &v) {
        sf::Sprite::setColor(v);
    }
    const sf::Vector2f& getPosition() {
        return sf::Sprite::getPosition();
    }
    void setPosition(const sf::Vector2f &v) {
        sf::Sprite::setPosition(v);
    }
    void setTexture(const sf::Texture &v) {
        sf::Sprite::setTexture(v);
    }

    void update(const float time) {
        auto p = getPosition();
        p += vector * time;
        setPosition(p);
        life -= decay * time;
    }
};

class ParticleEngine : public BaseObject, public TextureResources {
private:
    std::vector<Particle> particles;
    std::function<void(Particle &, const float &)> updateFunc;
    std::function<void(Particle &)> renewFunc;
public:
    static auto Library() {
        auto ret = std::make_shared<chaiscript::Module>();
        ret->add(chaiscript::user_type<ParticleEngine>(), "ParticleEngine")
                .add(chaiscript::constructor<ParticleEngine(unsigned int)>(), "ParticleEngine")
                .add(chaiscript::fun(&ParticleEngine::setUpdateFunc), "setUpdateFunc")
                .add(chaiscript::fun(&ParticleEngine::setRenewFunc), "setRenewFunc")
                .add(chaiscript::fun(&ParticleEngine::setParticleTexture),"setParticleTexture");
        ret->add(chaiscript::base_class<BaseObject, ParticleEngine>());
        ret->add(chaiscript::user_type<Particle>(), "Particle")
                .add(chaiscript::fun(&Particle::decay), "decay")
                .add(chaiscript::fun(&Particle::life), "life")
                .add(chaiscript::fun(&Particle::vector), "vector")
                .add(chaiscript::fun(&Particle::getPosition), "getPosition")
                .add(chaiscript::fun(&Particle::setPosition), "setPosition")
                .add(chaiscript::fun(&Particle::getColor), "getColor")
                .add(chaiscript::fun(&Particle::setColor), "setColor")
                .add(chaiscript::fun(&Particle::rotation), "rotation")
                .add(chaiscript::fun(&Particle::vectorRot), "vectorRot")
                .add(chaiscript::fun(&Particle::update), "update");
        ret->add(chaiscript::base_class<TextureResources,ParticleEngine>());
        return ret;
    }

    void update(const float &time) override {

        for (auto &p : particles) {
            if (p.life <= 0) {
                if(renewFunc) {
                    renewFunc(p);
                }

            }
            if(updateFunc) {
                updateFunc(p, time);
            }

        }
    }

    void setParticleTexture(std::string name) {
        for (auto &p : particles)
            p.setTexture(getTexture(name));
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        for (const auto &p : particles) {
            target.draw(p, states);
        }
    }

    ParticleEngine(unsigned int size) : particles(size) {
        for(auto i=0; i<size; i++) {
            particles[i] = Particle();
        }
    }

    void setUpdateFunc(std::function<void(Particle &, const float &)> update) {
        this->updateFunc = update;
    }

    void setRenewFunc(std::function<void(Particle &)> renew) {
        this->renewFunc = renew;
    }
};


#endif //INNER_PARTICLEENGINE_H
