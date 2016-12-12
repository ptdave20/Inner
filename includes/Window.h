//
// Created by ptdave on 12/5/16.
//

#ifndef INNER_WINDOW_H
#define INNER_WINDOW_H

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include "json/json.h"
#include "Debug.h"
#include <fstream>
#include "Scene.h"

class Window {
public:
    Window() {
        windowMode.width = 640;
        windowMode.height = 480;
        windowMode.bitsPerPixel = 32;;
        title = "Inner";
        style = sf::Style::Default;
        debug = false;
    }

    void openConfig(const std::string &file) {
        std::ifstream in(file, std::ifstream::binary);
        if (!in.is_open()) {
            return;
        }

        Json::Reader reader;
        Json::Value root;

        if (!reader.parse(in, root)) {
            in.close();
            return;
        }

        if (!root["window"].empty() && root["window"].isObject()) {
            auto w = root["window"];
            if (w["height"].isInt()) {
                windowMode.height = w["height"].asInt();
            }
            if (w["width"].isInt()) {
                windowMode.width = w["width"].asInt();
            }
            if (w["title"].isString()) {
                title = w["title"].asString();
            }
            if (w["fullscreen"].isBool()) {
                if (w["fullscreen"].asBool())
                    style |= sf::Style::Fullscreen;
                else
                    style ^= sf::Style::Fullscreen;
            }
            if (w["debug"].isBool()) {
                debug = w["debug"].asBool();
            }
        }

        if (root["initScene"].isString()) {
            std::shared_ptr<Scene> initScene(new Scene());
            initScene->openFile(root["initScene"].asString());
            std::cout << initScene->getName() << " loaded" << std::endl;
            sceneStack.push_back(initScene);
        }

        in.close();

    }

    void createWindow() {
        window.create(windowMode, title, style);
        if (debug) {
            ImGui::SFML::Init(window);
            window.resetGLStates();
        }
    }

    void run() {
        sf::Event event;
        sf::Clock clock;
        sf::Time time;
        Debug _debug;
        bool run = true;

        while (run) {
            //
            while (window.pollEvent(event)) {
                if (debug)
                    ImGui::SFML::ProcessEvent(event);
                switch (event.type) {
                    case sf::Event::Closed:
                        run = false;
                        break;
                    case sf::Event::Resized:
                        windowMode.width = event.size.width;
                        windowMode.height = event.size.height;
                        break;
                    case sf::Event::MouseMoved:
                        break;
                    case sf::Event::KeyReleased:
                        break;
                    case sf::Event::KeyPressed:
                        break;
                    case sf::Event::MouseButtonPressed:
                        break;
                    case sf::Event::MouseButtonReleased:
                        break;
                }
            }
            time = clock.restart();
            window.clear(sf::Color::Black);

            if (debug) {

                ImGui::SFML::Update(window, time);

                _debug.run(time);

                ImGui::Render();
            }


            window.display();
        }
        ImGui::SFML::Shutdown();
        window.close();
    }

private:
    sf::RenderWindow window;
    std::string title;
    sf::VideoMode windowMode;
    bool debug;
    unsigned int style;
    std::vector<std::shared_ptr<Scene>> sceneStack;
};


#endif //INNER_WINDOW_H
