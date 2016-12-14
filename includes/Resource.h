//
// Created by ptdave on 12/7/16.
//

#ifndef INNER_RESOURCE_H
#define INNER_RESOURCE_H

#include <string>

template<class T>
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
		if (value)
			delete value;
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
	bool load() {
		if (value) {
			unload();
		}
		value = std::shared_ptr<sf::Music>(new sf::Music);
		return value->openFromFile(path);
	}

	operator Json::Value&() {
		Json::Value ret;
		ret["type"] = "music";
		ret["name"] = name;
		ret["file"] = path;

		return ret;
	}
};

class TextureResource : Resource<sf::Texture> {
public:
	bool load() {
		if (value) {
			unload();
		}
		value = std::shared_ptr<sf::Music>(new sf::Texture);
		return value->loadFromFile(path);
	}

	operator Json::Value&() {
		Json::Value ret;
		ret["type"] = "texture";
		ret["name"] = name;
		ret["file"] = path;

		return ret;
	}
};

#endif //INNER_RESOURCE_H
