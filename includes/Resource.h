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

    Resource<T> &operator=(const Resource<T> &v) {
        this->value = v.value;
        this->name = v.name;
        this->type = v.type;
        this->path = v.path;
        return *this;
    }

    operator std::shared_ptr<T>() {
        return value;
    }

	std::shared_ptr<T> getValue() {
		if (value) {
			return value;
		}
		return nullptr;
	}

    T &operator*() {
        if (value) {
            return *value;
        }
        throw std::runtime_error("Null resource");
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

class TextureResource : public Resource<sf::Texture> {
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

    friend class SpriteResource;
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

class SpriteAnimation {
public:
    static void Register(sel::State &state) {
        state["SpriteAnimation"].SetClass<SpriteAnimation>(
                "add", &SpriteAnimation::add,
                "size", &SpriteAnimation::size,
                "setLoop", &SpriteAnimation::setLoop,
                "getLoop", &SpriteAnimation::getLoop
        );
    }

    SpriteAnimation() {
        time = 0;
        loop = false;
    }

    void add(int left, int top, int width, int height) {
        rect.push_back(sf::IntRect(left, top, width, height));
    }

    sf::IntRect &operator[](const int &i) {
        return rect[i];
    }

    const unsigned long size() {
        return rect.size();
    }

    void setLoop(const bool v) {
        loop = v;
    }

    bool getLoop() {
        return loop;
    }

    operator Json::Value() {
        Json::Value ret;
        ret["loop"] = loop;
        ret["time"] = time;
        for (const auto &i : rect) {
            Json::Value r;
            r.append(i.left);
            r.append(i.top);
            r.append(i.width);
            r.append(i.height);

            ret["rect"] = r;
        }
        return ret;
    }

private:
    bool loop;
    float time;
    std::vector<sf::IntRect> rect;
};

class SpriteResource : Resource<sf::Sprite> {
public:
    static void Register(sel::State &state) {
        SpriteAnimation::Register(state);
        state["SpriteResource"].SetClass<SpriteResource>(

        );
    }

    SpriteResource() {

    }

    SpriteResource(TextureResource resource) {
        this->texture = resource;
    }

    void addAnimation(std::string name, SpriteAnimation anim) {
        animations[name] = anim;
    }

    virtual bool load() {
        std::ifstream f;
        f.open(path, std::ios::binary);
        if (!f.is_open() && !f.good()) {
            return false;
        }

        Json::Reader reader;
        Json::Value root;
        if (!reader.parse(f, root)) {
            return false;
        }

        if (root["animations"].isArray()) {
            for (const auto &anim : root["animations"]) {
                SpriteAnimation a;
                std::string name = anim["name"].asString();
                for (const auto &r : anim["rect"]) {
                    a.add(r[0].asInt(), r[1].asInt(), r[2].asInt(), r[3].asInt());
                }
                a.setLoop(anim["loop"].asBool());
                addAnimation(name, a);
            }
        }

        return true;
    }

    operator Json::Value() {
        Json::Value ret;
        ret["type"] = "sprite";
        ret["name"] = name;
        ret["file"] = path;
        for (auto &v : animations) {
            ret["animations"][v.first] = v.second;
        }
        return ret;
    }

    void connect(TextureResource v) {
        texture = v;
    }

private:
    std::map<std::string, SpriteAnimation> animations;
    TextureResource texture;
};


class ResourceManager {
private:
    std::vector<TextureResource> textures;
    std::vector<MusicResource> music;
    std::vector<SpriteResource> sprites;
};

#endif //INNER_RESOURCE_H
