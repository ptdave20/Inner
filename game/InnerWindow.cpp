//
// Created by ptdave on 3/14/17.
//

#include "InnerWindow.h"

InnerWindow::InnerWindow() {
    std::srand(std::time(nullptr));
    bind();
}

InnerWindow::~InnerWindow() {

}

void InnerWindow::bind() {
    //chai.add(chaiscript::Std_Lib::library());
    chai.add(chaiscript::fun(&InnerWindow::openConfig,this),"window_openConfig");
    chai.add(chaiscript::fun(&InnerWindow::push_scene,this),"window_pushScene");
    chai.add(chaiscript::fun(&InnerWindow::pop_scene,this),"window_popScene");
    chai.add(chaiscript::fun(&InnerWindow::stop, this), "stop");
    chai.add(chaiscript::fun(&InnerWindow::eval, this), "include");
    chai.add(chaiscript::fun([](unsigned int min, unsigned int max) { return std::rand() % (max - min) + min; }),
             "rand");
    chai.add(Window::Library());
    chai.add(TextureResources::Library());
    chai.add(BaseObject::Library());
    chai.add(Scene::Library());
    chai.add(MenuScene::Library());
    chai.add(FadeInOutScene::Library());
    chai.add(ParticleEngine::Library());
}

void InnerWindow::push_scene(std::shared_ptr<Scene> s) {
    this->scene_push_back(s);
}

void InnerWindow::pop_scene() {
    this->scene_pop_back();
}

void InnerWindow::handleEvent(const sf::Event &e) {

}

void InnerWindow::handleLogic() {

}

void InnerWindow::eval(std::string file) {
    chai.eval_file(file);
}
