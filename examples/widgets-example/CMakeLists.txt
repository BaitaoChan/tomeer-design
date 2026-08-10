cmake_minimum_required(VERSION 3.16)

project(tomeer-widgets-example LANGUAGES CXX)

# 基础配置
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB ORIGIN CONFIGURE_DEPENDS src/*.h src/*.cpp)
file(GLOB WINDOW CONFIGURE_DEPENDS src/window/*.h src/window/*.cpp)

add_executable(
        ${PROJECT_NAME}
        ${ORIGIN}
        ${WINDOW}
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/widgets-example.qrc
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
        tomeer-widgets
)

add_dependencies(${PROJECT_NAME} tomeer-widgets)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${PROJECT_NAME}
        LIBRARY DESTINATION ${PROJECT_NAME}
)

find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${CMAKE_PREFIX_PATH}/bin")

# WIN32 平台使用 windeployqt 将 QT 库安装至运行目录
if (WIN32 AND WINDEPLOYQT_EXECUTABLE)
    install(CODE "
        if(EXISTS \"${WINDEPLOYQT_EXECUTABLE}\")
            execute_process(
                COMMAND \"${WINDEPLOYQT_EXECUTABLE}\"
                        --no-translations
                        --dir \"${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}\"
                        \"${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/${PROJECT_NAME}.exe\"
            )
        endif()
    ")
endif ()