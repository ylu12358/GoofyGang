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
		unproRed1();
	if (selector == 2)
		unproBlue1();
	if (selector == 3)
		proRed();
	if (selector == 4)
		proBlue();
	if (selector == 5)
		skills();
	if (selector == 6) //TESTING SLOT
		oneCube();
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
