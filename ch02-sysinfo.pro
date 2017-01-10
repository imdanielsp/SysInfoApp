#-------------------------------------------------
#
# Project created by QtCreator 2017-01-10T08:59:48
#
#-------------------------------------------------

QT       += core gui
CONFIG   += C++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ch02-sysinfo
TEMPLATE = app


SOURCES += main.cpp\
    SysInfo.cpp \
    MainWindow.cpp \
    SysInfoWidget.cpp \
    CpuWidget.cpp \
    MemoryWidget.cpp

HEADERS  += \
    SysInfo.h \
    MainWindow.h \
    SysInfoWidget.h \
    CpuWidget.h \
    MemoryWidget.h

windows {
    SOURCES += SysInfoWindowsImpl.cpp
    HEADERS += SysInfoWindowsImpl.h
}

linux {
    SOURCES += SysInfoLinuxImpl.cpp
    HEADERS += SysInfoLinuxImpl.h
}

macx {
    SOURCES += SysInfoMacImpl.cpp
    HEADERS += SysInfoMacImpl.h
}
FORMS    += \
    MainWindow.ui
