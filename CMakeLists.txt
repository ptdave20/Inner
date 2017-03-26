cmake_minimum_required(VERSION 3.5)
project(Inner)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")

include(cotire)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lpthread -ldl")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE ON)

find_package(Threads REQUIRED)

find_package(SFML 2 REQUIRED system window graphics audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
endif ()

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
endif ()

find_package(Boost COMPONENTS filesystem system REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif ()


set(HEADER_FILES
        includes/typedefs.h
        includes/BaseObject.h
        includes/Scene.h
        includes/Window.h
        includes/jsoncpp.cpp
        includes/Inner.h
        includes/SceneManager.h includes/Resources.h)


set(IMGUI_FILES
        includes/imgui/imgui.cpp
        includes/imgui/imgui-SFML.cpp
        includes/imgui/imgui_draw.cpp)

set(GAME_FILES
        game/InnerWindow.cpp
        main.cpp
        game/SFML_Scene.cpp game/SFML_Scene.h)

set(SOURCE_FILES ${IMGUI_FILES} ${HEADER_FILES} ${GAME_FILES} includes/SceneManager.h)

add_executable(Inner ${SOURCE_FILES})

target_link_libraries(Inner ${SFML_LIBRARIES} ${OPENGL_LIBRARIES} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
cotire(Inner)