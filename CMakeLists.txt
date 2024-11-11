cmake_minimum_required(VERSION 3.29)
project(WebBrowser)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Sql
        WebEngineWidgets
        REQUIRED)

add_executable(WebBrowser main.cpp
        src/dataitemmanager.cpp
        include/dataitemmanager.h
        src/historyview.cpp
        include/historyview.h
        src/webbrowser.cpp
        include/webbrowser.h
        src/webview.cpp
        include/webview.h
        include/dataitem.h
        resources.qrc
)
target_link_libraries(WebBrowser
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Sql
        Qt::WebEngineWidgets
)

include_directories(${WebBrowser_SOURCE_DIR}/include)
