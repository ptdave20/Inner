#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


int main() {
    boost::property_tree::ptree root;
    boost::property_tree::read_json("json/main.json", root);

    auto windowObj = root.get_child("window");
    auto height = windowObj.get<int>("height");
    auto width = windowObj.get<int>("width");
    auto title = windowObj.get<std::string>("title");

    sf::RenderWindow window(sf::VideoMode(width, height), title);
    bool running = true;
    sf::Event event;


    sf::Clock clock;
    sf::Time time;
    while (running) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    running = false;
                    break;
                case sf::Event::Resized:
                    break;
            }
        }

        window.clear(sf::Color::Black);
        time = clock.restart();

        window.display();
    }

    return 0;
}