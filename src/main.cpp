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
	reset_all_encoders();

	pros::lcd::initialize();
	pros::lcd::register_btn1_cb(on_center_button);

	intake_hold();
	
//	Actual_Route_init();

	auto_selector();
	pros::delay(100);
	if (selector == 1)
		init_6cube();
//		init_upr();
	if (selector == 2)
		init_6cube();
//		init_upb();
	if (selector == 3)
		init_pr();
	if (selector == 4)
		init_pb();
	if (selector == 5)
	{
		tank = false;
		init_skills();
	}
	if(selector == 6){
		Actual_Route_init();
	}
}

void disabled() {}

void competition_initialize() {}

void autonomous()
{

//	Actual_Route();

	if (selector == 1)
		u_6cube(RED);
	if (selector == 2)
		u_6cube(BLUE);
	if (selector == 3)
		proRed();
	if (selector == 4)
		proBlue();
	if (selector == 5)
	{
		skills1();
		//skills2();		
	}
	if (selector == 6) //TESTING SLOT
		Actual_Route();
	//	one_cube();
//		test();
}

void opcontrol()
{
	
	pros::Controller master(CONTROLLER_MASTER);
	master.set_text(0, 0, "#ThankYou448X");
	start_driver();

	stacking_state();

	pros::Task drive_control_t(drive_control, nullptr, "name");
	pros::Task tray_control_t(tray_control, nullptr, "name");
	pros::Task arm_control_t(arm_control, nullptr, "name");

	while (true)
	{
		pros::lcd::set_text(1, "Selector Value: " + std::to_string(selector));
		pros::lcd::set_text(2, "Tray Sensor:" + std::to_string(get_tray_pos()));
		pros::lcd::set_text(3, "Arm Sensor:" + std::to_string(get_arm_pos()));

		pros::delay(20);
	}
}