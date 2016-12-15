//
// Created by ptdave on 11/27/16.
//

#include "Inner.h"

#ifndef INNER_ENTITY_H
#define INNER_ENTITY_H


class Entity : public sf::Sprite {
private:
    std::string name;
    sf::FloatRect spriteBounds;
    bool useBounds;
    sf::Vector2f vector;
public:
    Entity(const std::string &name = "Unnamed Entity") : name(name) {
        useBounds = false;
    }

    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name) {
        Entity::name = name;
    }

    const sf::FloatRect &getSpriteBounds() const {
        return spriteBounds;
    }

    void setSpriteBounds(const sf::FloatRect &spriteBounds) {
        Entity::spriteBounds = spriteBounds;
    }

    bool isUseBounds() const {
        return useBounds;
    }

    void setUseBounds(bool useBounds) {
        Entity::useBounds = useBounds;
    }

    const sf::Vector2f &getVector() const {
        return vector;
    }

    void setVector(const sf::Vector2f &vector) {
        Entity::vector = vector;
    }

    virtual void update(const sf::Time &time) = 0;
};


#endif //INNER_ENTITY_H
