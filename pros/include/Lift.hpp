#ifndef _LIFT_HPP_
#define _LIFT_HPP_

class Lift{
	int8_t leftMotor;
	int8_t rightMotor;
public:
	Lift();
	void initLift(int8_t leftPort, int8_t rightPort);
	okapi::AsyncPosIntegratedController makeLift();
};

extern Lift robotLift;

#endif