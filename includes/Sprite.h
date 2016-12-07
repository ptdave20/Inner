//
// Created by ptdave on 12/6/16.
//

#ifndef INNER_SPRITE_H
#define INNER_SPRITE_H

#include <SFML/Graphics.hpp>
#include "json/json.h"
#include "Scene.h"

class Sprite {
public:
    Sprite(const Scene &scene, const Json::Value &value) {

    }

private:
    std::string name;
    sf::FloatRect rect;
    sf::Sprite sprite;
};


#endif //INNER_SPRITE_H
