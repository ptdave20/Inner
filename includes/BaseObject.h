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

    static chaiscript::ModulePtr Library() {
        chaiscript::ModulePtr ret = std::make_shared<chaiscript::Module>();

        ret->add(chaiscript::constructor<BaseObject()>(), "BaseObject")
                .add(chaiscript::fun(&BaseObject::getName), "getName")
                .add(chaiscript::fun(&BaseObject::setName), "setName")
                .add(chaiscript::fun(&BaseObject::print), "print");
        return ret;
    }

    BaseObject &operator()(chaiscript::ChaiScript &chai) {
        chai.add(chaiscript::user_type<sf::Drawable>(), "Drawable");
        chai.add(chaiscript::user_type<sf::Transformable>(), "Transformable");
        chai.add(chaiscript::user_type<BaseObject>(), "BaseObject")
                .add(chaiscript::fun(&BaseObject::getName), "getName")
                .add(chaiscript::fun(&BaseObject::reset), "reset")
                .add(chaiscript::fun(&BaseObject::getScale), "getScale")
                .add(chaiscript::fun(&BaseObject::getOrigin), "getOrigin")
                .add(chaiscript::fun(&BaseObject::getRotation), "getRotation")
                .add(chaiscript::fun(&BaseObject::setRotation), "setRotation")
                .add(chaiscript::fun(&BaseObject::getTransform), "getTransform")
                .add(chaiscript::fun(&BaseObject::getInverseTransform), "getInverseTransform")
                .add(chaiscript::fun(&BaseObject::getPosition), "getPosition");
    }

    void print() {
        std::cout << *this << std::endl;
    }

    operator const char*() {
        return std::string(getName() + " ( " + std::to_string(getPosition().x) + " x " + std::to_string(getPosition().y) + " )").c_str();
    }
    friend std::ostream &operator<<(std::ostream &os, const BaseObject &entity) {
        using namespace std;
        os << entity;
        return os;
    }
};


#endif //INNER_ENTITY_H
