cmake_minimum_required(VERSION 3.5)
project(Inner)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE ON)


find_package(SFML 2 REQUIRED system window graphics audio)
if (SFML_FOUND)
    include_directories(${CMAKE_SOURCE_DIR}/libs/imgui/)
    include_directories(${SFML_INCLUDE_DIR})
    include_directories(${CMAKE_SOURCE_DIR}/libs/imguisfml/)
endif ()

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
endif ()

set(IMGUI_SOURCE_FILES ${CMAKE_SOURCE_DIR}/libs/imgui/imgui.cpp ${CMAKE_SOURCE_DIR}/libs/imgui/imgui_draw.cpp ${CMAKE_SOURCE_DIR}/libs/imguisfml/imgui-SFML.cpp)
set(SOURCE_FILES main.cpp includes/Entity.h includes/Tile.h includes/Map.h includes/Scene.h ${IMGUI_SOURCE_FILES} includes/Window.h includes/Debug.h includes/Sprite.h includes/jsoncpp.cpp includes/Resource.h)

add_executable(Inner ${SOURCE_FILES})

target_link_libraries(Inner ${SFML_LIBRARIES} ${OPENGL_LIBRARIES})