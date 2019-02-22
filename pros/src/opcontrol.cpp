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

	okapi::ChassisControllerIntegrated opcontrolDrive = robotDrive.makeDrive();

	bool flipperAuto = false;
	bool liftAuto = false;

	while (true) {
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
		{
			opcontrolDrive.tank((master.get_analog(ANALOG_LEFT_Y) * 0.3)/127.0, (master.get_analog(ANALOG_RIGHT_Y) * 0.3)/127.0);
		}
		else
		{
			opcontrolDrive.tank((master.get_analog(ANALOG_LEFT_Y))/127.0, (master.get_analog(ANALOG_RIGHT_Y))/127.0);
		}

		if(std::abs(partner.get_analog(ANALOG_LEFT_Y)) > 20)
		{
			robotLift.set(partner.get_analog(ANALOG_LEFT_Y));
			liftAuto = false;
		}
		else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
		{
			robotLift.zeroh();
			liftAuto = true;
		}
		else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
		{
			robotLift.travelh();
			liftAuto = true;
		}
		else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
		{
			robotLift.highposth();
			liftAuto = true;
		}
		else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
		{
			robotLift.highpostfliph();
			liftAuto = true;
		}
		else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
		{
			robotLift.lowposth();
			liftAuto = true;
		}
		else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT))
		{
			robotLift.lowpostfliph();
			liftAuto = true;
		}
		else if(!liftAuto)
		{
			robotLift.set(0);
		}
		
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
