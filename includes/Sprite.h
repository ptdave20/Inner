//
// Created by ptdave on 12/6/16.
//

#ifndef INNER_SPRITE_H
#define INNER_SPRITE_H

#include <SFML/Graphics.hpp>
#include "json/json.h"
#include "Scene.h"

struct SpriteAnimation {
    std::string name;
    std::vector<sf::IntRect> rect;
};

class Sprite {
public:
    void setName(std::string &_name) {
        name = _name;
    }

    const std::string &getName() {
        return name;
    }

    void addAnimation(std::string name) {
        SpriteAnimation anim;
        anim.name = name;

        animations.push_back(anim);
    }

private:
    std::string name;
    sf::Sprite sprite;
    std::vector<SpriteAnimation> animations;
};


#endif //INNER_SPRITE_H
