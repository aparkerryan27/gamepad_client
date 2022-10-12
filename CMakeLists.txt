cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

project(pufferbot_client
        VERSION 2019.1.0
        DESCRIPTION "add basic planning capabilities to agents"
        LANGUAGES CXX)

string(APPEND CMAKE_CXX_FLAGS " -fno-strict-aliasing -pthread ")

find_package(Dependencies)
install_dependency(https://github.com/germanespinosa/easy-tcp)
install_dependency(https://github.com/germanespinosa/gamepad_lib Gamepad_lib)
include_directories(dependencies/easy-tcp/include)
include_directories(dependencies/gamepad_lib/include)

add_executable(client src/main.cpp)
target_link_libraries( client
        LINK_PUBLIC
        easy-tcp
        gamepad_lib)