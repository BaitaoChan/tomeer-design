cmake_minimum_required(VERSION 3.16)

project(CukeWidgets LANGUAGES CXX)

# 基础配置
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB ORIGIN CONFIGURE_DEPENDS core/*.h core/*.cpp)
file(GLOB DEV CONFIGURE_DEPENDS core/dev/*.h core/dev/*.cpp)
file(GLOB LAB CONFIGURE_DEPENDS lab/*.h lab/*.cpp)
file(GLOB PRIVATE CONFIGURE_DEPENDS core/private/*.h core/private/*.cpp lab/private/*.h lab/private/*.cpp)
file(GLOB STYLE CONFIGURE_DEPENDS core/style/*.h core/style/*.cpp lab/style/*.h lab/style/*.cpp)

# 可执行文件
add_library(${PROJECT_NAME} SHARED
        ${ORIGIN}
        ${DEV}
        ${LAB}
        ${PRIVATE}
        ${STYLE}
)

# 查找 Qt 包
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# 包含目录
target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lab>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core/dev>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core/private>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lab/private>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core/style>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lab/style>
)

# 链接库
target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
)

target_compile_definitions(${PROJECT_NAME} PRIVATE CUKEWIDGETS_LIBRARY)

# install 库文件 dll/lib
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}
        RUNTIME DESTINATION ${PROJECT_NAME}/${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${PROJECT_NAME}/${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${PROJECT_NAME}/${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${PROJECT_NAME}/${CMAKE_INSTALL_INCLUDEDIR}
)

# 将 dll 安装到 CukeWidgetsExample 运行目录下
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION CukeWidgetsExample
        LIBRARY DESTINATION CukeWidgetsExample
)

# 导出公共头文件和库文件
file(GLOB PUBLIC_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/core/*.h")
file(GLOB LAB_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/lab/*.h")

install(FILES ${PUBLIC_HEADERS} DESTINATION ${PROJECT_NAME}/${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${LAB_HEADERS} DESTINATION ${PROJECT_NAME}/${CMAKE_INSTALL_INCLUDEDIR}/lab)