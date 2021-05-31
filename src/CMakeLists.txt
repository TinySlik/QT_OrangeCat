cmake_minimum_required(VERSION 3.2)
project(oil_src)

add_subdirectory(paramserv)

if(OS_WIN)
  set(QT_PLATFORM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/impl.win32.cpp)
else()
  set(QT_PLATFORM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/impl.linux.cpp)
endif()

file(GLOB_RECURSE QRC_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../res/*.qrc)
#set(QRC_SOURCE_FILES res.qrc)
qt5_add_resources(QRC_FILES ${QRC_SOURCE_FILES})

set(SOURCE_FILES ${QRC_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/certificateerrordialog.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/passworddialog.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/downloadmanagerwidget.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/downloadwidget.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/browser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/browserwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/downloadmanagerwidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/downloadwidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/tabwidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/webpage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/webpopupwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/webview.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/urldecode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/window.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/logo.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/logo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/memorymapped.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/memorymapped.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/dataprocesswidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/dataprocesswidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/manchesterdecoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/manchesterdecoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/personificationdecoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/personificationdecoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/time.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/highfrequencysensivitydecoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/highfrequencysensivitydecoder.cpp
    ${QT_PLATFORM_FILES}
)

include_directories(log)
include_directories(paramserv)
include_directories(../3rdparty/asyncplusplus/include)

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-expansion-to-defined -Wno-deprecated-declarations" )
add_executable(sample ${SOURCE_FILES})
target_link_libraries(sample PRIVATE Qt5::Widgets Qt5::WebEngineWidgets Qt5::Quick paramserv Async++)
