#include "main.h"

using namespace pros;

Lift robotLift;

Lift::Lift() {};

void Lift::initLift(int leftPort, int rightPort, int left2Port, int right2Port)
{
	bool leftReverse = leftPort < 0;
	if(leftPort < 0) leftPort *= -1;

	Motor* leftMotor = new Motor((std::uint8_t) leftPort, E_MOTOR_GEARSET_18, leftReverse, E_MOTOR_ENCODER_ROTATIONS);

	left = (Motor*) malloc(sizeof(Motor));

	memcpy(left, leftMotor, sizeof(*leftMotor));

	bool rightReverse = rightPort < 0;
	if(rightPort < 0) rightPort *= -1;

	Motor* rightMotor = new Motor((std::uint8_t) rightPort, E_MOTOR_GEARSET_18, rightReverse, E_MOTOR_ENCODER_ROTATIONS);

	right = (Motor*) malloc(sizeof(Motor));

	memcpy(right, rightMotor, sizeof(*rightMotor));

	bool left2Reverse = left2Port < 0;
	if(left2Port < 0) left2Port *= -1;

	Motor* left2Motor = new Motor((std::uint8_t) left2Port, E_MOTOR_GEARSET_18, left2Reverse, E_MOTOR_ENCODER_ROTATIONS);

	left2 = (Motor*) malloc(sizeof(Motor));

	memcpy(left2, left2Motor, sizeof(*left2Motor));

	bool right2Reverse = right2Port < 0;
	if(right2Port < 0) right2Port *= -1;

	Motor* right2Motor = new Motor((std::uint8_t) right2Port, E_MOTOR_GEARSET_18, right2Reverse, E_MOTOR_ENCODER_ROTATIONS);

	right2 = (Motor*) malloc(sizeof(Motor));

	memcpy(right2, right2Motor, sizeof(*right2Motor));
}

void Lift::set(int speed)
{
	left->move(speed);
	right->move(speed);
	left2->move(speed);
	right2->move(speed);
}