#ifndef _LIFT_HPP_
#define _LIFT_HPP_

class Lift{
	pros::Motor* left;
	pros::Motor* right;
	pros::Motor* left2;
	pros::Motor* right2;
public:
	Lift();
	void initLift(int leftPort, int rightPort, int left2Port, int right2Port);
	void set(int speed);
	void travelh();
	void afterScore();
	void zeroh();
	void lowposth();
	void lowpostfliph();
	void highposth();
	void highpostfliph();
	bool waitForTarget();
	void printMotorTemps();
};

extern Lift robotLift;

#endif
