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
};

class ParticleEngine : public BaseObject, public TextureResources {
private:
    std::vector<std::shared_ptr<Particle>> particles;
    std::function<void(std::shared_ptr<Particle>, const float &)> updateFunc;
    std::function<void(std::shared_ptr<Particle>)> renewFunc;
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
                .add(chaiscript::fun(&Particle::vectorRot), "vectorRot");
        ret->add(chaiscript::base_class<TextureResources,ParticleEngine>());
        return ret;
    }

    void update(const float &time) override {

        for (auto &p : particles) {
            if (p->life <= 0) {
                if(renewFunc) {
                    renewFunc(p);
                }

            }
            if(updateFunc) {
                updateFunc(p, time);
            }

        }
    }

    void setParticleTexture(Particle &p, std::string name){
        p.setTexture(getTexture(name));
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        for(const auto p : particles) {
            target.draw(*p,states);
        }
    }

    ParticleEngine(unsigned int size) : particles(size) {
        for(auto i=0; i<size; i++) {
            particles[i] = std::make_shared<Particle>();
        }
    }

    void setUpdateFunc(std::function<void(std::shared_ptr<Particle>, const float &)> update) {
        this->updateFunc = update;
    }

    void setRenewFunc(std::function<void(std::shared_ptr<Particle>)> renew) {
        this->renewFunc = renew;
    }
};


#endif //INNER_PARTICLEENGINE_H
