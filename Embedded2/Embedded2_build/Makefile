#############################################################################
# Makefile for building: Embedded1_2
# Generated by qmake (2.01a) (Qt 4.5.0) on: Sun Nov 15 20:04:16 2015
# Project:  ../Embedded1_2/Embedded1_2.pro
# Template: app
# Command: /opt/EmbedSky/qt-4.5/build/build_arm/bin/qmake -spec /opt/EmbedSky/qt-4.5/__install/arm/mkspecs/qws/linux-arm-g++ -unix -o Makefile ../Embedded1_2/Embedded1_2.pro
#############################################################################

####### Compiler, tools and options

CC            = arm-linux-gcc
CXX           = arm-linux-g++
DEFINES       = -DEMBED_2 -DDISABLE_NODE6 -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/qws/linux-arm-g++ -I../Embedded1_2 -I/opt/EmbedSky/qt-4.5/__install/arm/include/QtCore -I/opt/EmbedSky/qt-4.5/__install/arm/include/QtNetwork -I/opt/EmbedSky/qt-4.5/__install/arm/include/QtGui -I/opt/EmbedSky/qt-4.5/__install/arm/include -I/root/eigen2 -I../Embedded1_2 -I../Embedded1_2 -I.
LINK          = arm-linux-g++
LFLAGS        = -Wl,-O1 -Wl,-rpath,/opt/EmbedSky/qt-4.5/__install/arm/lib
LIBS          = $(SUBLIBS)  -L/opt/EmbedSky/qt-4.5/__install/arm//lib -lQtGui -L/tslib-1.4/libc -L/opt/EmbedSky/qt-4.5/__install/arm//lib -lts -lQtNetwork -lQtCore -lm -lrt -ldl -lpthread
AR            = arm-linux-ar cqs
RANLIB        = 
QMAKE         = /opt/EmbedSky/qt-4.5/build/build_arm/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = ../../Embedded1_2/worktimer.cpp \
		../../Embedded1_2/udpthread.cpp \
		../../Embedded1_2/motorthread.cpp \
		../../Embedded1_2/gui.cpp \
		../../Embedded1_2/src/udpdata.cpp \
		../../Embedded1_2/src/reso_rates.cpp \
		../../Embedded1_2/src/can_com.cpp \
		../../Embedded1_2/main.cpp moc_worktimer.cpp \
		moc_udpthread.cpp \
		moc_motorthread.cpp \
		moc_gui.cpp \
		moc_reso_rates.cpp
OBJECTS       = worktimer.o \
		udpthread.o \
		motorthread.o \
		gui.o \
		udpdata.o \
		reso_rates.o \
		can_com.o \
		main.o \
		moc_worktimer.o \
		moc_udpthread.o \
		moc_motorthread.o \
		moc_gui.o \
		moc_reso_rates.o
DIST          = /opt/EmbedSky/qt-4.5/__install/arm/mkspecs/common/g++.conf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/common/unix.conf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/common/linux.conf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/common/qws.conf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/qconfig.pri \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/qt_functions.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/qt_config.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/exclusive_builds.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/default_pre.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/release.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/default_post.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/warn_on.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/qt.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/unix/thread.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/moc.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/resources.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/uic.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/yacc.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/lex.prf \
		../Embedded1_2/Embedded1_2.pro
QMAKE_TARGET  = Embedded1_2
DESTDIR       = 
TARGET        = Embedded1_2

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_gui.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: ../Embedded1_2/Embedded1_2.pro  /opt/EmbedSky/qt-4.5/__install/arm/mkspecs/qws/linux-arm-g++/qmake.conf /opt/EmbedSky/qt-4.5/__install/arm/mkspecs/common/g++.conf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/common/unix.conf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/common/linux.conf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/common/qws.conf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/qconfig.pri \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/qt_functions.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/qt_config.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/exclusive_builds.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/default_pre.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/release.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/default_post.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/warn_on.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/qt.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/unix/thread.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/moc.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/resources.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/uic.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/yacc.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/lex.prf \
		/opt/EmbedSky/qt-4.5/__install/arm/lib/libQtGui.prl \
		/opt/EmbedSky/qt-4.5/__install/arm/lib/libQtNetwork.prl \
		/opt/EmbedSky/qt-4.5/__install/arm/lib/libQtCore.prl
	$(QMAKE) -spec /opt/EmbedSky/qt-4.5/__install/arm/mkspecs/qws/linux-arm-g++ -unix -o Makefile ../Embedded1_2/Embedded1_2.pro
/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/common/g++.conf:
/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/common/unix.conf:
/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/common/linux.conf:
/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/common/qws.conf:
/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/qconfig.pri:
/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/qt_functions.prf:
/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/qt_config.prf:
/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/exclusive_builds.prf:
/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/default_pre.prf:
/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/release.prf:
/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/default_post.prf:
/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/warn_on.prf:
/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/qt.prf:
/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/unix/thread.prf:
/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/moc.prf:
/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/resources.prf:
/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/uic.prf:
/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/yacc.prf:
/opt/EmbedSky/qt-4.5/__install/arm/mkspecs/features/lex.prf:
/opt/EmbedSky/qt-4.5/__install/arm/lib/libQtGui.prl:
/opt/EmbedSky/qt-4.5/__install/arm/lib/libQtNetwork.prl:
/opt/EmbedSky/qt-4.5/__install/arm/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /opt/EmbedSky/qt-4.5/__install/arm/mkspecs/qws/linux-arm-g++ -unix -o Makefile ../Embedded1_2/Embedded1_2.pro

dist: 
	@$(CHK_DIR_EXISTS) ../Embedded1_2/.tmp/Embedded1_21.0.0 || $(MKDIR) ../Embedded1_2/.tmp/Embedded1_21.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) ../Embedded1_2/.tmp/Embedded1_21.0.0/ && $(COPY_FILE) --parents ../../Embedded1_2/worktimer.h ../../Embedded1_2/udpthread.h ../../Embedded1_2/motorthread.h ../../Embedded1_2/gui.h ../../Embedded1_2/src/udpdata.h ../../Embedded1_2/src/reso_rates.h ../../Embedded1_2/src/can_com.h ../../Embedded1_2/src/dictionary.h ../Embedded1_2/.tmp/Embedded1_21.0.0/ && $(COPY_FILE) --parents ../../Embedded1_2/worktimer.cpp ../../Embedded1_2/udpthread.cpp ../../Embedded1_2/motorthread.cpp ../../Embedded1_2/gui.cpp ../../Embedded1_2/src/udpdata.cpp ../../Embedded1_2/src/reso_rates.cpp ../../Embedded1_2/src/can_com.cpp ../../Embedded1_2/main.cpp ../Embedded1_2/.tmp/Embedded1_21.0.0/ && $(COPY_FILE) --parents ../Embedded1_2/gui.ui ../Embedded1_2/.tmp/Embedded1_21.0.0/ && (cd `dirname ../Embedded1_2/.tmp/Embedded1_21.0.0` && $(TAR) Embedded1_21.0.0.tar Embedded1_21.0.0 && $(COMPRESS) Embedded1_21.0.0.tar) && $(MOVE) `dirname ../Embedded1_2/.tmp/Embedded1_21.0.0`/Embedded1_21.0.0.tar.gz . && $(DEL_FILE) -r ../Embedded1_2/.tmp/Embedded1_21.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_worktimer.cpp moc_udpthread.cpp moc_motorthread.cpp moc_gui.cpp moc_reso_rates.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_worktimer.cpp moc_udpthread.cpp moc_motorthread.cpp moc_gui.cpp moc_reso_rates.cpp
moc_worktimer.cpp: ../../Embedded1_2/src/reso_rates.h \
		../../Embedded1_2/src/udpdata.h \
		../../Embedded1_2/src/dictionary.h \
		../../Embedded1_2/motorthread.h \
		../../Embedded1_2/src/can_com.h \
		../../Embedded1_2/worktimer.h
	/opt/EmbedSky/qt-4.5/__install/arm//bin/moc $(DEFINES) $(INCPATH) ../../Embedded1_2/worktimer.h -o moc_worktimer.cpp

moc_udpthread.cpp: ../../Embedded1_2/udpthread.h
	/opt/EmbedSky/qt-4.5/__install/arm//bin/moc $(DEFINES) $(INCPATH) ../../Embedded1_2/udpthread.h -o moc_udpthread.cpp

moc_motorthread.cpp: ../../Embedded1_2/src/can_com.h \
		../../Embedded1_2/src/dictionary.h \
		../../Embedded1_2/motorthread.h
	/opt/EmbedSky/qt-4.5/__install/arm//bin/moc $(DEFINES) $(INCPATH) ../../Embedded1_2/motorthread.h -o moc_motorthread.cpp

moc_gui.cpp: ../../Embedded1_2/udpthread.h \
		../../Embedded1_2/motorthread.h \
		../../Embedded1_2/src/can_com.h \
		../../Embedded1_2/src/dictionary.h \
		../../Embedded1_2/worktimer.h \
		../../Embedded1_2/src/reso_rates.h \
		../../Embedded1_2/src/udpdata.h \
		../../Embedded1_2/gui.h
	/opt/EmbedSky/qt-4.5/__install/arm//bin/moc $(DEFINES) $(INCPATH) ../../Embedded1_2/gui.h -o moc_gui.cpp

moc_reso_rates.cpp: ../../Embedded1_2/src/reso_rates.h
	/opt/EmbedSky/qt-4.5/__install/arm//bin/moc $(DEFINES) $(INCPATH) ../../Embedded1_2/src/reso_rates.h -o moc_reso_rates.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_gui.h
compiler_uic_clean:
	-$(DEL_FILE) ui_gui.h
ui_gui.h: ../Embedded1_2/gui.ui
	/opt/EmbedSky/qt-4.5/__install/arm/bin/uic ../Embedded1_2/gui.ui -o ui_gui.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

worktimer.o: ../../Embedded1_2/worktimer.cpp ../../Embedded1_2/worktimer.h \
		../../Embedded1_2/src/reso_rates.h \
		../../Embedded1_2/src/udpdata.h \
		../../Embedded1_2/src/dictionary.h \
		../../Embedded1_2/motorthread.h \
		../../Embedded1_2/src/can_com.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o worktimer.o ../../Embedded1_2/worktimer.cpp

udpthread.o: ../../Embedded1_2/udpthread.cpp ../../Embedded1_2/udpthread.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o udpthread.o ../../Embedded1_2/udpthread.cpp

motorthread.o: ../../Embedded1_2/motorthread.cpp ../../Embedded1_2/motorthread.h \
		../../Embedded1_2/src/can_com.h \
		../../Embedded1_2/src/dictionary.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o motorthread.o ../../Embedded1_2/motorthread.cpp

gui.o: ../../Embedded1_2/gui.cpp ../../Embedded1_2/gui.h \
		../../Embedded1_2/udpthread.h \
		../../Embedded1_2/motorthread.h \
		../../Embedded1_2/src/can_com.h \
		../../Embedded1_2/src/dictionary.h \
		../../Embedded1_2/worktimer.h \
		../../Embedded1_2/src/reso_rates.h \
		../../Embedded1_2/src/udpdata.h \
		ui_gui.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gui.o ../../Embedded1_2/gui.cpp

udpdata.o: ../../Embedded1_2/src/udpdata.cpp ../../Embedded1_2/src/udpdata.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o udpdata.o ../../Embedded1_2/src/udpdata.cpp

reso_rates.o: ../../Embedded1_2/src/reso_rates.cpp ../../Embedded1_2/src/reso_rates.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o reso_rates.o ../../Embedded1_2/src/reso_rates.cpp

can_com.o: ../../Embedded1_2/src/can_com.cpp ../../Embedded1_2/src/can_com.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o can_com.o ../../Embedded1_2/src/can_com.cpp

main.o: ../../Embedded1_2/main.cpp ../../Embedded1_2/gui.h \
		../../Embedded1_2/udpthread.h \
		../../Embedded1_2/motorthread.h \
		../../Embedded1_2/src/can_com.h \
		../../Embedded1_2/src/dictionary.h \
		../../Embedded1_2/worktimer.h \
		../../Embedded1_2/src/reso_rates.h \
		../../Embedded1_2/src/udpdata.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o ../../Embedded1_2/main.cpp

moc_worktimer.o: moc_worktimer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_worktimer.o moc_worktimer.cpp

moc_udpthread.o: moc_udpthread.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_udpthread.o moc_udpthread.cpp

moc_motorthread.o: moc_motorthread.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_motorthread.o moc_motorthread.cpp

moc_gui.o: moc_gui.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_gui.o moc_gui.cpp

moc_reso_rates.o: moc_reso_rates.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_reso_rates.o moc_reso_rates.cpp

####### Install

install_target: first FORCE
	@$(CHK_DIR_EXISTS) $(INSTALL_ROOT)/home/zhuzhijun/Codes/Embedded_Motor/Embedded2/Embedded1_2/./ || $(MKDIR) $(INSTALL_ROOT)/home/zhuzhijun/Codes/Embedded_Motor/Embedded2/Embedded1_2/./ 
	-$(INSTALL_PROGRAM) "$(QMAKE_TARGET)" "$(INSTALL_ROOT)/$(QMAKE_TARGET)"
	-arm-linux-strip "$(INSTALL_ROOT)/$(QMAKE_TARGET)"

uninstall_target:  FORCE
	-$(DEL_FILE) "$(INSTALL_ROOT)/$(QMAKE_TARGET)"
	-$(DEL_DIR) $(INSTALL_ROOT)/home/zhuzhijun/Codes/Embedded_Motor/Embedded2/Embedded1_2/./ 


install:  install_target  FORCE

uninstall: uninstall_target   FORCE

FORCE:

