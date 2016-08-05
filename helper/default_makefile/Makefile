INC= 'include/'
VISION= vision/
MOTION= motion/
BEHAVIOR= behavior/
COMM= communication/
DEBUG= -g
OPENCV= -lopencv_core
BOOST= -lboost_system -lboost_thread -lboost_timer

simulator: clean	
	g++ -o simulator main.cc $(VISION)*'.cc' $(MOTION)*'.cc' $(BEHAVIOR)*'.cc' $(COMM)*'.cc' -I$(INC) $(DEBUG) $(OPENCV) $(BOOST)

clean:
	clear