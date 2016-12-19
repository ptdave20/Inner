//
// Created by ptdave on 12/5/16.
//

#include "Inner.h"

#ifndef INNER_DEBUG_H
#define INNER_DEBUG_H


namespace ImGui {
    static auto vector_getter = [](void *vec, int idx, const char **out_text) {
        auto &vector = *static_cast<std::vector<std::string> *>(vec);
        if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
        *out_text = vector.at(idx).c_str();
        return true;
    };

    bool Combo(const char *label, int *currIndex, std::vector<std::string> &values) {
        if (values.empty()) { return false; }
        return Combo(label, currIndex, vector_getter,
                     static_cast<void *>(&values), values.size());
    }

    bool ListBox(const char *label, int *currIndex, std::vector<std::string> &values) {
        if (values.empty()) { return false; }
        return ListBox(label, currIndex, vector_getter,
                       static_cast<void *>(&values), values.size());
    }

}


class Debug {
public:
    Debug() {
        fps = "";
        time = 0;
        frames = 0;
    }

    void run(const sf::Time &u) {
        ImGui::Begin("Inner tools");
        if (ImGui::Button("Toggle Scenes")) {
            // Get a list of files in the scene directory
        }

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);

        ImGui::End();

    }

private:


	char buffer[256],buffer2[256];

    // END SCENE WINDOW

    float time;
    int frames;
    std::string fps;
};

#endif //INNER_DEBUG_H
