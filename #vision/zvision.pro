#To make a project qtable, just add a .pro file with the following tags
#run with  qmake -o Makefile vision.pro to generate the makefile
#run make

OBJECTS_DIR= generated_files 		#Intermediate object files directory
DESTDIR=     ../bin          		#Target file directory
INCLUDEPATH= include  \		        #Paths to be included
			 ../data

CONFIG += qt

TARGET = zvision

HEADERS +=         include/*.h \
				   ../data/*.h

SOURCES +=         src/*.cc \
                   zvision.cc

QT += core

LIBS += -lopencv_core -lboost_system -lboost_thread -lboost_timer
