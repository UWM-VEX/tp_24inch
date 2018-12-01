#include "main.h"

using namespace okapi;

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
	ChassisControllerIntegrated autoDrive = robotDrive.makeDrive();

	auto profileController = AsyncControllerFactory::motionProfile(
		0.75,  // Maximum linear velocity of the Chassis in m/s
		1.0,  // Maximum linear acceleration of the Chassis in m/s/s
		10.0, // Maximum linear jerk of the Chassis in m/s/s/s
		autoDrive // Chassis Controller
	);

	autoDrive.setMaxVelocity(125);

	AsyncPosIntegratedController autoLift = robotLift.makeLift();

	bool firstTime = false;

	switch(autonomousInfoStruct.mode)
	{
		case(DO_NOTHING):

		break;
		case(TEST):
			autoDrive.moveDistance(5_ft);
			autoDrive.turnAngle(90_deg);
			pros::delay(500);
			autoDrive.turnAngle(-90_deg);
			autoDrive.moveDistance(-5_ft);
		break;
		case(MOTION_PROFILE):
			profileController.generatePath({
			  okapi::Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
			  okapi::Point{5_ft, -2_ft, 0_deg}}, // The next point in the profile, 3 feet forward
			  "A" // Profile name
			);

			profileController.setTarget("A");

			profileController.waitUntilSettled();
		break;
		case(TWO_CAPS):
			autoDrive.moveDistance(2_ft);
			pros::delay(500);
			autoDrive.moveDistance(-1_ft);
			pros::delay(500);
			autoDrive.turnAngle(60_deg);
			pros::delay(500);
			autoDrive.moveDistance(2_ft);
			robotClaw.set(-127);
			pros::delay(500);

			while(!robotTurner.rotate180(firstTime))
			{
				firstTime = false;
				pros::delay(20);
			}

			robotClaw.set(30);
			pros::delay(500);
			robotClaw.set(0);
			autoDrive.moveDistance(-18_in);


		break;
		default:
		// Do nothing
		break;
	}
}
