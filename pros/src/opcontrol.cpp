#include "main.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Controller partner(pros::E_CONTROLLER_PARTNER);

	bool flipperAuto = false;

	while (true) {
		robotDrive.tankDrive((master.get_analog(ANALOG_LEFT_Y)), (master.get_analog(ANALOG_RIGHT_Y)));

		robotLift.set(partner.get_analog(ANALOG_LEFT_Y));

		if(std::abs(partner.get_analog(ANALOG_RIGHT_Y)) > 20)
		{
			robotFlipper.set(partner.get_analog(ANALOG_RIGHT_Y));
			flipperAuto = false;
		}
		else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
		{
			robotFlipper.up();
			flipperAuto = true;
		}
		else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
		{
			robotFlipper.down();
			flipperAuto = true;
		}
		else if(!flipperAuto)
		{
			robotFlipper.set(0);
		}
		
		pros::delay(20);
	}
}
