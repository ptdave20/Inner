cmake_minimum_required(VERSION 3.5)
project(Inner)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE ON)


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

find_package(Lua REQUIRED)
if (Lua_FOUND)
    include_directories(${Lua_INCLUDE_DIR})
endif ()


set(HEADER_FILES
        includes/Entity.h
        includes/Tile.h
        includes/Map.h
        includes/Scene.h
        includes/Window.h
        includes/Debug.h
        includes/Sprite.h
        includes/jsoncpp.cpp
        includes/Resource.h
        includes/Action.h
        includes/Menu.h)


set(IMGUI_FILES
        includes/imgui/imgui.cpp
        includes/imgui/imgui-SFML.cpp
        includes/imgui/imgui_draw.cpp)

set(SOURCE_FILES main.cpp ${HEADER_FILES} ${IMGUI_FILES} includes/Inner.h)

add_executable(Inner ${SOURCE_FILES})

target_link_libraries(Inner ${SFML_LIBRARIES} ${OPENGL_LIBRARIES} ${Boost_LIBRARIES} ${Lua_LIBRARIES})