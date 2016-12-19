//
// Created by ptdave on 12/6/16.
//

#include "Inner.h"

#ifndef INNER_SPRITE_H
#define INNER_SPRITE_H

class SpriteAnimation {
public:
    static void Register(sel::State &state) {
        state["SpriteAnimation"].SetClass<SpriteAnimation>(
                "add", &SpriteAnimation::add,
                "size", &SpriteAnimation::size,
                "setLoop", &SpriteAnimation::setLoop,
                "getLoop", &SpriteAnimation::getLoop
        );
    }

    SpriteAnimation() {
        time = 0;
        current = 0;
        loop = false;
    }

    void add(int left, int top, int width, int height) {
        rect.push_back(sf::IntRect(left, top, width, height));
    }

    sf::IntRect &operator[](const int &i) {
        return rect[i];
    }

    const unsigned long size() {
        return rect.size();
    }

    void setLoop(const bool v) {
        loop = v;
    }

    bool getLoop() {
        return loop;
    }

    const sf::IntRect &update(const float &v) {
        current += v;
        while (current >= time) {
            current -= time;
        }

        return rect[static_cast<int>(current / time)];
    }

private:
    bool loop;
    float time, current;
    std::vector<sf::IntRect> rect;
};

class Sprite {
public:
    Sprite(std::string name) {
        setName(name);
    }

    static void Register(sel::State &state) {
        SpriteAnimation::Register(state);
        state["Sprite"].SetClass<Sprite, std::string>(
                "addAnimation", &Sprite::addAnimation,
                "getName", &Sprite::getName,
                "setName", &Sprite::setName
        );
    }

    void setName(std::string _name) {
        name = _name;
    }

    const std::string getName() {
        return name;
    }

    void addAnimation(std::string name, SpriteAnimation anim) {
        animations[name] = anim;
    }

private:
    std::string name;
    sf::Sprite sprite;
    std::map<std::string, SpriteAnimation> animations;
};


#endif //INNER_SPRITE_H
