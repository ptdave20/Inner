//
// Created by ptdave on 3/29/17.
//

#include "../Inner.h"

#ifndef INNER_PARTICLEENGINE_H
#define INNER_PARTICLEENGINE_H

class Particle {
public:
    float vectorX, vectorY;
    float posX, posY;
    float life;
    float decay;

    Particle() {
        vectorX = 0;
        vectorY = 0;
        posX = 0;
        posY = 0;
        life = 0;
        decay = 0;
    }
};

class ParticleEngine : public BaseObject {
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
                .add(chaiscript::fun(&ParticleEngine::setRenewFunc), "setRenewFunc");
        ret->add(chaiscript::base_class<BaseObject, ParticleEngine>());
        ret->add(chaiscript::user_type<Particle>(), "Particle")
                .add(chaiscript::fun(&Particle::decay), "decay")
                .add(chaiscript::fun(&Particle::life), "life")
                .add(chaiscript::fun(&Particle::vectorX), "vectorX")
                .add(chaiscript::fun(&Particle::vectorY), "vectorY")
                .add(chaiscript::fun(&Particle::posX), "posX")
                .add(chaiscript::fun(&Particle::posY), "posY");
        return ret;
    }

    void update(const float &time) override {
        for (auto &p : particles) {
            if ((*p).life <= 0) {
                renewFunc(p);
            }
            updateFunc(p, time);
        }
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        BaseObject::draw(target, states);
    }

    ParticleEngine(unsigned int size) : particles(size) {

    }

    void setUpdateFunc(std::function<void(std::shared_ptr<Particle>, const float &)> update) {
        this->updateFunc = update;
    }

    void setRenewFunc(std::function<void(std::shared_ptr<Particle>)> renew) {
        this->renewFunc = renew;
    }
};


#endif //INNER_PARTICLEENGINE_H
