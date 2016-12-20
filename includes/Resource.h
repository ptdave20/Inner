//
// Created by ptdave on 12/7/16.
//

#include "Inner.h"

#ifndef INNER_RESOURCE_H
#define INNER_RESOURCE_H


template<typename T>
class Resource {
public:
    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name) {
        Resource::name = name;
    }

    const std::string &getPath() const {
        return path;
    }

    void setPath(const std::string &path) {
        Resource::path = path;
    }

    const std::string &getType() const {
        return type;
    }

    void setType(const std::string &type) {
        Resource::type = type;
    }

	virtual bool load() = 0;
	virtual void unload() {
		if (value) {
			value.reset();
		}
	}

	std::shared_ptr<T> getValue() {
		if (value) {
			return value;
		}
		return nullptr;
	}
protected:
    std::string path;
    std::string type;
    std::string name;
	std::shared_ptr<T> value;
};

class MusicResource : Resource<sf::Music> {
public:
    MusicResource(std::string file) {
        path = file;
        load();
    }

    ~MusicResource() {
        if (value) {
            unload();
        }
    }
    virtual bool load() {
		if (value) {
			unload();
		}
		value = std::shared_ptr<sf::Music>(new sf::Music);
		return value->openFromFile(path);
	}

    operator Json::Value() {
		Json::Value ret;
		ret["type"] = "music";
		ret["name"] = name;
		ret["file"] = path;
		return ret;
	}

    void play() {
        if (value) {
            value->play();
        }
    }

    void stop() {
        if (value) {
            value->stop();
        }
    }

    float getDuration() {
        if (value) {
            value->getDuration();
        }
		return 0;
    }

    float getCurrentTime() {
        if (value) {
            value->getPlayingOffset().asSeconds();
        }
		return 0;
    }

    void setCurrentTime(const float &v) {
        if (value) {
            sf::Time t;
            value->setPlayingOffset(sf::seconds(v));
        }
    }

    void setVolume(const float &v) {
        if (value) {
            value->setVolume(v);
        }
    }

    const float getVolume(const float &v) {
        return value->getVolume();
    }

    void setLoop(const bool v) {
        if (value) {
            value->setLoop(v);
        }
    }

    bool getLoop() {
        if (value) {
            return value->getLoop();
        }

        return false;
    }

    static void Register(sel::State &state) {
        state["MusicResource"].SetClass<MusicResource, std::string>(
                "play", &MusicResource::play,
                "stop", &MusicResource::stop,
                "getDuration", &MusicResource::getDuration,
                "getCurrentTime", &MusicResource::getCurrentTime,
                "setCurrentTime", &MusicResource::setCurrentTime,
                "getVolume", &MusicResource::getVolume,
                "setVolume", &MusicResource::setVolume,
                "getLoop", &MusicResource::getLoop,
                "setLoop", &MusicResource::setLoop
        );
    }
};

class TextureResource : Resource<sf::Texture> {
public:
    virtual bool load() {
		if (value) {
			unload();
		}
        value = std::shared_ptr<sf::Texture>(new sf::Texture);
		return value->loadFromFile(path);
	}

    operator Json::Value() {
		Json::Value ret;
		ret["type"] = "texture";
		ret["name"] = name;
		ret["file"] = path;
		return ret;
	}

    static void Register(sel::State &state) {
        state["TextureResource"].SetClass<TextureResource>();
    }
};

class FontResource : Resource<sf::Font> {
public:
    virtual bool load() {
        if (value) {
            unload();
        }
        value = std::shared_ptr<sf::Font>(new sf::Font);
        return value->loadFromFile(path);
    }

    operator Json::Value() {
        Json::Value ret;
        ret["type"] = "font";
        ret["name"] = name;
        ret["file"] = path;
        return ret;
    }
};

#endif //INNER_RESOURCE_H
