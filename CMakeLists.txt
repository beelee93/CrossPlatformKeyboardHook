cmake_minimum_required(VERSION 3.1)

project(DoorOpener)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")

add_subdirectory(HookInterface)
add_subdirectory(MainApp)