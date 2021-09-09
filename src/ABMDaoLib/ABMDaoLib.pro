QT += core gui sql

TEMPLATE = lib
DEFINES += _WIN_ADBM_EXPORTING

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
    well/dao/welldao.cpp \
    well/dao/jsoninterface.cpp



HEADERS += \
    windllsupport.h \
    abmdaolib.h \
    common/base/basecommon.h \
    common/base/baseentity.h \
    common/file/fileutils.h \
    common/json/jsonutils.h \
    common/log/easylogging++.h \
    common/mysql/SqlUtils.h \
    well/dao/welldao.h \
    well/dao/jsoninterface.h \
    well/dao/configuru.hpp
# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
