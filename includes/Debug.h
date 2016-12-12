//
// Created by ptdave on 12/5/16.
//

#ifndef INNER_DEBUG_H
#define INNER_DEBUG_H


#include "imgui/imgui.h"
#include <iostream>

#include <boost/filesystem.hpp>
#include "Scene.h"


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
        sceneWindow = false;
        sceneSelectedIndex = 0;
        sceneLoadedIndex = -1;
        fps = "";
        time = 0;
        frames = 0;
    }

    void run(const sf::Time &u) {
        ImGui::Begin("Inner tools");
        if (ImGui::Button("Toggle Scenes")) {
            // Get a list of files in the scene directory
            scanSceneFiles();
            sceneWindow = !sceneWindow;
            sceneSelectedIndex = -1;
            sceneLoadedIndex = -1;
            sceneLoadedIndex = -1;
            sceneLoadedMusicIndex = -1;
        }
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);

        ImGui::End();

        if (sceneWindow) {
            SceneWindowProc();
        }
    }

private:
    void SceneWindowProc() {
        static char sceneName[256];
        static std::string selectedMusicText;
        ImGui::Begin("Scenes", &sceneWindow);
        ImGui::Combo("Select a scene", &sceneSelectedIndex, sceneFiles);

        if (sceneLoadedIndex != sceneSelectedIndex) {
            // Need to load a scene and prep for display
            if (scene) {
                auto s = scene.release();
                delete s;
            }

            scene = std::unique_ptr<Scene>(new Scene());
            scene->openFile(sceneBoostFiles[sceneSelectedIndex].string());
            sceneLoadedIndex = sceneSelectedIndex;

            std::strcpy(sceneName, scene->getName().c_str());
            auto &resMusic = scene->getResMusic();
            songs.clear();
            songs.push_back(std::string(" "));
            for (const auto m : resMusic) {
                songs.push_back(m.first);
            }
        }

        // Scene name
        ImGui::InputText("Name", sceneName, 256);

        ImGui::BeginGroup();
        ImGui::Text("Texture Resources");

        ImGui::EndGroup();


        ImGui::BeginGroup();
        ImGui::Text("Music Resources");
        ImGui::Combo("", &sceneSelectedMusicIndex, songs);
        if (ImGui::Button("+##Add")) {
            // Add music resource
        }
        if (ImGui::Button("-##Delete")) {
            // Delete music resource
        }
        ImGui::EndGroup();

        ImGui::BeginGroup();
        ImGui::Text("Font Resources");
        ImGui::EndGroup();

        ImGui::End();
    }
    void scanSceneFiles() {
        namespace fs = boost::filesystem;
        fs::path path("./scenes");
        fs::directory_iterator end;
        sceneBoostFiles.clear();

        if (fs::exists(path) && fs::is_directory(path)) {
            for (fs::directory_iterator dir_itr(path); dir_itr != end; dir_itr++) {
                if (fs::is_regular(dir_itr->status())) {
                    sceneBoostFiles.push_back(dir_itr->path());
                    sceneFiles.push_back(dir_itr->path().c_str());
                }
            }
        }
    }

    // SCENE WINDOW
    bool sceneWindow;
    std::unique_ptr<Scene> scene;
    std::vector<boost::filesystem::path> sceneBoostFiles;
    std::vector<std::string> sceneFiles;
    int sceneSelectedIndex;
    int sceneLoadedIndex;
    int sceneSelectedMusicIndex;
    int sceneLoadedMusicIndex;
    std::vector<std::string> songs;

    // END SCENE WINDOW

    float time;
    int frames;
    std::string fps;
};

#endif //INNER_DEBUG_H
