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

void initialize()
{
	pros::lcd::initialize();
	pros::lcd::register_btn1_cb(on_center_button);

	reset_drive_encoder();
	reset_tray_encoder();
	reset_arm_encoder();
	reset_intake_encoder();

	set_tray_pid(TRAY_IN);
	
	auto_selector();

	if (selector == 1)
		init_upr();
	if (selector == 2)
		init_upb();
	if (selector == 3)
		init_pr();
	if (selector == 4)
		init_pb();
	if (selector == 5)
		init_skills();
	if (selector == 6)
		init_skills();
		//one cube
}

void disabled() {}

void competition_initialize() {}

void autonomous()
{
	reset_drive_encoder();
	reset_tray_encoder();
	reset_arm_encoder();
	reset_intake_encoder();

	if (selector == 1)
		unproRed();
	if (selector == 2)
		unproBlue();
	if (selector == 3)
		pro_red();
	if (selector == 4)
		pro_blue();
	if (selector == 5)
		skillsTime();
	if (selector == 6) //TESTING SLOT
		oneCube();
		//chassis_straight();
}

void opcontrol()
{
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

		pros::delay(20);
	}
}
