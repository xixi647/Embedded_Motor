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

DEFINES+=EMBED_1
#DEFINES+=DISABLE_NODE6

SOURCES +=\
    ../../Embedded1_2/worktimer.cpp \
    ../../Embedded1_2/udpthread.cpp \
    ../../Embedded1_2/motorthread.cpp \
    ../../Embedded1_2/gui.cpp \
    ../../Embedded1_2/src/udpdata.cpp \
    ../../Embedded1_2/src/reso_rates.cpp \
    ../../Embedded1_2/src/can_com.cpp \
    ../../Embedded1_2/main.cpp


HEADERS  +=\
    ../../Embedded1_2/worktimer.h \
    ../../Embedded1_2/udpthread.h \
    ../../Embedded1_2/motorthread.h \
    ../../Embedded1_2/gui.h \
    ../../Embedded1_2/src/udpdata.h \
    ../../Embedded1_2/src/reso_rates.h \
    ../../Embedded1_2/src/can_com.h \
    ../../Embedded1_2/src/dictionary.h


FORMS    += gui.ui

linux-*{
    target.path=./
    INSTALLS+=target
}

OTHER_FILES += \
    usr_cmd.sh
