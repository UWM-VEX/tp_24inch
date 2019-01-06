#ifndef _TURNER_HPP_
#define _TURNER_HPP_

class Turner{
	pros::Motor* driver;
	bool turnForward = true;
public:
	Turner();
	void initTurner(int driverPort);
	void set(int speed);
	bool rotate180(bool isFirstTime);
	void printMotorTemps();
};

extern Turner robotTurner;

#endif