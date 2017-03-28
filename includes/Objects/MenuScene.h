//
// Created by ptdave on 3/27/17.
//

#include "../Inner.h"

#ifndef INNER_MENU_H
#define INNER_MENU_H


class MenuScene : public Scene {
private:
    std::vector<sf::Text> menuOptions;
    std::function<void(int)> selectedFunc;
    unsigned int selectedOption;
    sf::Font normalFont,selectedFont;
    sf::Color normalColor,selectedColor;
    unsigned int normalSize,selectedSize;
    int lineSpacing;
public:
    static chaiscript::ModulePtr Library() {
        chaiscript::ModulePtr ret = std::make_shared<chaiscript::Module>();
        ret->add(chaiscript::constructor<MenuScene()>(),"MenuScene")
                .add(chaiscript::fun(&MenuScene::addOption),"addOption")
                .add(chaiscript::fun(&MenuScene::totalMenuOptions),"totalMenuOptions")
                .add(chaiscript::fun(&MenuScene::getSelectedIndex),"getSelectedIndex")
                .add(chaiscript::fun(&MenuScene::getSelectedString),"getSelectedString")
                .add(chaiscript::fun(&MenuScene::setNormalFontColor),"setNormalFontColor")
                .add(chaiscript::fun(&MenuScene::setNormalFontSize),"setNormalFontSize")
                .add(chaiscript::fun(&MenuScene::setNormalFont),"setNormalFont")
                .add(chaiscript::fun(&MenuScene::setSelectedFontColor),"setSelectedFontColor")
                .add(chaiscript::fun(&MenuScene::setSelectedFontSize),"setSelectedFontSize")
                .add(chaiscript::fun(&MenuScene::setSelectedFont), "setSelectedFont")
                .add(chaiscript::fun(&MenuScene::setSelectedFunction), "setSelectedFunction");
        ret->add(chaiscript::base_class<BaseObject,MenuScene>());
        ret->add(chaiscript::base_class<Resources,MenuScene>());
        ret->add(chaiscript::base_class<Scene,MenuScene>());
        return ret;
    }

    MenuScene() {
        selectedOption = -1;
        normalSize = 30;
        selectedSize = 30;
        lineSpacing = 5;
    }

    void position() {
        auto yOffSet = 0;
        for(auto &o : menuOptions) {
            auto pos = o.getPosition();
            pos.y = yOffSet;
            yOffSet += o.getLocalBounds().height + lineSpacing;
            o.setPosition(pos);
        }
    }

    void setSelectedFunction(std::function<void(int)> f) {
        selectedFunc = f;
    }

    unsigned int totalMenuOptions() const {
        return menuOptions.size();
    }
    void addOption(const std::string option) {
        menuOptions.push_back(sf::Text(option,normalFont));
        menuOptions.back().setColor(normalColor);
        menuOptions.back().setCharacterSize(normalSize);
        menuOptions.back().setFont(normalFont);
        position();
    }
    void setNormalFontColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a = 255) {
        normalColor.r = r;
        normalColor.g = g;
        normalColor.b = b;
        normalColor.a = a;
        for(auto i=0; i<menuOptions.size(); i++) {
            if(i==selectedOption) {
                continue;
            }
            menuOptions[i].setColor(normalColor);
        }
    }
    void setSelectedFontColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a = 255) {
        selectedColor.r = r;
        selectedColor.g = g;
        selectedColor.b = b;
        selectedColor.a = a;
        for(auto i=0; i<menuOptions.size(); i++) {
            if(i==selectedOption) {
                menuOptions[i].setColor(selectedColor);
            }
        }
    }
    void setNormalFontSize(const unsigned int size) {
        normalSize = size;
        for(auto i=0; i<menuOptions.size(); i++) {
            if(i==selectedOption) {
                continue;
            }
            menuOptions[i].setCharacterSize(size);
        }
    }
    unsigned int getNormalFontSize() const {
        return normalSize;
    }
    unsigned int getSelectedFontSize() const {
        return selectedSize;
    }
    void setSelectedFontSize(const unsigned int size) {
        selectedSize = size;
        for(auto i=0; i<menuOptions.size(); i++) {
            if(i==selectedOption) {
                menuOptions[i].setCharacterSize(size);
            }
        }
    }
    unsigned int getSelectedIndex() const {
        return selectedOption;
    }
    const std::string getSelectedString() {
        return menuOptions[selectedOption].getString().toAnsiString();
    }
    void setSelectedFont(const std::string f) {
        selectedFont = getFont(f);
        for(auto i=0; i<menuOptions.size(); i++) {
            if(i==selectedOption) {
                menuOptions[i].setFont(normalFont);
            }
        }
    }
    void setNormalFont(const std::string f) {
        normalFont = getFont(f);
        for(auto i=0; i<menuOptions.size(); i++) {
            if(i==selectedOption) {
                continue;
            }
            menuOptions[i].setFont(normalFont);
        }
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        //std::cout << menuOptions.size() << std::endl;
        for(auto i = 0; i<menuOptions.size(); i++) {
            target.draw(menuOptions[i],states);
        }
    }

    void handleEvent(sf::Event &event) override {
        if (event.type == sf::Event::MouseMoved) {
            auto m = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
            for (auto i = 0; i < menuOptions.size(); i++) {
                if (menuOptions[i].getGlobalBounds().contains(m) && selectedOption != i) {
                    menuOptions[i].setFont(selectedFont);
                    menuOptions[i].setColor(selectedColor);
                    menuOptions[i].setCharacterSize(selectedSize);
                    selectedOption = i;
                } else if (!menuOptions[i].getGlobalBounds().contains(m)) {
                    menuOptions[i].setFont(normalFont);
                    menuOptions[i].setColor(normalColor);
                    menuOptions[i].setCharacterSize(normalSize);
                }
            }
            position();
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            auto m = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
            for (const auto &o : menuOptions) {
                if (o.getGlobalBounds().contains(m)) {
                    // Trigger option event
                    if (selectedFunc)
                        selectedFunc(selectedOption);

                }
            }
        }
    }

};


#endif //INNER_MENU_H
