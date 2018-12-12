#include "main.h"

using namespace pros;

Claw robotClaw;

Claw::Claw() {};

void Claw::initClaw(int motor1Port, int motor2Port)
{
	bool motor1Reverse = motor1Port < 0;
	if(motor1Port < 0) motor1Port *= -1;

	Motor* motor1Motor = new Motor((std::uint8_t) motor1Port, E_MOTOR_GEARSET_36, motor1Reverse, E_MOTOR_ENCODER_DEGREES);

	motor1 = (Motor*) malloc(sizeof(Motor));

	memcpy(motor1, motor1Motor, sizeof(*motor1Motor));

	bool motor2Reverse = motor2Port < 0;
	if(motor2Port < 0) motor2Port *= -1;

	Motor* motor2Motor = new Motor((std::uint8_t) motor2Port, E_MOTOR_GEARSET_36, motor2Reverse, E_MOTOR_ENCODER_DEGREES);

	motor2 = (Motor*) malloc(sizeof(pros::Motor));

	memcpy(motor2, motor2Motor, sizeof(*motor2Motor));
}

void Claw::set(int speed)
{
	motor1->move(speed);
	motor2->move(speed);

	std::cout << "Motor 1: " << motor1->get_temperature() << std::endl;
}

void Claw::open()
{
	motor1->move_absolute(60, 60);
	motor2->move_absolute(60, 60);
}

void Claw::close()
{
	motor1->move_absolute(10, 127);
	motor2->move_absolute(10, 127);
}