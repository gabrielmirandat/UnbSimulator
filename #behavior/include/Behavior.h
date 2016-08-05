#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_

#include <iostream>

class Behavior
{
private:
	
public:
	Behavior(){};
	~Behavior(){};

	void searchBall() const {
		std::cout << "		Behavior::searchBall" << std::endl;};

	void alignGoal() const {
		std::cout << "		Behavior::alignGoal" << std::endl;};

	void checkBondaries() const {
		std::cout << "		Behavior::checkBondaries" << std::endl;};

	void run();
};

#endif //BEHAVIOR_H_