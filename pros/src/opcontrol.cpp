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
	okapi::AsyncPosIntegratedController opcontrolLift = robotLift.makeLift();

	bool lastTurnerRotate = false;
	bool turnerAuto = false;
	bool lastClawClosed = false;

	while (true) {
		robotDrive.tankDrive((master.get_analog(ANALOG_LEFT_Y)), (master.get_analog(ANALOG_RIGHT_Y)));

		opcontrolLift.controllerSet(partner.get_analog(ANALOG_LEFT_Y) / 127.0);

		if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
		{
			robotClaw.set(60);
			lastClawClosed = false;
		}
		else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_R2) ||
			lastClawClosed)
		{
			robotClaw.set(-60);
			lastClawClosed = true;
		}
		else
		{
			robotClaw.set(0);
		}

		if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) ||
			partner.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
			turnerAuto = false;
		else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_UP) ||
			partner.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
			turnerAuto = true;

		if(turnerAuto)
		{
			robotTurner.rotate180((partner.get_digital(pros::E_CONTROLLER_DIGITAL_UP)
				|| partner.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) && ! lastTurnerRotate);

			lastTurnerRotate = partner.get_digital(pros::E_CONTROLLER_DIGITAL_UP) ||
								partner.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
		}
		else
		{
			if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
			{
				robotTurner.set(-30);
			}
			else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT))
			{
				robotTurner.set(30);
			}
			else
			{
				robotTurner.set(0);
			}
		}
		
		pros::delay(20);
	}
}
