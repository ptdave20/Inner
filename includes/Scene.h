//
// Created by ptdave on 11/27/16.
//

#include "Inner.h"

#ifndef INNER_SCENE_H
#define INNER_SCENE_H

typedef std::shared_ptr<BaseObject> SharedEntity;
typedef std::vector<SharedEntity> VectorEntity;
typedef std::map<std::string,VectorEntity> LayerEntity;


class Scene : public BaseObject, protected Resources {
public:
    //CONSTRUCTOR
    Scene() {
        this->setName("Unnamed Scene");
    }

    static chaiscript::ModulePtr Library() {
        chaiscript::ModulePtr ret = std::make_shared<chaiscript::Module>();

        ret->add(chaiscript::base_class<BaseObject,Scene>())
                .add(chaiscript::user_type<Scene>(),"Scene")
                .add(chaiscript::fun(&Scene::loadFont),"loadFont")
                .add(chaiscript::fun(&Scene::loadSfx),"loadSfx")
                .add(chaiscript::fun(&Scene::loadTexture),"loadTexture");
        return ret;
    }

    void update(const sf::Time &delta) {
        for(auto &s : entities) {
            for(auto &e : s.second)
                e->update(delta.asSeconds());
        }
    }

    void update(const float &delta) {
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
    LayerEntity entities;
    sf::Transform transform;

};

#endif //INNER_SCENE_H