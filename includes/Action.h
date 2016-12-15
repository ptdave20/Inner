//
// Created by ptdave on 12/8/16.
//

#ifndef INNER_ACTION_H
#define INNER_ACTION_H

#include <string>
#include <map>

enum ACTIONS {
    MUSIC_START,
    MUSIC_STOP,
    MUSIC_LOOP,
    MUSIC_LOAD,
    MUSIC_UNLOAD,

    TEXTURE_LOAD,
    TEXTURE_UNLOAD,

    FONT_LOAD,
    FONT_UNLOAD,

    SPRITE_LOAD,
    SPRITE_UNLOAD,

    SCENE_LOAD,
    SCENE_UNLOAD,
    SCENE_BEGIN,
    SCENE_END,

    VARIABLE_SET,
    VARIABLE_MOD
};

const std::vector<std::string> ACTIONS_TEXT = {
        "music_start",
        "music_stop",
        "music_loop",
        "music_load",
        "music_unload",

        "texture_load",
        "texture_unload",

        "font_load",
        "font_unload",

        "sprite_load",
        "sprite_unload",

        "scene_load",
        "scene_unload",
        "scene_begin",
        "scene_end",

        "variable_set",
        "variable_mod"
};

typedef std::pair<int, std::string> ACTION;

class OnAction : public std::vector<ACTION> {
public:
    operator Json::Value() {
		Json::Value ret;
        for (const auto &action : *this) {
			Json::Value act;
            act[ACTIONS_TEXT[action.first]] = action.second;
			ret.append(ret);
		}
		return ret;
	}

    void Parse(Json::Value &value) {
        const auto members = value.getMemberNames();

        for (const auto &member : members) {
            auto v = value[member];
            ACTION action;
            for (int i = 0; i < ACTIONS_TEXT.size(); i++) {
                if (member == ACTIONS_TEXT[i]) {
                    action.first = i;
                    action.second = v.asString();

                    push_back(action);
                    break;
                }
            }

            // If we reach this point, then we don't know what it is or we have added it already
        }
    }
};


#endif //INNER_ACTION_H
