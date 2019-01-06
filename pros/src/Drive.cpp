#include "main.h"
#include <cmath>

using namespace pros;

Drive robotDrive;

Drive::Drive() {}

void Drive::initDrive(int frontLeftPort, int frontRightPort, int middleLeftPort, int middleRightPort, int rearLeftPort, int rearRightPort)
{
	frontLeft = new Motor((std::uint8_t) abs(frontLeftPort), E_MOTOR_GEARSET_18, frontLeftPort < 0, E_MOTOR_ENCODER_ROTATIONS);
	frontRight = new Motor((std::uint8_t) abs(frontRightPort), E_MOTOR_GEARSET_18, frontRightPort < 0, E_MOTOR_ENCODER_ROTATIONS);
	middleLeft = new Motor((std::uint8_t) abs(middleLeftPort), E_MOTOR_GEARSET_18, middleLeftPort < 0, E_MOTOR_ENCODER_ROTATIONS);
	middleRight = new Motor((std::uint8_t) abs(middleRightPort), E_MOTOR_GEARSET_18, middleRightPort < 0, E_MOTOR_ENCODER_ROTATIONS);
	rearLeft = new Motor((std::uint8_t) abs(rearLeftPort), E_MOTOR_GEARSET_18, rearLeftPort < 0, E_MOTOR_ENCODER_ROTATIONS);
	rearRight = new Motor((std::uint8_t) abs(rearRightPort), E_MOTOR_GEARSET_18, rearRightPort < 0, E_MOTOR_ENCODER_ROTATIONS);
}

void Drive::tankDrive(int left, int right)
{
	frontLeft->move(left);
	frontRight->move(right);
	rearLeft->move(left);
	rearRight->move(right);
}

void Drive::moveDistance(double distance, int speed)
{
	int32_t velocity = (distance > 0) ? speed : -speed;
	double targetRotation = distance / (wheelDiameter * M_PI);

	frontLeft->move_relative(targetRotation, velocity);
	frontRight->move_relative(targetRotation, velocity);
	rearLeft->move_relative(targetRotation, velocity);
	rearRight->move_relative(targetRotation, velocity);

	bool done = false;

	while(!done)
	{
		std::cout << "Auto Looping" << std::endl;
		done = (std::abs(frontLeft->get_position() - frontLeft->get_target_position()) < 0.05) &&
		(std::abs(frontRight->get_position() - frontRight->get_target_position()) < 0.05) &&
		(std::abs(rearLeft->get_position() - rearLeft->get_target_position()) < 0.05) &&
		(std::abs(rearRight->get_position() - rearRight->get_target_position()) < 0.05);
		delay(20);
	}
}

void Drive::turnAngle(double angle, int speed)
{
	int32_t velocity = (angle > 0) ? speed : -speed;
	double distanceToTurn = (angle / 360.0) * M_PI * wheelBaseWidth;
	double targetRotation = distanceToTurn / (wheelDiameter * M_PI);

	frontLeft->move_relative(targetRotation, velocity);
	frontRight->move_relative(-targetRotation, velocity);
	rearLeft->move_relative(targetRotation, velocity);
	rearRight->move_relative(-targetRotation, velocity);

	bool done = false;

	while(!done)
	{
		std::cout << "Auto Looping" << std::endl;
		done = (std::abs(frontLeft->get_position() - frontLeft->get_target_position()) < 0.05) &&
		(std::abs(frontRight->get_position() - frontRight->get_target_position()) < 0.05) &&
		(std::abs(rearLeft->get_position() - rearLeft->get_target_position()) < 0.05) &&
		(std::abs(rearRight->get_position() - rearRight->get_target_position()) < 0.05);
		delay(20);
	}
}

void Drive::getMotorTemps()
{
	lcd::print(0, "FL: %f", frontLeft->get_temperature());
	lcd::print(1, "FR: %f", frontRight->get_temperature());
	lcd::print(2, "RL: %f", rearLeft->get_temperature());
	lcd::print(3, "RR: %f", rearRight->get_temperature());
}