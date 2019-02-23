#ifndef _FLIPPER_HPP_
#define _FLIPPER_HPP_

class Flipper{
	pros::Motor* motor1;
	pros::Motor* motor2;
	double DOWN_POSITION;
	double UP_POSITION;
	double TILT_POSITION;
	double SMALL_TILT_POSITION;
public:
	Flipper();
	void initFlipper(int motor1Port, int motor2Port);
	void set(int speed);
	void down();
	bool isDown();
	void downBlocking();
	void up();
	bool isUp();
	void upBlocking();
	void tilt();
	bool isTilt();
	void tiltBlocking();
	void smallTilt();
	bool isSmallTilt();
	void smallTiltBlocking();
	void printMotorTemps();
};

extern Flipper robotFlipper;

#endif