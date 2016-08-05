#To make a project qtable, just add a .pro file with the following tags
#run with  qmake -o Makefile motion.pro to generate the makefile
#run make

OBJECTS_DIR= generated_files #Intermediate object files directory
MOC_DIR=     generated_files #Intermediate moc files directory
DESTDIR=     ../bin          #Target file directory
INCLUDEPATH= include         #Path for included files

CONFIG += qt

TARGET = motion 

HEADERS +=         include/*.h

SOURCES +=         src/*.cc \
                   motion.cc

QT += core

LIBS += -lopencv_core -lboost_system -lboost_thread -lboost_timer
