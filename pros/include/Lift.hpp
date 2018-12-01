#ifndef _LIFT_HPP_
#define _LIFT_HPP_

class Lift{
	int8_t leftMotor;
	int8_t rightMotor;
	int8_t left2Motor;
	int8_t right2Motor;
public:
	Lift();
	void initLift(int8_t leftPort, int8_t rightPort, int8_t left2Port, int8_t right2Port);
	okapi::AsyncPosIntegratedController makeLift();
};

extern Lift robotLift;

#endif