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

	Logger::setDefaultLogger(
    	std::make_shared<Logger>(
			TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
			"/ser/sout", // Output to the PROS terminal
			Logger::LogLevel::debug // Show errors and warnings
		)
	);

	reset_all_encoders();
	pros::delay(200);

	//std::cout<<chassisController->getModel()->getSensorVals()[0]<<std::endl; //left sensor
	//std::cout<<chassisController->getModel()->getSensorVals()[1]<<std::endl; //right sensor
	//chassisController getState theta convert(degree) //odometry

	intake_hold();

	auto_selector();
	pros::delay(100);
	if (selector == 1)
//		init_6cube();
	if (selector == 2)
//		init_6cube();
	if (selector == 3)
//		init_protected();
	if (selector == 4)
//		init_protected();
	if (selector == 5)
	{
		// tank = false;
		// init_skills();
	}
	if(selector == 6){
//		init_pickup();
	}
}

void disabled() {}

void competition_initialize() {}

void autonomous()
{
	pros::Task output(sensors, nullptr, "name");

	if (selector == 1)
		unprotect(RED);
	if (selector == 2)
		unprotect(BLUE);
	if (selector == 3)
		protect(RED);
	if (selector == 4)
		protect(BLUE);
	if (selector == 5)
	{
//		skills1();
//		skills2();		
//		protected_blue();
	}
	if (selector == 6) //TESTING SLOT
		//protected_auton();
//		pickup();
//		one_cube();
	{
		test();
	}
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

//		printf("tray sensor: %d", get_tray_pos()); //testing printf
		std::cout<<get_arm_pos()<<std::endl; //testing cout 

		pros::delay(20);
	}
}