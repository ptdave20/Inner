//
// Created by ptdave on 11/27/16.
//

#include "Inner.h"

#ifndef INNER_SCENE_H
#define INNER_SCENE_H

typedef std::shared_ptr<BaseObject> SharedEntity;
typedef std::vector<SharedEntity> VectorEntity;
typedef std::map<std::string,VectorEntity> LayerEntity;


class Scene : public BaseObject, public Resources {
public:
    //CONSTRUCTOR
    Scene() {
        setName("Unnamed Scene");
    }

    virtual void init(unsigned int screenWidth, unsigned int screenHeight) {

    }

    virtual void deinit() {

    }

    static chaiscript::ModulePtr Library() {
        chaiscript::ModulePtr ret = std::make_shared<chaiscript::Module>();

        ret->add(chaiscript::user_type<sf::Font>(),"Font");
        ret->add(chaiscript::constructor<sf::Font()>(),"Font");

        ret->add(chaiscript::user_type<Resources>(),"Resources")
                .add(chaiscript::constructor<Resources()>(),"Resources")
                .add(chaiscript::fun(&Resources::loadFont),"loadFont")
                .add(chaiscript::fun(&Resources::getFont),"getFont");

        ret->add(chaiscript::user_type<Scene>(),"Scene")
                .add(chaiscript::constructor<Scene()>(),"Scene")
                .add(chaiscript::fun(&Scene::loadFont),"loadFont")
                .add(chaiscript::fun(&Scene::loadSfx),"loadSfx")
                .add(chaiscript::fun(&Scene::loadTexture),"loadTexture")
                .add(chaiscript::fun(&Scene::setUpdate),"setUpdate")
                .add(chaiscript::fun(&Scene::addLayer),"addLayer")
                .add(chaiscript::fun(&Scene::addEntity),"addEntity");
        ret->add(chaiscript::base_class<BaseObject,Scene>());
        ret->add(chaiscript::base_class<Resources,Scene>());
        return ret;
    }

    void update(const sf::Time &delta) override {
        if(updateFunc)
            updateFunc(delta.asSeconds());
        for(auto &s : entities) {
            for(auto &e : s.second)
                e->update(delta.asSeconds());
        }
    }

    void update(const float &delta) override {
        if(updateFunc)
            updateFunc(delta);
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

    void setUpdate(std::function<void(float)> func) {
        updateFunc = func;
    }
private:
    LayerEntity entities;
    sf::Transform transform;
    std::function<void(float)> updateFunc;
};

#endif //INNER_SCENE_H