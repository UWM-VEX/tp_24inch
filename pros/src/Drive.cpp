#include "main.h"
#include <cmath>

using namespace okapi;

Drive robotDrive;

Drive::Drive() {}

void Drive::initDrive(int8_t frontLeftPort, int8_t frontRightPort, int8_t middleLeftPort, int8_t middleRightPort, int8_t rearLeftPort, int8_t rearRightPort)
{
	frontLeft = frontLeftPort;
	frontRight = frontRightPort;
	middleLeft = middleLeftPort;
	middleRight = middleRightPort;
	rearLeft = rearLeftPort;
	rearRight = rearRightPort;
}

okapi::ChassisControllerIntegrated Drive::makeDrive()
{
	return ChassisControllerFactory::create(
		  {frontLeft, middleLeft, rearLeft}, {frontRight, middleRight, rearRight},
		  AbstractMotor::gearset::green,
		  {1.8_in, 15_in}
		);
}