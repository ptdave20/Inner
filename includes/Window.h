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
        debug = false;


    }

    static void Register(sel::State &state) {
        state["Window"].SetClass<Window>(
			"openConfig", &Window::openConfig,
            "createWindow", &Window::createWindow,
            "run", &Window::run,
            "stop", &Window::stop);

		// Register IntRect
		state["IntRect"].SetClass<sf::IntRect>(
				"left",&sf::IntRect::left,
				"top",&sf::IntRect::top,
				"width",&sf::IntRect::width,
				"height",&sf::IntRect::height
			);

        // Register our objects
        Scene::Register(state);
        MusicResource::Register(state);
        TextureResource::Register(state);
    }

    bool openConfig(std::string file) {
        std::cout << file << std::endl;
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
            if (w["debug"].isBool()) {
                debug = w["debug"].asBool();
            }
        }

        if (root["initScene"].isString()) {
            std::shared_ptr<Scene> initScene(new Scene());
            //initScene->openFile(root["initScene"].asString());
            std::cout << initScene->getName() << " loaded" << std::endl;
            sceneStack.push_back(initScene);
        }

        in.close();
        return true;
    }

    void createWindow() {
        window.create(windowMode, title, style);
		window.setFramerateLimit(60);
        if (debug) {
            ImGui::SFML::Init(window);
            window.resetGLStates();
        }
    }

    void stop() {
        running = false;
    }

    void run() {
        sf::Event event;
        sf::Clock clock;
        sf::Time time;
        Debug _debug;
        running = true;

        while (running) {
            //
            while (window.pollEvent(event)) {
                if (debug)
                    ImGui::SFML::ProcessEvent(event);
                switch (event.type) {
                    case sf::Event::Closed:
                        running = false;
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


            for (const auto &s : sceneStack) {
                window.draw(*s);
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
    bool running;


};


#endif //INNER_WINDOW_H
