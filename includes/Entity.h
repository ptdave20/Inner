//
// Created by ptdave on 11/27/16.
//

#include <ostream>
#include "Inner.h"

#ifndef INNER_ENTITY_H
#define INNER_ENTITY_H


class Entity : public sf::Sprite {
private:
    std::string name;
    std::string state;
public:
    static void Register(sel::State &state) {
        state["Entity"].SetClass<Entity, std::string>(
                "getName", &Entity::getName,
                "setName", &Entity::setName,
                "getState", &Entity::getState,
                "setState", &Entity::setState
        );
    }

    Entity(std::string name) {
        this->name = name;
        this->state = "idle";
    }

    void update(const float time) {

    }

    const std::string getName() const {
        return name;
    }

    void setName(std::string v) {
        name = v;
    }

    const std::string getState() const {
        return state;
    }

    void setState(std::string v) {
        state = v;
    }

    friend std::ostream &operator<<(std::ostream &os, const Entity &entity) {
        os << entity.getName() << " ( " << entity.getPosition().x << " " << entity.getPosition().y << " )";
        return os;
    }
};


#endif //INNER_ENTITY_H
