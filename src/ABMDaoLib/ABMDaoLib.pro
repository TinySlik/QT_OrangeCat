QT += core gui sql

TEMPLATE = lib
DEFINES += ABMDAOLIB_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

Debug:MOC_DIR =             $$PWD/../../../build/ABMDaoLib/debug
Debug:RCC_DIR =             $$PWD/../../../build/ABMDaoLib/debug
Debug:UI_DIR =              $$PWD/../../../build/ABMDaoLib/debug
Debug:OBJECTS_DIR =         $$PWD/../../../build/ABMDaoLib/debug

Release:MOC_DIR =           $$PWD/../../../build/ABMDaoLib/release
Release:RCC_DIR =           $$PWD/../../../build/ABMDaoLib/release
Release:UI_DIR =            $$PWD/../../../build/ABMDaoLib/release
Release:OBJECTS_DIR =       $$PWD/../../../build/ABMDaoLib/release

Debug:DESTDIR = $$PWD/../../../_output/ABMDaoLib/debug
Release:DESTDIR = $$PWD/../../../_output/ABMDaoLib/release

CONFIG += build_all
CONFIG += debug_and_release

contains(DEFINES, WIN64){
    CONFIG(debug, debug|release){
        TARGET = ABMDaoLib-x64
    }else{
        TARGET = ABMDaoLib-x64
    }
}else{
    CONFIG(debug, debug|release){
        TARGET = ABMDaoLib
    }else{
        TARGET = ABMDaoLib
    }
}

SOURCES += \
    abmdaolib.cpp \
    common/base/basecommon.cpp \
    common/base/baseentity.cpp \
    common/file/fileutils.cpp \
    common/json/jsonutils.cpp \
    common/log/easylogging++.cc \
    common/mysql/SqlUtils.cpp \
    pulse/dao/pospulserdao.cpp \
    pulse/entity/pospulser.cpp \
    runinfo/dao/runinfodesdao.cpp \
    runinfo/dao/runinfodrillstatsdao.cpp \
    runinfo/dao/runinfogeneraldao.cpp \
    runinfo/dao/runinfomatchedsystemstrackingdao.cpp \
    runinfo/dao/runinfomudstatsdao.cpp \
    runinfo/dao/runinfomwdstatsdao.cpp \
    runinfo/dao/runinforeliabilitydao.cpp \
    runinfo/entity/runinfodes.cpp \
    runinfo/entity/runinfodrillstats.cpp \
    runinfo/entity/runinfogeneral.cpp \
    runinfo/entity/runinfomatchedsystemstracking.cpp \
    runinfo/entity/runinfomudstats.cpp \
    runinfo/entity/runinfomwdstats.cpp \
    runinfo/entity/runinforeliability.cpp \
    well/dao/wellinfodao.cpp \
    well/dao/wellinfodistancesdao.cpp \
    well/dao/wellinfoformationdao.cpp \
    well/dao/wellinfogeneraldao.cpp \
    well/dao/wellinfolocationdao.cpp \
    well/dao/wellinfomatchedsystemstrackingdao.cpp \
    well/dao/wellinfopersonneldao.cpp \
    well/dao/wellinfosurveyinfodao.cpp \
    well/entity/wellinfo.cpp \
    well/entity/wellinfodistances.cpp \
    well/entity/wellinfoformation.cpp \
    well/entity/wellinfogeneral.cpp \
    well/entity/wellinfolocation.cpp \
    well/entity/wellinfomatchedsystemstracking.cpp \
    well/entity/wellinfopersonnel.cpp \
    well/entity/wellinfosurveyinfo.cpp


HEADERS += \
    ABMDaoLib_global.h \
    abmdaolib.h \
    common/base/basecommon.h \
    common/base/baseentity.h \
    common/file/fileutils.h \
    common/json/jsonutils.h \
    common/log/easylogging++.h \
    common/mysql/SqlUtils.h \
    pulse/dao/pospulserdao.h \
    pulse/entity/pospulser.h \
    runinfo/dao/runinfodesdao.h \
    runinfo/dao/runinfodrillstatsdao.h \
    runinfo/dao/runinfogeneraldao.h \
    runinfo/dao/runinfomatchedsystemstrackingdao.h \
    runinfo/dao/runinfomudstatsdao.h \
    runinfo/dao/runinfomwdstatsdao.h \
    runinfo/dao/runinforeliabilitydao.h \
    runinfo/entity/runinfodes.h \
    runinfo/entity/runinfodrillstats.h \
    runinfo/entity/runinfogeneral.h \
    runinfo/entity/runinfomatchedsystemstracking.h \
    runinfo/entity/runinfomudstats.h \
    runinfo/entity/runinfomwdstats.h \
    runinfo/entity/runinforeliability.h \
    well/dao/wellinfodao.h \
    well/dao/wellinfodistancesdao.h \
    well/dao/wellinfoformationdao.h \
    well/dao/wellinfogeneraldao.h \
    well/dao/wellinfolocationdao.h \
    well/dao/wellinfomatchedsystemstrackingdao.h \
    well/dao/wellinfopersonneldao.h \
    well/dao/wellinfosurveyinfodao.h \
    well/entity/wellinfo.h \
    well/entity/wellinfodistances.h \
    well/entity/wellinfoformation.h \
    well/entity/wellinfogeneral.h \
    well/entity/wellinfolocation.h \
    well/entity/wellinfomatchedsystemstracking.h \
    well/entity/wellinfopersonnel.h \
    well/entity/wellinfosurveyinfo.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
