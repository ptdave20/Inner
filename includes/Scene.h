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
#include "Resource.h"

#include <string>

#include <map>
#include <memory>
#include "json/json.h"
#include <fstream>
#include <ios>
#include <locale>

class OnAction {
private:
    bool done;
public:
    bool isDone() const {
        return done;
    }

    void setDone(bool done) {
        OnAction::done = done;
    }

    const std::string &getDo_what() const {
        return do_what;
    }

    void setDo_what(const std::string &do_what) {
        OnAction::do_what = do_what;
    }

    const std::map<std::string, std::string> &getActions() const {
        return actions;
    }

    void setActions(const std::map<std::string, std::string> &actions) {
        OnAction::actions = actions;
    }
private:
    std::string do_what;
    std::map<std::string, std::string> actions;
};

class MenuOption {
public:
    const std::string &getText() const {
        return text;
    }

    void setText(const std::string &text) {
        MenuOption::text = text;
    }

    const std::vector<OnAction> &getOnSelect() const {
        return onSelect;
    }

    void setOnSelect(const std::vector<OnAction> &onSelect) {
        MenuOption::onSelect = onSelect;
    }

    const std::vector<OnAction> &getOnMouseOver() const {
        return onMouseOver;
    }

    void setOnMouseOver(const std::vector<OnAction> &onMouseOver) {
        MenuOption::onMouseOver = onMouseOver;
    }

    const std::vector<OnAction> &getOnMouseLeave() const {
        return onMouseLeave;
    }

    void setOnMouseLeave(const std::vector<OnAction> &onMouseLeave) {
        MenuOption::onMouseLeave = onMouseLeave;
    }

    const std::vector<OnAction> &getOnMouseClick() const {
        return onMouseClick;
    }

    void setOnMouseClick(const std::vector<OnAction> &onMouseClick) {
        MenuOption::onMouseClick = onMouseClick;
    }

    const std::vector<OnAction> &getOnMouseRelease() const {
        return onMouseRelease;
    }

    void setOnMouseRelease(const std::vector<OnAction> &onMouseRelease) {
        MenuOption::onMouseRelease = onMouseRelease;
    }

private:
    std::string text;
    std::vector<OnAction> onSelect;
    std::vector<OnAction> onMouseOver;
    std::vector<OnAction> onMouseLeave;
    std::vector<OnAction> onMouseClick;
    std::vector<OnAction> onMouseRelease;
};

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
        auto vRes = root["resTextures"];
        auto vSprites = root["sprites"];
        auto vTriggers = root["triggers"];
        auto vType = root["type"];
        auto vMenus = root["menus"];

        if (!vName.empty() && vName.isString()) {
            setName(vName.asString());
        }

        if (vType.isString()) {
            auto t = vType.asString();
            std::locale loc;
            for (std::string::size_type i = 0; i < t.length(); ++i)
                std::cout << std::tolower(t[i], loc);
            type = t;
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

        if (!vMenus.empty() && vMenus.isArray() && type == "menu") {
            // Load our menu options and prepare actions
            for (auto &menu : vMenus) {
                // Needs to be object, otherwise continue to the next
                if (!menu.isObject())
                    continue;
                MenuOption option;
                if (menu["text"].isString()) {
                    option.setText(menu["text"].asString());
                }
                menuOptions.push_back(option);
            }
        }

        if (root["resources"].isArray()) {
            for (auto res : root["resources"]) {
                // Needs to determine a type
                if (!res["type"].isString() || !res["name"].isString() || !res["file"].isString()) {
                    continue;
                }

                auto type = res["type"].asString();
                auto name = res["name"].asString();
                auto file = res["file"].asString();

                if (type == "music") {
                    if (loadMusic(name, file)) {
                        std::cout << "Loaded music resource : " << name << std::endl;
                        continue;
                    }
                }

                if (type == "texture") {
                    if (loadTexture(name, file)) {
                        std::cout << "Loaded texture resource : " << name << std::endl;
                    }
                }


            }
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
        std::shared_ptr<sf::Texture> t(new sf::Texture);
        if (!t->loadFromFile(file)) {
            return false;
        }
        resTextures[name] = t;
        return true;
    }

    bool loadMusic(std::string name, std::string file) {
        std::shared_ptr<sf::Music> t(new sf::Music);
        if (!t->openFromFile(file)) {
            return false;
        }
        resMusic[name] = t;
        return true;
    }

    void update(const sf::Time &time) {

    }
private:
    sf::Music music;
    std::string name, type;
    std::map<std::string, std::shared_ptr<sf::Texture>> resTextures;
    std::map<std::string, std::shared_ptr<Sprite>> resSprites;
    std::map<std::string, std::shared_ptr<sf::Music>> resMusic;
    std::vector<MenuOption> menuOptions;
};

#endif //INNER_SCENE_H