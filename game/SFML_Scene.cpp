//
// Created by ptdave on 3/15/17.
//

#include "SFML_Scene.h"

bool SFML_Scene::load() {
    std::cout << loadFont("quiet_horror","fonts/quiet_horror_story.ttf") << std::endl;
    return true;
}