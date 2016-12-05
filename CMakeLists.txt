cmake_minimum_required(VERSION 3.5)
project(Inner)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED system window graphics audio)
if (SFML_FOUND)
    include_directories(${CMAKE_SOURCE_DIR}/libs/imgui/)
    include_directories(${SFML_INCLUDE_DIR})
    include_directories(${CMAKE_SOURCE_DIR}/libs/imguisfml/)
endif ()

find_package(Boost COMPONENTS system filesystem REQUIRED)
if (BOOST_FOUND)
    include_directories(${BOOST_INCLUDE_DIR})
endif ()

find_package(Lua REQUIRED)
if (LUA_FOUND)
    include_directories(${LUA_INCUDE_DIR})
    include_directories(${CMAKE_SOURCE_DIR}/libs/Selene/include)
    include_directories(${CMAKE_SOURCE_DIR}/libs/LuaBridge/Source/LuaBridge)
endif ()

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
if (OPENGL_FOUND)

endif ()

set(IMGUI_SOURCE_FILES ${CMAKE_SOURCE_DIR}/libs/imgui/imgui.cpp ${CMAKE_SOURCE_DIR}/libs/imgui/imgui_draw.cpp ${CMAKE_SOURCE_DIR}/libs/imguisfml/imgui-SFML.cpp)
set(SOURCE_FILES main.cpp includes/Entity.h includes/Tile.h includes/Map.h includes/Scene.h ${IMGUI_SOURCE_FILES})

add_executable(Inner ${SOURCE_FILES})

target_link_libraries(Inner ${SFML_LIBRARIES})
target_link_libraries(Inner ${BOOST_LIBRARIES})
target_link_libraries(Inner ${LUA_LIBRARIES})
target_link_libraries(Inner ${OPENGL_LIBRARIES})