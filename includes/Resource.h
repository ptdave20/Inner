//
// Created by ptdave on 12/7/16.
//

#ifndef INNER_RESOURCE_H
#define INNER_RESOURCE_H

#include <string>

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

private:
    std::string path;
    std::string type;
    std::string name;
};


#endif //INNER_RESOURCE_H
