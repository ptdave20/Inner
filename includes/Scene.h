//
// Created by ptdave on 11/27/16.
//

#ifndef INNER_SCENE_H
#define INNER_SCENE_H

#include <SFML/Audio.hpp>

#include "Map.h"
#include "Entity.h"
#include "Tile.h"
#include "Sprite.h"

#include <string>

#include <map>
#include <memory>
#include "json/json.h"
#include <fstream>
#include <ios>

class Scene {
public:
    //CONSTRUCTOR
    Scene() {
    }


    bool openFile(const std::string &file) {
        std::ifstream in(file, std::ifstream::binary);
        Json::Reader reader;
        Json::Value root;
        if (!in.is_open()) {
            return false;
        }

        auto success = reader.parse(in, root);
        if (!success) {
            return false;
        }

        auto vName = root["name"];
        auto vRes = root["resources"];
        auto vSprites = root["sprites"];
        auto vTriggers = root["triggers"];
        auto vType = root["type"];
        auto vMenus = root["menus"];

        if (!vName.empty() && vName.isString()) {
            setName(vName.asString());
        }

        if (!vRes.empty() && vRes.isArray()) {
            // Go through each resource and load it into our data
        }

        if (!vSprites.empty() && vRes.isArray()) {
            // Go through all the sprites and prepare it
        }

        if (!vType.empty() && vType.isString()) {
            // Set our scene type {Menu , map, etc..}
        }

        if (!vMenus.empty() && vMenus.isArray()) {
            // Load our menu options and prepare actions
        }
        in.close();
        return true;
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
        resources[name] = t;
        return true;
    }

    void update(const sf::Time &time) {

    }
private:
    sf::Music music;
    std::string name, type;
    std::map<std::string, std::shared_ptr<sf::Texture>> resources;
    std::map<std::string, std::shared_ptr<Sprite>> resSprites;
    std::map<std::string, std::shared_ptr<sf::Music>> resMusic;
};

#endif //INNER_SCENE_H