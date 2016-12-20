//
// Created by ptdave on 11/27/16.
//

#include "Inner.h"

#ifndef INNER_ENTITY_H
#define INNER_ENTITY_H


class Entity {
private:
    std::string name;
    Sprite *sprite;
public:
    static void Register(sel::State &state) {
        state["Entity"].SetClass<Entity, std::string>(
                "setSprite", &Entity::setSprite
        );
    }

    Entity(std::string name) {
        this->name = name;
    }

    void setSprite(Sprite *sprite) {
        this->sprite = sprite;
    }
};


#endif //INNER_ENTITY_H
