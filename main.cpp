#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Inner");
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