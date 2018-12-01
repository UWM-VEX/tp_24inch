#include "main.h"

using namespace okapi;

Drive robotDrive;

Drive::Drive() {}

void Drive::initDrive(int8_t frontLeftPort, int8_t frontRightPort, int8_t rearLeftPort, int8_t rearRightPort)
{
	frontLeft = frontLeftPort;
	frontRight = frontRightPort;
	rearLeft = rearLeftPort;
	rearRight = rearRightPort;
}

okapi::ChassisControllerIntegrated Drive::makeDrive()
{
	Motor fl(frontLeft);
	Motor fr(frontRight);
	Motor rl(rearLeft);
	Motor rr(rearRight);

	return ChassisControllerFactory::create(
		  {fl, rl}, {fr, rr},
		  AbstractMotor::gearset::green,
		  {4_in, 17_in}
		);
}