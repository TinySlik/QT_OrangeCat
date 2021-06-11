cmake_minimum_required(VERSION 3.2)
project(oil_src)

add_subdirectory(paramserv)

if(OS_WIN)
  set(QT_FILTER_PLATFORM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/impl.win32.cpp)
else()
  set(QT_FILTER_PLATFORM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/impl.linux.cpp)
endif()

file(GLOB_RECURSE QRC_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../res/*.qrc)
#set(QRC_SOURCE_FILES res.qrc)
qt5_add_resources(QRC_FILES ${QRC_SOURCE_FILES})

set(SOURCE_FILTER_FILES ${QRC_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/certificateerrordialog.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/passworddialog.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/downloadmanagerwidget.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/downloadwidget.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/browser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/browserwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/downloadmanagerwidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/downloadwidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/tabwidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/webpage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/webpopupwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/webview.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/urldecode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/window.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/logo.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/logo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/memorymapped.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/memorymapped.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/dataprocesswidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/dataprocesswidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/manchesterdecoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/manchesterdecoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/personificationdecoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/personificationdecoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/time.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/highfrequencysensivitydecoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/highfrequencysensivitydecoder.cpp
    ${QT_FILTER_PLATFORM_FILES}
)

if(OS_WIN)
  set(QT_COMPARE_PLATFORM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/impl.win32.cpp)
else()
  set(QT_COMPARE_PLATFORM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/impl.linux.cpp)
endif()


set(SOURCE_COMPARE_FILES ${QRC_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/certificateerrordialog.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/passworddialog.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/downloadmanagerwidget.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/downloadwidget.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/browser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/browserwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/downloadmanagerwidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/downloadwidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/tabwidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/webpage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/webpopupwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/webview.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/urldecode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/window.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/logo.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/logo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/memorymapped.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/memorymapped.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/dataprocesswidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/dataprocesswidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/manchesterdecoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/manchesterdecoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/personificationdecoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/personificationdecoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/time.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/highfrequencysensivitydecoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/compare/highfrequencysensivitydecoder.cpp
    ${QT_COMPARE_PLATFORM_FILES}
)

include_directories(log)
include_directories(paramserv)
include_directories(../3rdparty/asyncplusplus/include)

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-expansion-to-defined -Wno-deprecated-declarations" )
add_executable(sample ${SOURCE_FILTER_FILES})

target_link_libraries(sample PRIVATE Qt5::Widgets Qt5::WebEngineWidgets Qt5::Quick paramserv Async++)

add_executable(compare_tool ${SOURCE_COMPARE_FILES})

target_link_libraries(compare_tool PRIVATE Qt5::Widgets Qt5::WebEngineWidgets Qt5::Quick paramserv Async++)
