#include "main.h"

using namespace okapi;

void turnAngleGyro(double angle, ChassisControllerIntegrated* drive, double maxSpeed = 0.5)
{
	pros::lcd::initialize();

	uint32_t timeAtAngle = 0;
	uint32_t startTime = pros::millis();

	ADIGyro gyro(1, 0.092);
	gyro.reset();

	double newOutput;
	double newInput;
	
	do
	{
		newInput = gyro.get();

		if(std::abs(newInput - angle) > 10)
		{
			newOutput = maxSpeed;
		}
		else if(std::abs(newInput - angle) > 2)
		{
			newOutput = 0.35;
		}
		else
		{
			newOutput = 0;
		}

		if(angle - newInput < 0)
		{
			newOutput *= -1;
		}

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
	}while(!(pros::millis() - timeAtAngle > 250 && timeAtAngle != 0) && pros::millis() - startTime < 2000);

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
			profileController->generatePath({
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

			profileController->waitUntilSettled();

			turnAngleGyro(90, &autoDrive);
		break;
		case(TWO_CAPS):
			if(autonomousInfoStruct.alliance == BLUE)
			{
				robotFlipper.downBlocking();

				profileController->generatePath({
				  okapi::Point{0_in, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
				  okapi::Point{40_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
				  "cap1" // Profile name
				);

				profileController->setTarget("cap1", false);
				profileController->waitUntilSettled();

				profileController->removePath("cap1");

				robotFlipper.tiltBlocking();

				profileController->generatePath({
				  okapi::Point{0_in, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
				  okapi::Point{18_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
				  "back1" // Profile name
				);

				profileController->setTarget("back1", true);
				profileController->waitUntilSettled();

				profileController->removePath("back1");

				turnAngleGyro(-60, &autoDrive);

				profileController->generatePath({
				  okapi::Point{0_in, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
				  okapi::Point{10_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
				  "getRoom" // Profile name
				);

				profileController->setTarget("getRoom", true);
				profileController->waitUntilSettled();

				profileController->removePath("getRoom");

				robotLift.lowpostfliph();
				robotLift.waitForTarget();

				robotFlipper.upBlocking();

				profileController->generatePath({
				  okapi::Point{0_in, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
				  okapi::Point{11_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
				  "pole1" // Profile name
				);

				profileController->setTarget("pole1", false);
				profileController->waitUntilSettled();

				profileController->removePath("pole1");

				robotLift.afterScore();
				robotLift.waitForTarget();

				profileController->generatePath({
					okapi::Point{0_in, 0_ft, 0_deg},
					okapi::Point{11_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
				  "back2"
				);

				profileController->setTarget("back2", true);
				profileController->waitUntilSettled();

				profileController->removePath("back2");

				robotLift.zeroh();
				robotLift.waitForTarget();
				
				robotFlipper.downBlocking();
				
				turnAngleGyro (80, &autoDrive);

				profileController->generatePath({
					okapi::Point{0_in, 0_ft, 0_deg},
					okapi::Point{15_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
				  "cap2"
				);

				profileController->setTarget("cap2", false);
				profileController->waitUntilSettled();

				profileController->removePath("cap2");

				robotFlipper.tiltBlocking();

				profileController->generatePath({
					okapi::Point{0_in, 0_ft, 0_deg},
					okapi::Point{12_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
				  "back3"
				);

				profileController->setTarget("back3", true);
				profileController->waitUntilSettled();

				profileController->removePath("back3");

				turnAngleGyro(-90, &autoDrive, 0.7);

				profileController->generatePath({
					okapi::Point{0_in, 0_ft, 0_deg},
					okapi::Point{6_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
				  "lineToPole"
				);

				profileController->setTarget("lineToPole", false);
				profileController->waitUntilSettled();

				profileController->removePath("lineToPole");

				turnAngleGyro(-80, &autoDrive, 0.7);

				profileController->generatePath({
					okapi::Point{0_in, 0_ft, 0_deg},
					okapi::Point{11_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
				  "lineToPole2"
				);

				profileController->setTarget("lineToPole2", false);

				robotLift.lowposth();

				profileController->waitUntilSettled();
				robotLift.waitForTarget();

				profileController->removePath("lineToPole2");

				robotLift.afterScore();
				robotLift.waitForTarget();

				profileController->generatePath({
					okapi::Point{0_in, 0_ft, 0_deg},
					okapi::Point{18_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
				  "backToPlatform"
				);

				profileController->setTarget("backToPlatform", true);

				robotLift.travelh();

				profileController->waitUntilSettled();
				robotLift.waitForTarget();

				profileController->removePath("backToPlatform");

				robotLift.zeroh();
				robotLift.waitForTarget();

				turnAngleGyro(90, &autoDrive);

				profileController->generatePath({
					okapi::Point{0_in, 0_ft, 0_deg},
					okapi::Point{45_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
				  "onPlatform"
				);

				profileController->setTarget("onPlatform", true);
				profileController->waitUntilSettled();
				profileController->removePath("onPlatform");

				profileController->generatePath({
					okapi::Point{0_in, 0_ft, 0_deg},
					okapi::Point{12_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
				  "onPlatform2"
				);

				profileController->setTarget("onPlatform2", true);
				profileController->waitUntilSettled();
				profileController->removePath("onPlatform2");
			}
			else
			{
				robotFlipper.downBlocking();

				profileController->generatePath({
				  okapi::Point{0_in, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
				  okapi::Point{40_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
				  "cap1" // Profile name
				);

				profileController->setTarget("cap1", false);
				profileController->waitUntilSettled();

				profileController->removePath("cap1");

				robotFlipper.tiltBlocking();

				profileController->generatePath({
				  okapi::Point{0_in, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
				  okapi::Point{15_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
				  "back1" // Profile name
				);

				profileController->setTarget("back1", true);
				profileController->waitUntilSettled();

				profileController->removePath("back1");

				turnAngleGyro(60, &autoDrive);

				profileController->generatePath({
				  okapi::Point{0_in, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
				  okapi::Point{10_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
				  "getRoom" // Profile name
				);

				profileController->setTarget("getRoom", true);
				profileController->waitUntilSettled();

				profileController->removePath("getRoom");

				robotLift.lowpostfliph();
				robotLift.waitForTarget();

				robotFlipper.upBlocking();

				profileController->generatePath({
				  okapi::Point{0_in, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
				  okapi::Point{12_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
				  "pole1" // Profile name
				);

				profileController->setTarget("pole1", false);
				profileController->waitUntilSettled();

				profileController->removePath("pole1");

				robotLift.afterScore();
				robotLift.waitForTarget();

				profileController->generatePath({
					okapi::Point{0_in, 0_ft, 0_deg},
					okapi::Point{17_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
				  "back2"
				);

				profileController->setTarget("back2", true);
				profileController->waitUntilSettled();

				profileController->removePath("back2");

				robotLift.zeroh();
				robotLift.waitForTarget();
				
				robotFlipper.downBlocking();
				
				turnAngleGyro (-80, &autoDrive);

				profileController->generatePath({
					okapi::Point{0_in, 0_ft, 0_deg},
					okapi::Point{15_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
				  "cap2"
				);

				profileController->setTarget("cap2", false);
				profileController->waitUntilSettled();

				profileController->removePath("cap2");

				robotFlipper.tiltBlocking();

				profileController->generatePath({
					okapi::Point{0_in, 0_ft, 0_deg},
					okapi::Point{12_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
				  "back3"
				);

				profileController->setTarget("back3", true);
				profileController->waitUntilSettled();

				profileController->removePath("back3");

				turnAngleGyro(90, &autoDrive, 0.5);

				profileController->generatePath({
					okapi::Point{0_in, 0_ft, 0_deg},
					okapi::Point{11_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
				  "lineToPole"
				);

				profileController->setTarget("lineToPole", false);
				profileController->waitUntilSettled();

				profileController->removePath("lineToPole");

				turnAngleGyro(72.5, &autoDrive, 0.5);

				robotFlipper.smallTiltBlocking();

				profileController->generatePath({
					okapi::Point{0_in, 0_ft, 0_deg},
					okapi::Point{9_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
				  "lineToPole2"
				);

				profileController->setTarget("lineToPole2", false);

				robotLift.lowposth();

				profileController->waitUntilSettled();
				robotLift.waitForTarget();

				profileController->removePath("lineToPole2");


				robotLift.afterScore();
				robotLift.waitForTarget();

				profileController->generatePath({
					okapi::Point{0_in, 0_ft, 0_deg},
					okapi::Point{24_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
				  "backToPlatform"
				);

				profileController->setTarget("backToPlatform", true);

				robotLift.travelh();

				profileController->waitUntilSettled();
				robotLift.waitForTarget();

				profileController->removePath("backToPlatform");

				robotLift.zeroh();
				robotLift.waitForTarget();

				turnAngleGyro(-90, &autoDrive);

				profileController->generatePath({
					okapi::Point{0_in, 0_ft, 0_deg},
					okapi::Point{45_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
				  "onPlatform"
				);

				profileController->setTarget("onPlatform", true);
				profileController->waitUntilSettled();
				profileController->removePath("onPlatform");

				profileController->generatePath({
					okapi::Point{0_in, 0_ft, 0_deg},
					okapi::Point{4_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
				  "onPlatform2"
				);

				profileController->setTarget("onPlatform2", true);
				profileController->waitUntilSettled();
				profileController->removePath("onPlatform2");
			}
		break;
		default:
		// Do nothing
		break;
	}
}
