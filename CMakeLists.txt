cmake_minimum_required(VERSION 3.5)
project(Inner)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp includes/Entity.h includes/Tile.h includes/Map.h includes/Scene.h)

add_executable(Inner ${SOURCE_FILES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Inner ${SFML_LIBRARIES})
endif ()

find_package(Boost COMPONENTS system filesystem REQUIRED)
if (BOOST_FOUND)
    include_directories(${BOOST_INCLUDE_DIR})
    target_link_libraries(Inner ${BOOST_LIBRARIES})
endif ()

find_package(Lua REQUIRED)
if (LUA_FOUND)
    include_directories(${LUA_INCUDE_DIR})
    include_directories(${CMAKE_SOURCE_DIR}/libs/Selene/include)
    include_directories(${CMAKE_SOURCE_DIR}/libs/LuaBridge/Source/LuaBridge)
    target_link_libraries(Inner ${LUA_LIBRARIES})
endif ()