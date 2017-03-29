//
// Created by ptdave on 3/28/17.
//

#include "../Inner.h"

#ifndef INNER_FADEINOUTSCENE_H
#define INNER_FADEINOUTSCENE_H


class FadeInOutScene : public Scene {
public:
    static chaiscript::ModulePtr Library() {
        auto ret = std::make_shared<chaiscript::Module>();

        ret->add(chaiscript::user_type<FadeInOutScene>(), "FadeInOutScene");
        ret->add(chaiscript::base_class<BaseObject, FadeInOutScene>());
        ret->add(chaiscript::base_class<Resources, FadeInOutScene>());
        ret->add(chaiscript::base_class<Scene, FadeInOutScene>());
        return ret;
    }
};


#endif //INNER_FADEINOUTSCENE_H
