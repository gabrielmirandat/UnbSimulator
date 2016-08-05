#ifndef MOTION_H_
#define MOTION_H_

#include <iostream>

class Motion
{
private:
	//void
public:
	Motion(){};
	~Motion(){};

	void walk(int x,int y,int z) const {
		std::cout << "Motion::walk" << std::endl;};

	void head(float angle_x, float angle_y) const {
		std::cout << "Motion::head" << std::endl;};

	void kick() const {
		std::cout << "Motion::kick" << std::endl;};

	void run();

};

#endif //MOTION_H_
