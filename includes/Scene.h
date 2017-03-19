//
// Created by ptdave on 11/27/16.
//

#include "Inner.h"

#ifndef INNER_SCENE_H
#define INNER_SCENE_H

typedef std::shared_ptr<Entity> SharedEntity;
typedef std::vector<SharedEntity> VectorEntity;
typedef std::map<std::string,VectorEntity> LayerEntity;


class Scene : public sf::Drawable, public sf::Transformable {
public:
    //CONSTRUCTOR
    Scene() {
        chai.add(chaiscript::Std_Lib::library());
    }

    void setName(std::string name) {
        this->name = name;
    }

    std::string getName() {
        return name;
    }

    void update(const sf::Time &delta) {
        for(auto &s : entities) {
            for(auto &e : s.second)
                e->update(delta);
        }
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        auto delta = transform * states.transform;

        for(auto lItr = entities.begin(); lItr!=entities.end(); lItr++) {
            for(auto itr = lItr->second.begin(); itr!=lItr->second.end(); itr++) {
                target.draw(*itr->get(),delta);
            }
        }
    }

    void addLayer(const std::string &name) {
        VectorEntity v;
        entities.insert(std::make_pair(name,v));
    }

    void addEntity(const std::string &name, SharedEntity entity) {
        entities[name].push_back(entity);
    }

    virtual bool load() = 0;


private:
    std::string name;
    LayerEntity entities;
    std::vector<std::string> renderOrder;
    sf::Transform transform;
    chaiscript::ChaiScript chai;

};

#endif //INNER_SCENE_H