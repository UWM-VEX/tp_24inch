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

	while (true) {
		robotDrive.tankDrive(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_Y));

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
		{
			robotShooter.set(127);
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
		{
			robotShooter.set(-127);
		}
		else
		{
			robotShooter.set(0);
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A))
		{
			robotIntake.setRoller(127);
			robotIntake.setElevator(127);
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B))
		{
			robotIntake.setRoller(-127);
			robotIntake.setElevator(-127);
		}
		else
		{
			robotIntake.setRoller(0);
			robotIntake.setElevator(0);
		}
		
		pros::delay(20);
	}
}
