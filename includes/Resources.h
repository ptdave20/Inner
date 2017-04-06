//
// Created by ptdave on 3/19/17.
//

#include "Inner.h"

#ifndef INNER_RESOURCES_H
#define INNER_RESOURCES_H

class TextureResources {
public:
    static auto Library() {
        auto ret = std::make_shared<chaiscript::Module>();

        ret->add(chaiscript::user_type<TextureResources>(), "TextureResources")
                .add(chaiscript::fun(&TextureResources::loadTexture), "loadTexture")
                .add(chaiscript::fun(&TextureResources::getTexture), "getTexture");

        return ret;
    }

    ~TextureResources() {
        textures.clear();
    }

    sf::Texture &getTexture(std::string v) {
        return textures[v];
    }

    bool loadTexture(std::string name, std::string path) {
        sf::Texture t;
        if (t.loadFromFile(path)) {
            textures[name] = t;
            return true;
        }
        return false;
    }

private:
    std::map<std::string, sf::Texture> textures;
};

class Resources : public TextureResources {
public:
    ~Resources() {
        fonts.clear();
        sfx.clear();
    }
    sf::Font& getFont(std::string v) {
        return fonts[v];
    }
    bool loadFont(std::string name, std::string path) {
        sf::Font f;
        if(f.loadFromFile(path)) {
            fonts[name] = f;
            return true;
        }
        return false;
    }


    sf::SoundBuffer getSfx(std::string v) {
        return sfx[v];
    }
    bool loadSfx(std::string name, std::string path) {
        sf::SoundBuffer s;
        if(s.loadFromFile(path)) {
            sfx[name] = s;
            return true;
        }
        return false;
    }
private:
    std::map<std::string,sf::Font> fonts;
    std::map<std::string,sf::SoundBuffer> sfx;
};


#endif //INNER_RESOURCES_H
