//
// Created by ptdave on 11/27/16.
//

#ifndef INNER_SCENE_H
#define INNER_SCENE_H

#include <SFML/Audio.hpp>

#include "Map.h"
#include "Entity.h"
#include "Tile.h"

#include <string>
#include <selene.h>

#include <map>
#include <memory>

using namespace sel;

class Scene {
public:
    //CONSTRUCTOR
    Scene(std::string _name) {
        name = name;
    }


    // MUSIC CONTROLS
    void loadMusic(std::string file) {
        music.openFromFile(file);
    }

    void startMusic() {
        music.play();
    }

    void stopMusic() {
        music.stop();
    }

    void setMusicVolume(const float &n) {
        music.setVolume(n);
    }

    const float getMusicVolume() {
        return music.getVolume();
    }

    void setMusicLoop(bool value) {
        music.setLoop(value);
    }

    bool getMusicLoop() {
        return music.getLoop();
    }


    // NAME CONTROLS
    std::string getName() {
        return name;
    }

    void setName(std::string _name) {
        name = _name;
    }

    // RESOURCE CONTROLS
    bool loadTexture(std::string name, std::string file) {
        std::shared_ptr<sf::Texture> t;
        if (!t->loadFromFile(file)) {
            return false;
        }
        textureResources[name] = t.shared_ptr();
        return true;
    }

    void update(const sf::Time &time) {

    }
private:
    sf::Music music;
    std::string name;
    std::map<std::string, std::shared_ptr<sf::Texture>> textureResources;
};

void SceneLua(sel::State &state) {
    state["Scene"].SetClass<Scene, std::string>(

            // MUSIC CONTROLS
            "loadMusic", &Scene::loadMusic,
            "startMusic", &Scene::startMusic,
            "stopMusic", &Scene::stopMusic,
            "setMusicVolume", &Scene::setMusicVolume,
            "getMusicVolume", &Scene::getMusicVolume,
            "setMusicLoop", &Scene::setMusicLoop,
            "getMusicLoop", &Scene::getMusicLoop,

            // NAME CONTROLS
            "getName", &Scene::getName,
            "setName", &Scene::setName,

            // LOAD RESOURCES
            "loadTexture", &Scene::loadTexture
    );
}


#endif //INNER_SCENE_H