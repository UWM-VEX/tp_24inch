#include "main.h"

using namespace okapi;

Lift robotLift;

Lift::Lift() {};

void Lift::initLift(int8_t leftPort, int8_t rightPort)
{
	leftMotor = leftPort;
	rightMotor = rightPort;
}

AsyncPosIntegratedController Lift::makeLift()
{
	Motor left(leftMotor);
	Motor right(rightMotor);

	return AsyncControllerFactory::posIntegrated(leftMotor, rightMotor);
}