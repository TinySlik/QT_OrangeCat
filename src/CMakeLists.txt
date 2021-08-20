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
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/memorymapped.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/memorymapped.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/dataprocesswidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/dataprocesswidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/decoder/manchesterdecoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/decoder/manchesterdecoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/decoder/personificationdecoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/decoder/personificationdecoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/decoder/personificationdecoderv2.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/decoder/personificationdecoderv2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/decoder/highfrequencysensivitydecoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/filter/decoder/highfrequencysensivitydecoder.cpp
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

if(OS_WIN)
  set(QT_DEPTH_PLATFORM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/impl.win32.cpp)
else()
  set(QT_DEPTH_PLATFORM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/impl.linux.cpp)
endif()

set(SOURCE_DEPTH_FILES ${QRC_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/urldecode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/window.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/memorymapped.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/memorymapped.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/displaywidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/displaywidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/time.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/renderutil.h
    ${CMAKE_CURRENT_SOURCE_DIR}/samples/depth/renderutil.cpp
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
    ${QT_DEPTH_PLATFORM_FILES}
)

set(SOURCE_ABMDAO_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/abmdaolib.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/common/base/basecommon.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/common/base/baseentity.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/common/file/fileutils.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/common/json/jsonutils.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/common/log/easylogging++.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/common/mysql/SqlUtils.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/config/config.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/config/dao/currentdatadao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/config/entity/currentdata.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/dao/runinfodesdao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/dao/runinfodrillstatsdao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/dao/runinfogeneraldao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/dao/runinfomatchedsystemstrackingdao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/dao/runinfomudstatsdao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/dao/runinfomwdstatsdao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/dao/runinforeliabilitydao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/entity/runinfodes.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/entity/runinfodrillstats.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/entity/runinfogeneral.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/entity/runinfomatchedsystemstracking.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/entity/runinfomudstats.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/entity/runinfomwdstats.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/entity/runinforeliability.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/toolParam/dao/abidao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/toolParam/dao/dgrdao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/toolParam/dao/hcimdao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/toolParam/dao/pcddao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/toolParam/dao/pospulserdao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/toolParam/dao/toolparametersdao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/toolParam/entity/abi.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/toolParam/entity/dgr.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/toolParam/entity/hcim.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/toolParam/entity/pcd.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/toolParam/entity/pospulser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/toolParam/entity/toolparameters.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/wellinfodao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/wellinfodistancesdao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/wellinfoformationdao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/wellinfogeneraldao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/wellinfolocationdao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/wellinfomatchedsystemstrackingdao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/wellinfopersonneldao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/wellinfosurveyinfodao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/entity/wellinfo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/entity/wellinfodistances.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/entity/wellinfoformation.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/entity/wellinfogeneral.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/entity/wellinfolocation.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/entity/wellinfomatchedsystemstracking.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/entity/wellinfopersonnel.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/entity/wellinfosurveyinfo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/ABMDaoLib_global.h
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
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/dao/runinfodesdao.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/dao/runinfodrillstatsdao.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/dao/runinfogeneraldao.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/dao/runinfomatchedsystemstrackingdao.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/dao/runinfomudstatsdao.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/dao/runinfomwdstatsdao.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/dao/runinforeliabilitydao.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/entity/runinfodes.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/entity/runinfodrillstats.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/entity/runinfogeneral.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/entity/runinfomatchedsystemstracking.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/entity/runinfomudstats.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/entity/runinfomwdstats.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/runinfo/entity/runinforeliability.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/toolParam/dao/abidao.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/toolParam/dao/dgrdao.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/toolParam/dao/hcimdao.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/toolParam/dao/pcddao.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/toolParam/dao/pospulserdao.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/toolParam/dao/toolparametersdao.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/toolParam/entity/abi.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/toolParam/entity/dgr.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/toolParam/entity/hcim.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/toolParam/entity/pcd.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/toolParam/entity/pospulser.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/toolParam/entity/toolparameters.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/wellinfodao.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/wellinfodistancesdao.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/wellinfoformationdao.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/wellinfogeneraldao.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/wellinfolocationdao.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/wellinfomatchedsystemstrackingdao.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/wellinfopersonneldao.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/wellinfosurveyinfodao.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/entity/wellinfo.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/entity/wellinfodistances.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/entity/wellinfoformation.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/entity/wellinfogeneral.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/entity/wellinfolocation.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/entity/wellinfomatchedsystemstracking.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/entity/wellinfopersonnel.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/entity/wellinfosurveyinfo.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/configuru.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/welldao.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/welldao.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/dao/jsoninterface.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/entity/wellinfodepthstatus.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib/well/entity/wellinfodepthstatus.h
)

include_directories(log)
include_directories(paramserv)
include_directories(../3rdparty/asyncplusplus/include)
include_directories(../3rdparty/ADlink/include)
include_directories(../3rdparty/liblas/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ABMDaoLib)

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-expansion-to-defined -Wno-deprecated-declarations" )
add_executable(sample ${SOURCE_FILTER_FILES})
#target_link_libraries(sample PRIVATE Qt5::Widgets Qt5::WebEngineWidgets Qt5::Quick Qt5::Svg paramserv Async++ ADlink)
if (ADLINK_32)
  target_link_libraries(sample PRIVATE Qt5::Widgets Qt5::WebEngineWidgets Qt5::Quick Qt5::Svg paramserv Async++ ADlink)
else()
  target_link_libraries(sample PRIVATE Qt5::Widgets Qt5::WebEngineWidgets Qt5::Quick Qt5::Svg paramserv Async++)
endif()


add_definitions(-DABMDAOLIB_LIBRARY)

add_library(ABMDaoLib ${SOURCE_ABMDAO_FILES})
target_link_libraries(ABMDaoLib PRIVATE Qt5::Widgets Qt5::Sql)

add_executable(display ${SOURCE_GENERAL_FILES})

target_link_libraries(display PRIVATE Qt5::Widgets Qt5::Quick Qt5::Svg paramserv)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/samples/gamma/qcustomplot)

add_executable(gamma ${SOURCE_GAMMA_FILES})

target_link_libraries(gamma PRIVATE Qt5::Widgets Qt5::PrintSupport Qt5::Svg paramserv las)

add_executable(depth ${SOURCE_DEPTH_FILES})

target_link_libraries(depth PRIVATE Qt5::Widgets Qt5::Quick Qt5::Svg Qt5::Sql paramserv ABMDaoLib)
