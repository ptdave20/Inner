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

	operator const Json::Value &() {
		Json::Value ret;
		ret["text"] = text;
		ret["onSelect"] = onSelect;
		ret["onMouseOver"] = onMouseOver;
		ret["onMouseLeave"] = onMouseLeave;
		ret["onMouseClick"] = onMouseClick;
		ret["onMouseRelease"] = onMouseRelease;

		return ret;
	}

	operator Json::Value &() {
		Json::Value ret;
		ret["text"] = text;
		ret["onSelect"] = onSelect;
		ret["onMouseOver"] = onMouseOver;
		ret["onMouseLeave"] = onMouseLeave;
		ret["onMouseClick"] = onMouseClick;
		ret["onMouseRelease"] = onMouseRelease;

		return ret;
	}

private:
    std::string text;
    OnAction onSelect;
    OnAction onMouseOver;
    OnAction onMouseLeave;
    OnAction onMouseClick;
    OnAction onMouseRelease;
};


#endif //INNER_MENU_H
