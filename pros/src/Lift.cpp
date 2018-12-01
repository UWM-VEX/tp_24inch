#include "main.h"

using namespace okapi;

Lift robotLift;

Lift::Lift() {};

void Lift::initLift(int8_t leftPort, int8_t rightPort, int8_t left2Port, int8_t right2Port)
{
	leftMotor = leftPort;
	rightMotor = rightPort;
	left2Motor = left2Port;
	right2Port = right2Port;
}

AsyncPosIntegratedController Lift::makeLift()
{
	Motor left(leftMotor);
	Motor right(rightMotor);
	Motor left2(left2Motor);
	Motor right2(right2Motor);

	return AsyncControllerFactory::posIntegrated({leftMotor, left2Motor, rightMotor, right2Motor});
}