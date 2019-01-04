#include "main.h"
#include <cmath>

using namespace pros;

Turner robotTurner;

Turner::Turner() {};

void Turner::initTurner(int driverPort)
{
	driver = new Motor((std::uint8_t) abs(driverPort), E_MOTOR_GEARSET_18, driverPort < 0, E_MOTOR_ENCODER_ROTATIONS);
}

void Turner::set(int speed)
{
	driver->move(speed);
}

bool Turner::rotate180(bool isFirstTime)
{
	if(isFirstTime)
	{
		if(turnForward)
		{
			driver->move_relative(2.75, 127);
		}
		else
		{
			driver->move_relative(-2.75, 127);
		}

		turnForward = ! turnForward;
	}

	return std::abs(driver->get_position() - driver->get_target_position()) < 0.05;
}