#ifndef _FLIPPER_HPP_
#define _FLIPPER_HPP_

class Flipper{
	pros::Motor* motor1;
	pros::Motor* motor2;
public:
	Flipper();
	void initFlipper(int motor1Port, int motor2Port);
	void set(int speed);
	void down();
	void up();
	void printMotorTemps();
};

extern Flipper robotFlipper;

#endif