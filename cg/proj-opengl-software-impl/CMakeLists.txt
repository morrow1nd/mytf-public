cmake_minimum_required(VERSION 3.16)
project(sgl)
file(GLOB H_FILES "src/*.h")
file(GLOB HPP_FILES "src/*.hpp")
add_executable(app
    src/main.c
    src/app_wrapper.cpp
    src/sgl.cpp
    ${H_FILES}
    ${HPP_FILES}
)
