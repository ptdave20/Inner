//
// Created by ptdave on 12/5/16.
//

#ifndef INNER_DEBUG_H
#define INNER_DEBUG_H

#include <imgui.h>
#include <iostream>

class Debug {
public:
    Debug() {
        sceneWindow = false;
    }

    void run() {
        ImGui::Begin("Inner tools");
        if (ImGui::Button("Toggle Scenes")) {
            sceneWindow = !sceneWindow;
        }
        ImGui::End();

        if (sceneWindow) {
            ImGui::Begin("Scenes");

            ImGui::End();
        }
    }

private:
    bool sceneWindow;
};

#endif //INNER_DEBUG_H
