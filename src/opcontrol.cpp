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

 //NONE OF THIS HAS BEEN TESTED BEFORE SO THERE MAY BE A LOT OF DEBUGGING THAT
 //NEEDS TO HAPPEN.

pros::Controller master(pros::E_CONTROLLER_MASTER);
bool state = LOW;
pros::ADIDigitalOut pneumatic_A = pros::ADIDigitalOut('A', state);

void testPneumatic(void);
void pneumaticLift();

void opcontrol() {
	while (true) {
		testPneumatic();

		//using single action pneumatics for a lift
		//pneumaticLift();
	}
}

void testPineumatic(void){
	if(master.get_digital(DIGITAL_A)){
		state = HIGH;
	}
	else
		state = LOW;
	pneumatic_A.set_value(state);
	pros::delay(20);
	return;
}

void pneumaticLift(void){
	static int liftWasMoving = 1;
	if(master.get_digital(DIGITAL_L1)){//moving up
		pneumatic_A.set_value(HIGH);
		//code to make lift go up
	}
	else if(master.get_digital(DIGITAL_L2)){//moving down
		pneumatic_A.set_value(LOW);
		//code to make the lift go down
	}else{
		//set value HIGH or LOW depending on wether or not the PID is heating up the
		// motors too much
		pneumatic_A.set_value(LOW);
		//send lift to hold position
	}
	return;
}

/*
pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
int left = master.get_analog(ANALOG_LEFT_Y);
int right = master.get_analog(ANALOG_RIGHT_Y);
pros::delay(20);
*/
