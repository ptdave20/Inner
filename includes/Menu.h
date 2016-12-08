//
// Created by ptdave on 12/8/16.
//

#ifndef INNER_MENU_H
#define INNER_MENU_H

#include "Action.h"
#include <vector>

class MenuOption {
public:
    const std::string &getText() const {
        return text;
    }

    void setText(const std::string &text) {
        MenuOption::text = text;
    }

    const std::vector<OnAction> &getOnSelect() const {
        return onSelect;
    }

    void setOnSelect(const std::vector<OnAction> &onSelect) {
        MenuOption::onSelect = onSelect;
    }

    const std::vector<OnAction> &getOnMouseOver() const {
        return onMouseOver;
    }

    void setOnMouseOver(const std::vector<OnAction> &onMouseOver) {
        MenuOption::onMouseOver = onMouseOver;
    }

    const std::vector<OnAction> &getOnMouseLeave() const {
        return onMouseLeave;
    }

    void setOnMouseLeave(const std::vector<OnAction> &onMouseLeave) {
        MenuOption::onMouseLeave = onMouseLeave;
    }

    const std::vector<OnAction> &getOnMouseClick() const {
        return onMouseClick;
    }

    void setOnMouseClick(const std::vector<OnAction> &onMouseClick) {
        MenuOption::onMouseClick = onMouseClick;
    }

    const std::vector<OnAction> &getOnMouseRelease() const {
        return onMouseRelease;
    }

    void setOnMouseRelease(const std::vector<OnAction> &onMouseRelease) {
        MenuOption::onMouseRelease = onMouseRelease;
    }

private:
    std::string text;
    std::vector<OnAction> onSelect;
    std::vector<OnAction> onMouseOver;
    std::vector<OnAction> onMouseLeave;
    std::vector<OnAction> onMouseClick;
    std::vector<OnAction> onMouseRelease;
};


#endif //INNER_MENU_H
