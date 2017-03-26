//
// Created by ptdave on 3/14/17.
//

#ifndef INNER_INNERGAME_H
#define INNER_INNERGAME_H

#include "../includes/Inner.h"

class InnerWindow : public Window {
public:
    InnerWindow();
    ~InnerWindow();

    void eval(std::string file);

private:
    void bind();
    void push_scene(std::shared_ptr<Scene>);
    void pop_scene();
    chaiscript::ChaiScript chai;

protected:
    void handleEvent(const sf::Event &e);
    void handleLogic();
};


#endif //INNER_INNERGAME_H
