cmake_minimum_required(VERSION 3.16)

project(CukeWidgetsExample LANGUAGES CXX)

# 基础配置
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB ORIGIN src/*.h src/*.cpp)
file(GLOB WINDOW src/window/*.h src/window/*.cpp)

add_executable(
        ${PROJECT_NAME}
        ${ORIGIN}
        ${WINDOW}
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/CukeWidgetsExample.qrc
)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/window>
)

# 查找 Qt 包
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        CukeWidgets
)

# 使用 windeployqt 自动复制依赖
find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${QT_INSTALL_PATH}/bin")

if (WINDEPLOYQT_EXECUTABLE)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "${WINDEPLOYQT_EXECUTABLE}" --no-translations --release "$<TARGET_FILE:${PROJECT_NAME}>"
            COMMENT "Running windeployqt to deploy Qt DLLs"
    )
endif ()

# 把 CukeWidgets.dll 复制到 exe 目录
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:CukeWidgets>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMENT "Copying CukeWidgets.dll to example output directory"
)