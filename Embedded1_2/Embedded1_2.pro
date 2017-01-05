#-------------------------------------------------
#
# Project created by QtCreator 2015-08-17T19:24:36
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Embedded1_2
TEMPLATE = app
INCLUDEPATH +=/root/eigen2

SOURCES += main.cpp\
        gui.cpp \
    src/udpdata.cpp \
    src/can_com.cpp \
    motorthread.cpp \
    worktimer.cpp \
    udpthread.cpp \
    src/reso_rates.cpp

HEADERS  += gui.h \
    src/udpdata.h \
    src/dictionary.h \
    src/can_com.h \
    motorthread.h \
    worktimer.h \
    udpthread.h \
    src/reso_rates.h

FORMS    += gui.ui

linux-*{
    target.path=./
    INSTALLS+=target
}

OTHER_FILES += \
    usr_cmd.sh
