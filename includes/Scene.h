//
// Created by ptdave on 11/27/16.
//

#include "Inner.h"

#ifndef INNER_SCENE_H
#define INNER_SCENE_H

typedef sel::function<int(float)> LuaRendererFunc;

class Scene : public sf::Drawable, public sf::Transformable {
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

    void update(const sf::Time &delta) {
        // Do all the backend work, then call our luaFunc for other work
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        auto delta = transform * states.transform;
        for (const auto &obj : entities) {
            target.draw(*obj, delta);
        }
    }

private:
    std::string name;
    std::vector<Entity *> entities;
    sf::Transform transform;
};

#endif //INNER_SCENE_H