//
// Created by ptdave on 12/5/16.
//

#ifndef INNER_WINDOW_H
#define INNER_WINDOW_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

class Window {
public:
    Window() {
        windowMode.width = 640;
        windowMode.height = 480;
        windowMode.bitsPerPixel = 32;;
        title = "Inner";
        style = sf::Style::Default;
        debug = false;

        debugSceneWindow = false;
    }

    void openConfig(std::string file) {
        boost::property_tree::ptree root;
        boost::property_tree::read_json(file, root);

        auto windowObj = root.get_child("window");

        auto optHeight = windowObj.get_optional<int>("height");
        auto optWidth = windowObj.get_optional<int>("width");
        auto optTitle = windowObj.get_optional<std::string>("title");
        auto optFullscreen = windowObj.get_optional<bool>("fullscreen");
        auto optDebug = windowObj.get_optional<bool>("debug");

        if (optHeight)
            windowMode.height = windowObj.get<int>("height");
        if (optWidth)
            windowMode.width = windowObj.get<int>("width");
        if (optTitle)
            title = windowObj.get<std::string>("title");
        if (optFullscreen && optFullscreen.get())
            style |= sf::Style::Fullscreen;
        if (optDebug)
            debug = optDebug.get();

    }

    void createWindow() {
        window.create(windowMode, title, style);
        if (debug) {
            ImGui::SFML::Init(window);
            window.resetGLStates();
        }
    }


    void debugDisplay() {
        ImGui::Begin("Inner tools");
        if (ImGui::Button("Toggle Scenes")) {
            debugSceneWindow = !debugSceneWindow;
        }
        ImGui::End();

        if (debugSceneWindow) {
            ImGui::Begin("Scenes");

            ImGui::End();
        }
    }

    void run() {
        sf::Event event;
        sf::Clock clock;
        sf::Time time;
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

                debugDisplay();

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


    bool debugSceneWindow;
};


#endif //INNER_WINDOW_H
