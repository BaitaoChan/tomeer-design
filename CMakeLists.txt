cmake_minimum_required(VERSION 3.16)

project(CukeTools LANGUAGES CXX)

# Qt 路径设置
set(CMAKE_PREFIX_PATH "D:/Software/Qt/6.7.3/msvc2019_64")

include(GNUInstallDirs)

# install 输出目录
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "" FORCE)

add_subdirectory(widgets)
add_subdirectory(examples/CukeWidgetsExample)