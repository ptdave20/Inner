//
// Created by ptdave on 11/27/16.
//

#include "Inner.h"

#ifndef INNER_SCENE_H
#define INNER_SCENE_H

typedef sel::function<int(float)> LuaRendererFunc;

class Scene {
public:
    //CONSTRUCTOR
    Scene() {
    }

    static void Register(sel::State &state) {
        state["Scene"].SetClass<Scene>(
                "setName", &Scene::setName,
                "getName", &Scene::getName
        );
    }

    void setName(std::string name) {
        this->name = name;
    }

    std::string getName() {
        return name;
    }

    void render(const sf::Time &delta) {
        // Do all the backend work, then call our luaFunc for other work
    }
private:
    std::string name;
};

#endif //INNER_SCENE_H