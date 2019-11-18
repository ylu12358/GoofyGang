#include "main.h"

void on_center_button()
{
	static bool pressed = false;
	pressed = !pressed;
	if (pressed)
		pros::lcd::set_text(2, "I was pressed!");
	else
		pros::lcd::clear_line(2);
}

/*
void preauton(){
	//Reset encoders
	reset_drive_encoder();
	reset_intake_encoder();
	reset_tray_encoder();

	//Deploy
	set_intake(-127);
	pros::delay(100);
}
*/
//--------------------------------------------------------------------------------------------------

void initialize()
{
	pros::lcd::initialize();
	pros::lcd::register_btn1_cb(on_center_button);


	reset_drive_encoder();
	reset_tray_encoder();
	reset_arm_encoder();
	reset_intake_encoder();

	set_tray_pid(TRAY_IN);
	
//	auto_selector();
/*
	if (selector == 1)
		init_pb();
	if (selector == 2)
		init_pr();
	if (selector == 3)
		init_upb();
	if (selector == 4)
		init_upr();
*/

}

void disabled() {}

void competition_initialize() {}

//----------------------------------------------------------------------------

void autonomous() {

	//chassis_straight();
	//chassis_turn();
	
	
	//path_straight();
	//path_curve();

//preauton();
	
	
	//blue
	init_unpro();
//	unprotected();
/*
	if (selector == 1)
		unpro();
	if (selector == 2)
		unpro();
	if (selector == 3)
		unpro();
	if (selector == 4)
		unpro();
*/
	//include skills() in selector
}

//-----------------------------------------------------------------------

void opcontrol() {

	pros::Controller master(CONTROLLER_MASTER);
	master.set_text(0, 0, "#ThankYou448X");
	
	pros::Task drive_control_t(drive_control, nullptr, "name");
	pros::Task tray_control_t(tray_control, nullptr, "name");
	pros::Task arm_control_t(arm_control, nullptr, "name");
	pros::Task intake_control_t(intake_control, nullptr, "name");

	while (true)
	{
		pros::lcd::set_text(1, "Selector Value: " + std::to_string(selector));
		pros::lcd::set_text(2, "Tray Sensor:" + std::to_string(get_tray_pos()));
		pros::lcd::set_text(3, "Arm Sensor:" + std::to_string(get_arm_pos()));
		pros::lcd::set_text(4, "Number: " + std::to_string(get_auton_select()));

		pros::delay(20);
	}
}
//1117
//1727
