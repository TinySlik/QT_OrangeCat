cmake_minimum_required(VERSION 3.5)

project(OIL LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/Common.cmake)

if(NOT CMAKE_DEBUG_POSTFIX)
  set(CMAKE_DEBUG_POSTFIX d)
endif()

LIST(APPEND CMAKE_MODULE_PATH cmake)

# options

include(cmake/Option.cmake)

# flags

if(OS_WIN)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
elseif(OS_MAC)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wno-error=deprecated-declarations -Wno-deprecated-declarations -Wno-error=expansion-to-defined -Wno-expansion-to-defined")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wno-error=deprecated-declarations -Wno-deprecated-declarations -Wno-error=expansion-to-defined -Wno-expansion-to-defined")
else()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-error=expansion-to-defined -Wno-expansion-to-defined")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-error=expansion-to-defined -Wno-expansion-to-defined")
endif()

include(cmake/DetectCXX11.cmake)

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")

string(STRIP "${CMAKE_C_FLAGS}" CMAKE_C_FLAGS)
string(STRIP "${CMAKE_CXX_FLAGS}" CMAKE_CXX_FLAGS)
message(STATUS "C_FLAGS: ${CMAKE_C_FLAGS}")
message(STATUS "CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

# packages

find_package(Threads QUIET)

macro(target_link_threads NAME)
  if(THREADS_HAVE_PTHREAD_ARG)
    target_compile_options(PUBLIC ${NAME} "-pthread")
  endif()
  if(CMAKE_THREAD_LIBS_INIT)
    target_link_libraries(${NAME} PUBLIC "${CMAKE_THREAD_LIBS_INIT}")
  endif()
endmacro()

include(CMakePackageConfigHelpers)


find_package(Qt5 COMPONENTS Widgets WebEngineWidgets REQUIRED)

set(OUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/_output")
set_outdir(
  "${OUT_DIR}/lib"
  "${OUT_DIR}/lib"
  "${OUT_DIR}/bin"
)


set(RES_DIR_OUTPUT ${OUT_DIR}/res)
set(RES_DIR ${PROJECT_SOURCE_DIR}/res)

add_custom_command(OUTPUT  ${RES_DIR_OUTPUT}
  COMMAND echo "Generating res dir"
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${RES_DIR}  ${RES_DIR_OUTPUT}
  COMMENT  "res file copy"
 )
add_custom_target(res ALL DEPENDS ${RES_DIR_OUTPUT})

add_custom_command(TARGET res
  POST_BUILD
  COMMAND echo "executing a res command"
 )

add_executable(OIL
    browser.h
    browserwindow.h
    downloadmanagerwidget.h
    downloadwidget.h
    tabwidget.h
    webpage.h
    webpopupwindow.h
    webview.h
    mongoose.h
    parameterserver.h
    simplethread.h
    urldecode.h
    easylogging++.h
    configuru.hpp
    browser.cpp
    browserwindow.cpp
    downloadmanagerwidget.cpp
    downloadwidget.cpp
    main.cpp
    tabwidget.cpp
    webpage.cpp
    webpopupwindow.cpp
    webview.cpp
    mongoose.c
    parameterserver.cpp
    urldecode.cpp
    certificateerrordialog.ui
    passworddialog.ui
    downloadmanagerwidget.ui
    downloadwidget.ui
)

target_link_libraries(OIL PRIVATE Qt5::Widgets Qt5::WebEngineWidgets )
