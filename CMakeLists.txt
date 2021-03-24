cmake_minimum_required(VERSION 3.5)

project(OIL LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets WebEngineWidgets REQUIRED)

add_executable(OIL
    browser.h
    browserwindow.h
    downloadmanagerwidget.h
    downloadwidget.h
    tabwidget.h
    webpage.h
    webpopupwindow.h
    webview.h
    browser.cpp
    browserwindow.cpp
    downloadmanagerwidget.cpp
    downloadwidget.cpp
    main.cpp
    tabwidget.cpp
    webpage.cpp
    webpopupwindow.cpp
    webview.cpp
    certificateerrordialog.ui
    passworddialog.ui
    downloadmanagerwidget.ui
    downloadwidget.ui
)

target_link_libraries(OIL PRIVATE Qt5::Widgets Qt5::WebEngineWidgets )
