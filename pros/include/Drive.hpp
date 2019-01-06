#ifndef _DRIVE_HPP_
#define _DRIVE_HPP_

#include "main.h"

class Drive{
private:
	pros::Motor* frontLeft;
	pros::Motor* frontRight;
	pros::Motor* middleLeft;
	pros::Motor* middleRight;
	pros::Motor* rearLeft;
	pros::Motor* rearRight;

	const double wheelDiameter = 4.0;
	const double wheelBaseWidth = 15.0;
public:
	Drive();
	void initDrive(int frontLeftPort, int frontRightPort, int middleLeftPort, int middleRightPort, int rearLeftPort, int rearRightPort);
	void tankDrive(int left, int right);
	void moveDistance(double distance, int speed = 90);
	void turnAngle(double angle, int speed = 90);
	void getMotorTemps();
};

extern Drive robotDrive;

#endif