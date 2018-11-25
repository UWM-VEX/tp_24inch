#include "main.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
	okapi::ChassisControllerIntegrated autoDrive = robotDrive.makeDrive();

	auto profileController = okapi::AsyncControllerFactory::motionProfile(
		0.5,  // Maximum linear velocity of the Chassis in m/s
		2.0,  // Maximum linear acceleration of the Chassis in m/s/s
		10.0, // Maximum linear jerk of the Chassis in m/s/s/s
		autoDrive // Chassis Controller
	);

	okapi::AsyncPosIntegratedController autoLift = robotLift.makeLift();

	switch(autonomousInfoStruct.mode)
	{
		case(0):

		break;
		default:
		// Do nothing
		break;
	}
}
