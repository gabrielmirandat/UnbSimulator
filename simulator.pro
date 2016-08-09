#To make a project qtable, just add a .pro file with the following tags
#run with  qmake -o Makefile simulator.pro to generate the makefile
#run make

OBJECTS_DIR= generated_files #Intermediate object files directory
MOC_DIR=     generated_files #Intermediate moc files directory
DESTDIR=     bin             #Target file directory
INCLUDEPATH= common/include  #Path for included files

CONFIG += qt

TARGET = simulator

HEADERS +=         common/include/*.h \
                   common/data/*.h

SOURCES +=         common/src/*.cc \
                   main.cc
		   		   
QT += core

LIBS += -lopencv_core -lboost_system -lboost_thread -lboost_timer
