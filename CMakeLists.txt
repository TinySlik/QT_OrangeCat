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
  set(QT_PATH "D:/Qt/Qt5.13.2/5.13.2")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
#  set(Qt5WebEngineWidgets_DIR ${QT_PATH}/msvc2017/lib/cmake/Qt5WebEngineWidgets)
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

find_package(Qt5 COMPONENTS Widgets WebEngineWidgets Quick REQUIRED)

set(OUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/_output")
set_outdir(
  "${OUT_DIR}/lib"
  "${OUT_DIR}/lib"
  "${OUT_DIR}/bin"
)

set(OIL_CMAKE_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}")
set(OIL_CMAKE_BINDIR "${CMAKE_INSTALL_PREFIX}/bin")
set(OIL_CMAKE_LIBDIR "${CMAKE_INSTALL_PREFIX}/lib")
set(OIL_CMAKE_INSTALLDIR "${OIL_CMAKE_LIBDIR}/cmake/${PROJECT_NAME}")

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

file(GLOB_RECURSE QRC_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/res/*.qrc)
#set(QRC_SOURCE_FILES res.qrc)
qt5_add_resources(QRC_FILES ${QRC_SOURCE_FILES})

if(OS_WIN)
  set(QT_PLATFORM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/impl.win32.cpp)
else()
  set(QT_PLATFORM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/impl.linux.cpp)
endif()

add_executable(${PROJECT_NAME}
    ${QRC_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/certificateerrordialog.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/src/passworddialog.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/src/downloadmanagerwidget.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/src/downloadwidget.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/src/browser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/browserwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/downloadmanagerwidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/downloadwidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tabwidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/webpage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/webpopupwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/webview.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mongoose.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/configuru.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parameterserver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/urldecode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/glwidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/window.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logo.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/glwidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/memorymapped.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/memorymapped.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/dataprocesswidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/dataprocesswidget.cpp
    ${QT_PLATFORM_FILES}
)

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-targets
    RUNTIME DESTINATION ${OIL_CMAKE_BINDIR}
    LIBRARY DESTINATION ${OIL_CMAKE_LIBDIR}
    ARCHIVE DESTINATION ${OIL_CMAKE_LIBDIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::WebEngineWidgets Qt5::Quick)
