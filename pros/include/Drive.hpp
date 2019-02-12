#ifndef _DRIVE_HPP_
#define _DRIVE_HPP_

#include "main.h"

class Drive{
private:
	int8_t frontLeft;
	int8_t frontRight;
	int8_t middleLeft;
	int8_t middleRight;
	int8_t rearLeft;
	int8_t rearRight;
public:
	Drive();
	void initDrive(int8_t frontLeftPort, int8_t frontRightPort, int8_t middleLeftPort, int8_t middleRightPort, int8_t rearLeftPort, int8_t rearRightPort);
	okapi::ChassisControllerIntegrated makeDrive();
};

extern Drive robotDrive;

#endif
