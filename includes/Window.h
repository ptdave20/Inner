//
// Created by ptdave on 12/5/16.
//

#include "Inner.h"

#ifndef INNER_WINDOW_H
#define INNER_WINDOW_H

class Window {
public:
    Window() {
        windowMode.width = 640;
        windowMode.height = 480;
        windowMode.bitsPerPixel = 32;;
        title = "Inner";
        style = sf::Style::Default;
    }
    virtual ~Window() {}

    bool openConfig(std::string file) {
        std::ifstream in(file, std::ifstream::binary);
        if (!in.is_open()) {
            return false;
        }

        Json::Reader reader;
        Json::Value root;

        if (!reader.parse(in, root)) {
            in.close();
            return false;
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
        }

        in.close();
        return true;
    }

    void createWindow() {
        window.create(windowMode, title, style);
		window.setFramerateLimit(60);
    }

    void stop() {
        running = false;
    }

    void start() {
        sf::Event event;
        sf::Clock clock;
        sf::Time time;

        createWindow();

        running = true;


        while (running) {
            //
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    running = false;
                }
                if (event.type == sf::Event::Resized) {
                    windowMode.width = event.size.width;
                    windowMode.height = event.size.height;
                }
                // Pass the even to the scene
                if (sceneManager.size() > 0)
                    sceneManager.back()->handleEvent(event);
            }
            time = clock.restart();
            window.clear(sf::Color::Black);

            if(sceneManager.size() > 0) {
                sceneManager.back()->update(time);
                window.draw(*sceneManager.back());
            }

            window.display();
        }
        window.close();
    }

    SceneManager& getSceneManager() {
        return sceneManager;
    }
private:
    sf::RenderWindow window;
    std::string title;
    sf::VideoMode windowMode;
    unsigned int style;
    SceneManager sceneManager;
    bool running;
};


#endif //INNER_WINDOW_H
