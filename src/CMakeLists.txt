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
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/urldecode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/window.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/memorymapped.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/memorymapped.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/dataprocesswidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/dataprocesswidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/bitdecoder/manchesterdecoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/bitdecoder/manchesterdecoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/bitdecoder/personificationdecoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/bitdecoder/personificationdecoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/bitdecoder/personificationdecoderv2.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/bitdecoder/personificationdecoderv2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/bitdecoder/highfrequencysensivitydecoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/bitdecoder/highfrequencysensivitydecoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/msgdecoder/msgdecoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/msgdecoder/msgdecoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/msgdecoder/tinimsgdecoderv1.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/msgdecoder/tinimsgdecoderv1.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/msgdecoder/tinimsgdecoderv2.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/msgdecoder/tinimsgdecoderv2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/time.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/renderutil.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/renderutil.cpp
    ${QT_FILTER_PLATFORM_FILES}
)

if(OS_WIN)
  set(QT_GENERAL_PLATFORM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/general/impl.win32.cpp)
else()
  set(QT_GENERAL_PLATFORM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/general/impl.linux.cpp)
endif()

set(SOURCE_GENERAL_FILES ${QRC_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/general/urldecode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/general/mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/general/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/general/window.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/general/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/general/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/general/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/general/memorymapped.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/general/memorymapped.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/general/displaywidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/general/displaywidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/general/time.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/general/renderutil.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/general/renderutil.cpp
    ${QT_GENERAL_PLATFORM_FILES}
)

if(OS_WIN)
  set(QT_GAMMA_PLATFORM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/impl.win32.cpp)
else()
  set(QT_GAMMA_PLATFORM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/impl.linux.cpp)
endif()

include_directories(gamma)

set(SOURCE_GAMMA_FILES ${QRC_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/memorymapped.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/memorymapped.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/time.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/renderutil.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/renderutil.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/customplottest.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/customplottest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/customplottest.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/qcustomplot/qcustomplot.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/qcustomplot/qcustomplot.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/drawImage/BaseItem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/drawImage/BaseItem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/drawImage/drawlineinfo.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/drawImage/drawlineinfo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/drawImage/DrawPictureHead.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/drawImage/DrawPictureHead.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/qteklinechat.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/qteklinechat.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/qteklinechat.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/type.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/customwidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/customwidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/rangeslider.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/rangeslider.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/glchartwidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/glchartwidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/time.cpp
    ${QT_GAMMA_PLATFORM_FILES}
)


set(SOURCE_DEPTH_FILES ${QRC_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/depthwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/depthwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/depthwindow.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/dialogdepthconfiguration.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/dialogdepthconfiguration.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/dialogdepthconfiguration.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/dialogactivatysettings.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/dialogactivatysettings.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/dialogactivatysettings.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/dialogdepthcalibration.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/dialogdepthcalibration.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/dialogdepthcalibration.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/dialogdepthctrl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/dialogdepthctrl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/dialogdepthctrl.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/dialogsetupdrawworks.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/dialogsetupdrawworks.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/dialogsetupdrawworks.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/dialogcalibrationworksheet.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/dialogcalibrationworksheet.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/dialogcalibrationworksheet.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/dialogdepthcardconfigration.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/dialogdepthcardconfigration.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/dialogdepthcardconfigration.h
)

set(SOURCE_ABMDAO_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/abmdaolib.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/common/base/basecommon.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/common/base/baseentity.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/common/file/fileutils.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/common/json/jsonutils.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/common/mysql/SqlUtils.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/config/config.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/config/dao/currentdatadao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/config/entity/currentdata.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/windllsupport.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/abmdaolib.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/common/base/basecommon.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/common/base/baseentity.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/common/file/fileutils.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/common/json/jsonutils.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/common/log/easylogging++.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/common/mysql/SqlUtils.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/config/config.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/config/dao/currentdatadao.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/config/entity/currentdata.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/configuru.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/welldao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/welldao.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/jsoninterface.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/jsoninterface.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/entity/wellinfodepthstatus.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/entity/wellinfodepthstatus.h
)

include_directories(log)
include_directories(paramserv)
include_directories(../3rdparty/asyncplusplus/include)
include_directories(../3rdparty/ADlink/include)
include_directories(../3rdparty/liblas/include)
include_directories(../3rdparty/libcdf/include)
include_directories(../3rdparty/gtest/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib)

link_directories(../3rdparty/gtest/lib)
#QTest，QtCore，QtGui
add_definitions(-D_WIN_ADBM_EXPORTING)
#add_definitions(-DAUTO_INITIALIZE_EASYLOGGINGPP)

add_library(ABMDaoLib ${SOURCE_ABMDAO_FILES})
target_link_libraries(ABMDaoLib PRIVATE Qt5::Widgets Qt5::Sql)

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-expansion-to-defined -Wno-deprecated-declarations" )
add_executable(sample WIN32 ${SOURCE_FILTER_FILES})
#target_link_libraries(sample PRIVATE Qt5::Widgets Qt5::WebEngineWidgets Qt5::Quick Qt5::Svg paramserv Async++ ADlink)
if (ADLINK_32)
  target_link_libraries(sample PRIVATE Qt5::Widgets Qt5::Quick Qt5::Svg paramserv Async++ cdf ABMDaoLib ADlink)
else()
  target_link_libraries(sample PRIVATE Qt5::Widgets Qt5::Quick Qt5::Svg paramserv Async++ cdf ABMDaoLib)
endif()

add_executable(display ${SOURCE_GENERAL_FILES})

target_link_libraries(display PRIVATE Qt5::Widgets Qt5::Quick Qt5::Svg paramserv)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/qcustomplot)

add_executable(gamma ${SOURCE_GAMMA_FILES})

target_link_libraries(gamma PRIVATE Qt5::Widgets Qt5::PrintSupport Qt5::Svg paramserv las)

add_executable(depth ${SOURCE_DEPTH_FILES})

target_link_libraries(depth PRIVATE Qt5::Widgets Qt5::Quick Qt5::Svg Qt5::Sql paramserv ABMDaoLib)
