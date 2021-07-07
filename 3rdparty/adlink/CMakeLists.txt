# Copyright (c) 2021 TiniOh
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

cmake_minimum_required(VERSION 3.1)
project(ADlink C CXX)

add_definitions(-D_WIN_EXPORTING)

set(ADLINK_SRC
    ${PROJECT_SOURCE_DIR}/src/adlink.cpp
    ${PROJECT_SOURCE_DIR}/src/JytekAi.cpp
    ${PROJECT_SOURCE_DIR}/src/JytekDIO.cpp
    ${PROJECT_SOURCE_DIR}/src/JytekAiDataProcess.cpp
)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

#LINK_LIBRARIES("${PROJECT_SOURCE_DIR}/lib/USB-Dask.lib")

add_library(${PROJECT_NAME} SHARED ${ADLINK_SRC})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads "${PROJECT_SOURCE_DIR}/lib/USB-Dask.lib")



