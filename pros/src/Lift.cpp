#include "main.h"

using namespace pros;

Lift robotLift;

Lift::Lift() {};

void Lift::initLift(int leftPort, int rightPort, int left2Port, int right2Port)
{
	left = new Motor((std::uint8_t) abs(leftPort), E_MOTOR_GEARSET_18, leftPort < 0, E_MOTOR_ENCODER_ROTATIONS);
	left2 = new Motor((std::uint8_t) abs(left2Port), E_MOTOR_GEARSET_18, left2Port < 0, E_MOTOR_ENCODER_ROTATIONS);
	right = new Motor((std::uint8_t) abs(rightPort), E_MOTOR_GEARSET_18, rightPort < 0, E_MOTOR_ENCODER_ROTATIONS);
	right2 = new Motor((std::uint8_t) abs(right2Port), E_MOTOR_GEARSET_18, right2Port < 0, E_MOTOR_ENCODER_ROTATIONS);
}

void Lift::set(int speed)
{
	left->move(speed);
	right->move(speed);
	left2->move(speed);
	right2->move(speed);
}