//
// Created by ptdave on 11/27/16.
//

#include <ostream>
#include "Inner.h"

#ifndef INNER_ENTITY_H
#define INNER_ENTITY_H


class BaseObject : public sf::Drawable, public sf::Transformable {
private:
    std::string name;
    UpdateFunction<BaseObject *> updateFunc;
public:
    BaseObject() {
        name = "Unnamed Object";
    }
    virtual ~BaseObject() = default;

    // Called when the object needs to be reset. Either a scene is over or needs to be reused
    virtual void reset() {

    }

    virtual void update(const float &time) {
        updateFunc(this, time);
    }

    virtual void update(const sf::Time &time) {
        updateFunc(this, time.asSeconds());
    }

    const std::string &getName() const {
        return name;
    }


    void setName(const std::string &v) {
        name = v;
    }

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        // Draw sprites or whatever here
    }

    virtual void handleEvent(sf::Event &event) {
        // Do nothing by default
    }

    void setPosition(float x, float y) {
        sf::Transformable::setPosition(x,y);
    }

    void setOrigin(float x, float y) {
        sf::Transformable::setOrigin(x,y);
    }

    void setRotation(float x) {
        sf::Transformable::setRotation(x);
    }

    void setScale(float x,float y) {
        sf::Transformable::setScale(x,y);
    }

    static chaiscript::ModulePtr Library() {
        chaiscript::ModulePtr ret = std::make_shared<chaiscript::Module>();


        ret->add(chaiscript::constructor<sf::Transformable()>(),"Transformable")
                .add(chaiscript::fun(&sf::Transformable::getInverseTransform),"getInverseTransform")
                .add(chaiscript::fun(&sf::Transformable::getOrigin),"getOrigin")
                .add(chaiscript::fun(&sf::Transformable::getPosition),"getPosition")
                .add(chaiscript::fun(&sf::Transformable::getRotation),"getRotation")
                .add(chaiscript::fun(&sf::Transformable::setRotation),"setRotation")
                .add(chaiscript::fun(&sf::Transformable::getScale),"getScale");
        ret->add(chaiscript::base_class<sf::Transformable,BaseObject>());
        ret->add(chaiscript::constructor<BaseObject()>(), "BaseObject")
                .add(chaiscript::fun(&BaseObject::getName), "getName")
                .add(chaiscript::fun(&BaseObject::setName), "setName")
                .add(chaiscript::fun(&BaseObject::setPosition),"setPosition")
                .add(chaiscript::fun(&BaseObject::setOrigin),"setOrigin")
                .add(chaiscript::fun(&BaseObject::setRotation),"setRotation")
                .add(chaiscript::fun(&BaseObject::setScale),"setScale")
                .add(chaiscript::fun(&BaseObject::print), "print");
        return ret;
    }

    void print() {
        std::cout << getName() + " ( " + std::to_string(getPosition().x) + " x " + std::to_string(getPosition().y) + " )" << std::endl;
    }
};


#endif //INNER_ENTITY_H
