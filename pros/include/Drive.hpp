#ifndef _DRIVE_HPP_
#define _DRIVE_HPP_

#include "main.h"

class Drive{
private:
	pros::Motor* frontLeft;
	pros::Motor* frontRight;
	pros::Motor* rearLeft;
	pros::Motor* rearRight;

	const double wheelDiameter = 4.0;
	const double wheelBaseWidth = 10.0;
public:
	Drive();
	void initDrive(int frontLeftPort, int frontRightPort, int rearLeftPort, int rearRightPort);
	void tankDrive(int left, int right);
	bool moveDistance(double distance);
};

extern Drive robotDrive;

#endif