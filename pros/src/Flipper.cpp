#include "main.h"

using namespace pros;

Flipper robotFlipper;

Flipper::Flipper() {};

void Flipper::initFlipper(int motor1Port, int motor2Port)
{
	motor1 = new Motor((std::uint8_t) abs(motor1Port), E_MOTOR_GEARSET_18, motor1Port < 0, E_MOTOR_ENCODER_DEGREES);
	motor2 = new Motor((std::uint8_t) abs(motor2Port), E_MOTOR_GEARSET_18, motor2Port < 0, E_MOTOR_ENCODER_DEGREES);

	UP_POSITION = -300;
	DOWN_POSITION = -840;
	TILT_POSITION = -650;
	SMALL_TILT_POSITION = -750;
}

void Flipper::set(int speed)
{
	motor1->move(speed);
	motor2->move(speed);
}

void Flipper::down()
{
	motor1->move_absolute(DOWN_POSITION, 127);
	motor2->move_absolute(DOWN_POSITION, 127);
}

bool Flipper::isDown()
{
	double averagePosition = (motor1->get_position() + motor2->get_position()) / 2.0;
	return std::abs(averagePosition - DOWN_POSITION) < 2;
}

void Flipper::downBlocking()
{
	uint32_t startTime = pros::millis();

	do{
		down();
		pros::delay(20);
	}while(!isDown() && pros::millis() - startTime < 2000);
}

void Flipper::up()
{
	motor1->move_absolute(UP_POSITION, 127);
	motor2->move_absolute(UP_POSITION, 127);
}

bool Flipper::isUp()
{
	double averagePosition = (motor1->get_position() + motor2->get_position()) / 2.0;
	return std::abs(averagePosition - UP_POSITION) < 2;
}

void Flipper::upBlocking()
{
	uint32_t startTime = pros::millis();
	do{
		up();
		pros::delay(20);
	}while(!isUp() && pros::millis() - startTime < 2000);
}

void Flipper::tilt()
{
	motor1->move_absolute(TILT_POSITION, 90);
	motor2->move_absolute(TILT_POSITION, 90);
}

bool Flipper::isTilt()
{
	double averagePosition = (motor1->get_position() + motor2->get_position()) / 2.0;
	return std::abs(averagePosition - TILT_POSITION) < 2;
}

void Flipper::tiltBlocking()
{
	uint32_t startTime = pros::millis();
	do{
		tilt();
		pros::delay(20);
	}while(!isTilt() && pros::millis() - startTime < 2000);
}

void Flipper::smallTilt()
{
	motor1->move_absolute(SMALL_TILT_POSITION, 90);
	motor2->move_absolute(SMALL_TILT_POSITION, 90);
}

bool Flipper::isSmallTilt()
{
	double averagePosition = (motor1->get_position() + motor2->get_position()) / 2.0;
	return std::abs(averagePosition - SMALL_TILT_POSITION) < 2;
}

void Flipper::smallTiltBlocking()
{
	uint32_t startTime = pros::millis();
	do{
		smallTilt();
		pros::delay(20);
	}while(!isSmallTilt() && pros::millis() - startTime < 2000);
}

void Flipper::printMotorTemps()
{
	lcd::print(0, "Motor 1: %f", motor1->get_temperature());
	lcd::print(1, "Motor 2: %f", motor2->get_temperature());
}
