//
// Created by ptdave on 11/27/16.
//

#ifndef INNER_SCENE_H
#define INNER_SCENE_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Entity.h"
#include "Tile.h"
#include "Sprite.h"
#include "Resource.h"
#include "Action.h"
#include "Menu.h"

#include <string>

#include <map>
#include <memory>
#include "json/json.h"
#include <fstream>
#include <ios>
#include <locale>




class Scene {
public:
    //CONSTRUCTOR
    Scene() {
    }

	void save(const std::string &file) {
		std::ofstream out(file, std::ofstream::binary);

		if (out.is_open()) {
			Json::Value root;
			 
			root["name"] = name;
			root["type"] = type;
			if (type == "menu") {
				root["menus"].clear();
				for (auto &s : menuOptions) {
					root["menus"].append(s);
				}
			}
            //root["resTextures"] = Json::Value;
            //root["resMusic"] = Json::Value;
            //root["resFont"] = Json::Value;

			out << root << std::endl;

			out.close();
		}
	}

	operator Json::Value &() {
		Json::Value ret;

		ret["name"] = name;
		ret["type"] = type;
		if (type == "menu") {
			ret["menus"].clear();
			for (auto &s : menuOptions) {
				ret["menus"].append(s);
			}
		}



		return ret;
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
                        continue;
                    }
                }

                if (type == "font") {
                    if (loadFont(name, file)) {
                        std::cout << "Loaded font resource : " << name << std::endl;
                        continue;
                    }
                }

            }
        }
        in.close();
        return true;
    }

    // MUSIC CONTROLS
    void loadMusic(std::string file) {
		if (music) {
			music->stop();
			music->setPlayingOffset(sf::Time::Zero);
		}

		music = std::shared_ptr<sf::Music>(new sf::Music);
        music->openFromFile(file);
    }

	void loadMusicResource(std::string res) {
		if (music) {
			music->stop();
			music->setPlayingOffset(sf::Time::Zero);
		}

		if (resMusic[res] != nullptr) {
			music = resMusic[res];
		}
	}

	const sf::Time getMusicPosition() {
		if (music) {
			return music->getPlayingOffset();
		}

		return sf::Time::Zero;
	}

	const sf::Time getMusicDuration() {
		if (music) {
			return music->getDuration();
		}

		return sf::Time::Zero;
	}

	bool isMusicPlaying() {
		if (music) {
			music->getStatus() == sf::Music::Playing;
		}
		return false;
	}

    void startMusic() {
		if(music)
			music->play();
    }

    void stopMusic() {
		if(music)
			music->stop();
    }

    void setMusicVolume(const float &n) {
		if(music)
			music->setVolume(n);
    }

    const float getMusicVolume() {
		if(music)
			return music->getVolume();
		return 0;
    }

    void setMusicLoop(bool value) {
		if(music)
			music->setLoop(value);
    }

    bool getMusicLoop() {
		if(music)
			return music->getLoop();
		return false;
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

	void removeMusicResource(std::string name) {
		if (resMusic[name]) {
			resMusic.erase(name);
		}
	}

    bool loadFont(std::string name, std::string file) {
        std::shared_ptr<sf::Font> t(new sf::Font);
        if (!t->loadFromFile(file)) {
            return false;
        }
        resFont[name] = t;
        return true;
    }

    std::vector<std::string> getTextureKeys() {
        std::vector<std::string> keys;
        for (const auto &k : resTextures) {
            keys.push_back(k.first);
        }
        return keys;
    }

    std::vector<std::string> getMusicKeys() {
        std::vector<std::string> keys;
        for (const auto &k : resTextures) {
            keys.push_back(k.first);
            std::cout << k.first << std::endl;
        }
        return keys;
    }

    void update(const sf::Time &time) {

    }

	
private:
    std::shared_ptr<sf::Music> music;
    std::string name, type;
    std::map<std::string, std::shared_ptr<sf::Texture>> resTextures;
    std::map<std::string, std::shared_ptr<Sprite>> resSprites;
    std::map<std::string, std::shared_ptr<sf::Music>> resMusic;
public:
    const std::map<std::string, std::shared_ptr<sf::Texture>> &getResTextures() const {
        return resTextures;
    }

    const std::map<std::string, std::shared_ptr<sf::Music>> &getResMusic() const {
        return resMusic;
    }

    const std::map<std::string, std::shared_ptr<sf::Font>> &getResFont() const {
        return resFont;
    }

private:
    std::map<std::string, std::shared_ptr<sf::Font>> resFont;
    std::vector<MenuOption> menuOptions;
};

#endif //INNER_SCENE_H