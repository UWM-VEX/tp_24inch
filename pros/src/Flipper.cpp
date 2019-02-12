#include "main.h"

using namespace pros;

Flipper robotFlipper;

Flipper::Flipper() {};

void Flipper::initFlipper(int motor1Port, int motor2Port)
{
	motor1 = new Motor((std::uint8_t) abs(motor1Port), E_MOTOR_GEARSET_18, motor1Port < 0, E_MOTOR_ENCODER_DEGREES);
	motor2 = new Motor((std::uint8_t) abs(motor2Port), E_MOTOR_GEARSET_18, motor2Port < 0, E_MOTOR_ENCODER_DEGREES);
}

void Flipper::set(int speed)
{
	motor1->move(speed);
	motor2->move(speed);
}

void Flipper::down()
{
	motor1->move_absolute(-840, 127);
	motor2->move_absolute(-840, 127);
}

void Flipper::up()
{
	motor1->move_absolute(-380, 127);
	motor2->move_absolute(-380, 127);
}

void Flipper::printMotorTemps()
{
	lcd::print(0, "Motor 1: %f", motor1->get_temperature());
	lcd::print(1, "Motor 2: %f", motor2->get_temperature());
}