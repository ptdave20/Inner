//
// Created by ptdave on 11/27/16.
//

#include "Inner.h"

#ifndef INNER_SCENE_H
#define INNER_SCENE_H

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

    void setLuaRender(sel::function<int(float)> luaFunc) {
        this->luaFunc = luaFunc;
    }
private:
    std::string name;
    sel::function<int(float)> luaFunc;
};

#endif //INNER_SCENE_H