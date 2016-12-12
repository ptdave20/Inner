//
// Created by ptdave on 12/5/16.
//

#ifndef INNER_DEBUG_H
#define INNER_DEBUG_H

#include <imgui.h>
#include <iostream>

#include <boost/filesystem.hpp>
#include "Scene.h"


class Debug {
public:
    Debug() {
        sceneWindow = false;
        sceneSelectedIndex = 0;
        sceneLoadedIndex = -1;
    }

    void run() {
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
        ImGui::End();

        if (sceneWindow) {
            SceneWindowProc();
        }
    }

private:
    void SceneWindowProc() {
        static char sceneName[256];
        static std::string selectedMusicText;
        ImGui::Begin("Scenes");
        ImGui::Combo("Select a scene", &sceneSelectedIndex, sceneFileString.c_str());

        if (sceneLoadedIndex != sceneSelectedIndex) {
            // Need to load a scene and prep for display
            if (scene) {
                auto s = scene.release();
                delete s;
            }

            scene = std::unique_ptr<Scene>(new Scene());
            scene->openFile(sceneFiles[sceneSelectedIndex].string());
            sceneLoadedIndex = sceneSelectedIndex;

            std::strcpy(sceneName, scene->getName().c_str());
            auto &resMusic = scene->getResMusic();
            std::vector<std::string> songs;
            for (const auto m : resMusic) {
                songs.push_back(m.first);
            }
            selectedMusicText = convertStringArray(songs);
        }

        // Scene name
        ImGui::InputText("Name", sceneName, 256);

        ImGui::BeginGroup();
        ImGui::Text("Texture Resources");

        ImGui::EndGroup();

        ImGui::BeginGroup();
        ImGui::Text("Music Resources");
        ImGui::Combo("", &sceneSelectedMusicIndex, selectedMusicText.c_str());
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
        sceneFiles.clear();

        if (fs::exists(path) && fs::is_directory(path)) {
            for (fs::directory_iterator dir_itr(path); dir_itr != end; dir_itr++) {
                if (fs::is_regular(dir_itr->status())) {
                    sceneFiles.push_back(dir_itr->path());
                }
            }
        }

        sceneFileString = "";
        for (const auto &f : sceneFiles) {
            sceneFileString += f.string().c_str();
            sceneFileString += "\0";
        }
    }

    std::string convertStringArray(std::vector<std::string> arr) {
        std::string ret = "";
        for (const auto &v : arr) {
            ret += v.c_str();

            ret += "\0";
        }
        return ret;
    }

    // SCENE WINDOW
    bool sceneWindow;
    std::unique_ptr<Scene> scene;
    std::vector<boost::filesystem::path> sceneFiles;
    std::string sceneFileString;
    int sceneSelectedIndex;
    int sceneLoadedIndex;
    int sceneSelectedMusicIndex;
    int sceneLoadedMusicIndex;


    // END SCENE WINDOW
};

#endif //INNER_DEBUG_H
