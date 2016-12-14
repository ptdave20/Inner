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
    SPRITE_UNLOAD
};

const std::string ACTIONS_TEXT[] = {
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
        "sprite_unload"
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
};


#endif //INNER_ACTION_H
