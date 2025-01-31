#include "main.h"

//tune strat
	//tune angle "Adjust p until you get a lil osccilation then add d very slowly until it stops"

	//p decrease rise time

	//i decrease settle time
	//i increase overshoot, but gets to target
	//i decrease oscillation

	//d decrease overshoot
	//d is sensitive to noise
	//d is also sensitive to disturbance (cube pressing arm up)

	//twitching like crazy might mean 
	//too HIGH of d (noise) or too LOW of i (doesnt reach target - oscillates)

std::shared_ptr<ChassisController> chassisController = ChassisControllerBuilder()
    .withMotors({11,12}, {10,9})
    .withGains({0.0200, 0.0000000000, 0.000000}, {0.0000000, 0.00000000, 0.00000000}) //.016, 0, .001    //.0012
    .withDimensions(AbstractMotor::gearset::blue, {{4.12500000_in, 10_in},  (3*300/7) }) //external ratio
    .build();

std::shared_ptr<AsyncMotionProfileController> profileController = AsyncMotionProfileControllerBuilder()
    .withLimits({2.41, 6.0, 10}) //2.4`
    .withOutput(chassisController)
    .buildMotionProfileController();

int selector = 0;

//Motors
pros::Motor lb_drive(11, MOTOR_GEARSET_18, true);
pros::Motor lf_drive(12, MOTOR_GEARSET_18, true);
pros::Motor rf_drive(9, MOTOR_GEARSET_18);
pros::Motor rb_drive(10, MOTOR_GEARSET_18);
pros::Motor l_intake(19, MOTOR_GEARSET_18);
pros::Motor r_intake(17, MOTOR_GEARSET_18, true);
pros::Motor tray(8, MOTOR_GEARSET_18);
pros::Motor arm(15, MOTOR_GEARSET_18, true);
//port  ded

//Sensors
pros::ADIPotentiometer tray_pot(1);
pros::ADIPotentiometer auton_selector(2);

//Math
int sgn(int input)
{
    if (input > 0)
        return 1;
    else if (input < 0)
        return -1;
    return 0;
}

int clipnum(int input, int clip)
{
    if (input > clip)
        return clip;
    else if (input < clip)
        return -clip;
    return input;
}

//Set Motors
void set_tank(double input_l, double input_r){
    lb_drive.move(input_l);
    lf_drive.move(input_l);
    rf_drive.move(input_r);
    rb_drive.move(input_r);
}

void set_slow_tank(int input_l, int input_r)
{
    input_l = abs(input_l) > 100 ? sgn(input_l) * 100 : input_l;
    input_r = abs(input_r) > 100 ? sgn(input_r) * 100 : input_r;

    lb_drive.move_velocity(input_l);
    lf_drive.move_velocity(input_l);
    rf_drive.move_velocity(input_r);
    rb_drive.move_velocity(input_r);
}

void slow_chassis(int volt)
{
    lb_drive.set_voltage_limit(volt);
    lf_drive.set_voltage_limit(volt);
    rf_drive.set_voltage_limit(volt);
    rb_drive.set_voltage_limit(volt);
}

void normal_chassis()
{
    lb_drive.set_voltage_limit(12000);
    lf_drive.set_voltage_limit(12000);
    rf_drive.set_voltage_limit(12000);
    rb_drive.set_voltage_limit(12000);
}

void drive_hold()
{
    lb_drive.set_brake_mode(MOTOR_BRAKE_HOLD);
    lf_drive.set_brake_mode(MOTOR_BRAKE_HOLD);
    rf_drive.set_brake_mode(MOTOR_BRAKE_HOLD);
    rb_drive.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void drive_coast()
{
    lb_drive.set_brake_mode(MOTOR_BRAKE_COAST);
    lf_drive.set_brake_mode(MOTOR_BRAKE_COAST);
    rf_drive.set_brake_mode(MOTOR_BRAKE_COAST);
    rb_drive.set_brake_mode(MOTOR_BRAKE_COAST);
}

void set_intake(int input)
{
    r_intake.move(input);
    l_intake.move(input);
}

void intake_relative(int pos, int vel)
{
    l_intake.move_relative(pos, vel);
    r_intake.move_relative(pos, vel);
}

void set_intake_speed(int32_t input)
{
    l_intake.set_voltage_limit(input);
    r_intake.set_voltage_limit(input);
}

void intake_hold()
{
    l_intake.set_brake_mode(MOTOR_BRAKE_HOLD);
    r_intake.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void intake_coast()
{
    l_intake.set_brake_mode(MOTOR_BRAKE_COAST);
    r_intake.set_brake_mode(MOTOR_BRAKE_COAST);
}

void set_tray(int input)
{
    tray.move(input);
}

void tray_hold()
{
    tray.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void tray_coast()
{
    tray.set_brake_mode(MOTOR_BRAKE_COAST);
}

void set_arm(int input)
{
    arm.move(input);
}

void arm_hold()
{
    arm.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void arm_coast()
{
    arm.set_brake_mode(MOTOR_BRAKE_COAST);
}

//Sensors
void reset_drive_encoder()
{
   lb_drive.set_zero_position(0);
   rb_drive.set_zero_position(0);
}

void reset_intake_encoder()
{
    l_intake.set_zero_position(0);
    r_intake.set_zero_position(0);
}

void reset_tray_encoder()
{
    tray.set_zero_position(0);
}

void reset_arm_encoder()
{
    arm.set_zero_position(0);
}

int get_left_drive_pos()
{
    return lb_drive.get_position();
}

int get_right_drive_pos()
{
    return rb_drive.get_position();
}

int get_left_drive_spe()
{
    return lb_drive.get_actual_velocity() / 200 * 127;
}

int get_right_drive_spe()
{
    return rb_drive.get_actual_velocity() / 200 * 127;
}

int get_left_intake_pos()
{
    return l_intake.get_position();
}
int get_right_intake_pos()
{
    return r_intake.get_position();
}

int get_tray_pos()
{
    return tray_pot.get_value();
}

int get_arm_pos()
{
    return arm.get_position();
}

int get_auton_select()
{
    return auton_selector.get_value();
}

//Auto
void auto_selector()
{
    pros::delay(300);

    //unprotected red
    if (get_auton_select() > 3850 && get_auton_select() < 4096)
    {
        selector = 1;
        return;
    }

    //unprotected blue
    else if (get_auton_select() > 2890 && get_auton_select() < 3850)
    {
        selector = 2;
        return;
    }

    //protected red
    else if (get_auton_select() > 2065 && get_auton_select() < 2890)
    {
        selector = 3;
        return;
    }

    //protected blue
    else if (get_auton_select() > 1427 && get_auton_select() < 2065)
    {
        selector = 4;
        return;
    }

    //skills
    else if (get_auton_select() > 712 && get_auton_select() < 1427)
    {
        selector = 5;
        return;
    }

    //one cube for now
    else if (get_auton_select() > 0 && get_auton_select() < 712)
    {
        selector = 6;
        return;
    }
    
    return;
}

//PID
int t_target = TRAY_IN;
void set_tray_pid(int input)
{
    t_target = input;
}

void tray_pid(void *)
{
    float power;
    float proportion;
    //.5
    float kp = 0.8; //1.1
    float integral;
    float ki = 0;
    float error;
    float errorT;
    float integralActiveZone = 20;
    float kd = 0;
    float derivative;
    float last_error;
    while (true)
    {
        error = t_target - get_tray_pos();
        proportion = error * kp;
        if(error < integralActiveZone && error!=0){
            errorT++;
        } else{
            errorT = 0;
        }
        if(errorT > 50){
            errorT = 50;
        }
        integral = errorT * ki;
        derivative = (error-last_error)*kd;
        last_error = error;
        power = integral + proportion + derivative;
        set_tray(power);
        pros::delay(20);
    }
}

int a_target;
void set_arm_pid(int input)
{
    a_target = input;
}

void arm_pid(void *)
{
    float power;
    float proportion;
    float kp = 1.2; //1
    float integral;
    float ki = 0.002; //.001
    float error;
    float errorT;
    float integralActiveZone = 20;
    float kd = 0;
    float derivative;
    float last_error;
    while (true)
    {
        error = a_target - get_arm_pos();
        proportion = error * kp;
        if(error < integralActiveZone && error!=0){
            errorT++;
        } else{
            errorT = 0;
        }
        if(errorT > 50){
            errorT = 50;
        }
        integral = errorT * ki;
        derivative = (error-last_error)*kd;
        last_error = error;
        power = integral + proportion + derivative;
        set_arm(power);
        pros::delay(20);
    }
}

void sensors(void* param){
    while(true){
        std::cout << "left:  "<<chassisController->getModel()->getSensorVals()[0] << std::endl;
        std::cout << "right: "<<chassisController->getModel()->getSensorVals()[1] << std::endl;

        pros::delay(10);
    }
}

pros::Task tray_pid_t(tray_pid, nullptr, "name");
pros::Task arm_pid_t(arm_pid, nullptr, "name");

void turnAng(float ang, float vel){
    lb_drive.move_relative(ang*5, vel);
    lf_drive.move_relative(ang*5, vel);
    rb_drive.move_relative(-ang*5, vel);
    rf_drive.move_relative(-ang*5, vel);
}

void swingTurn(float lAng, float rAng, float lVel, float rVel){
    lb_drive.move_relative(lAng*5, lVel);
    lf_drive.move_relative(lAng*5, lVel);
    rb_drive.move_relative(rAng*5, rVel);
    rf_drive.move_relative(rAng*5, rVel);
}

void suspend_tray()
{
    tray_pid_t.suspend();
}

void resume_tray()
{
    tray_pid_t.resume();
}

void suspend_arm()
{
    arm_pid_t.suspend();
}

void resume_arm()
{
    arm_pid_t.resume();
}

void reset_all_encoders()
{
    reset_drive_encoder();
	reset_tray_encoder();
	reset_arm_encoder();
	reset_intake_encoder();
}
