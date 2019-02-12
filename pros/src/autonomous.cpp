#include "main.h"

using namespace okapi;

void turnAngleGyro(double angle, ChassisControllerIntegrated* drive)
{
	pros::lcd::initialize();

	const double kP = 0.005;
	const double kI = 0.07;
	const double kD = 10;

	uint32_t timeAtAngle = 0;

	auto controller = IterativeControllerFactory::posPID(kP, kI, kD);
	ADIGyro gyro(1, 0.1);
	gyro.reset();

	controller.setTarget(angle);
	
	do
	{
		double newInput = gyro.get();
		double newOutput = controller.step(newInput);
		drive->arcade(0, newOutput);

		pros::lcd::print(0, "Gyro: %f", newInput);

		pros::Task::delay(20);

		if(std::abs(newInput - angle) < 1 && timeAtAngle == 0)
		{
			timeAtAngle = pros::millis();
		}
		else if(std::abs(newInput - angle) >= 1)
		{
			timeAtAngle = 0;
		}
	}while(!(pros::millis() - timeAtAngle > 250 && timeAtAngle != 0));

	drive->stop();
}

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

	AsyncMotionProfileController* profileController;

	profileController = new AsyncMotionProfileController(
		TimeUtilFactory::create(),
		1.0,  // Maximum linear velocity of the Chassis in m/s
		1.0,  // Maximum linear acceleration of the Chassis in m/s/s
		10.0, // Maximum linear jerk of the Chassis in m/s/s/s
		autoDrive.getChassisModel(), // Chassis Controller
		autoDrive.getChassisScales(),
		autoDrive.getGearsetRatioPair()
	);

	profileController->startThread();

	bool firstTime = false;

	autoDrive.setMaxVelocity(125);

	switch(autonomousInfoStruct.mode)
	{
		case(DO_NOTHING):

		break;
		case(TEST):
			/*profileController->generatePath({
			  okapi::Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
			  okapi::Point{3_ft, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
			  "A" // Profile name
			);

			profileController->generatePath({
			  okapi::Point{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
			  okapi::Point{2_ft, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
			  "B" // Profile name
			);

			profileController->setTarget("A");

			profileController->waitUntilSettled();

			profileController->setTarget("B");

			profileController->waitUntilSettled();*/

			turnAngleGyro(90, &autoDrive);
		break;
		default:
		// Do nothing
		break;
	}
}
