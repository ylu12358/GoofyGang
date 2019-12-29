#include "main.h"

//p decrease rise time

//i decrease settle time
//i increase overshoot, but gets to target
//i decrease oscillation

//d decrease overshoot
//d is sensitive to noise
//d is also sensitive to disturbance (cube pressing arm up)

//twitching like crazy might mean 
    //too HIGH of d (noise) or too LOW of i (doesnt reach target - oscillates)


ChassisControllerPID chassisController = ChassisControllerFactory::create(
    {14, 13}, {-17, -15},
    IterativePosPIDController::Gains{0.001, 0.00000001, 0.000}, //{0.001, 0, 0.0001}}//.0006
    //TUNE THIS TO STOP GETTING CROOKED DRIVING (SLANTED)
    IterativePosPIDController::Gains{0, 0, 0},
    IterativePosPIDController::Gains{0.017, 0.0001, 0.0000}, //0.01, 0.000325, 0.01425, 0.0004 //.00006
    AbstractMotor::gearset::green,                            //0.0175, 0.01, 0.000375
    {4.125_in, 12.28125_in});

AsyncMotionProfileController profileController = AsyncControllerFactory::motionProfile(
    0.8,                // Maximum linear velocity in m/s
    1.75,               // Maximum linear acceleration in m/s/s
    15.0,               // Maximum linear jerk in m/s/s/s
    chassisController); // Chassis Controller

int selector = 0;

//Motors
pros::Motor lb_drive(14, MOTOR_GEARSET_18);
pros::Motor lf_drive(13, MOTOR_GEARSET_18);
pros::Motor rf_drive(15, MOTOR_GEARSET_18, true);
pros::Motor rb_drive(17, MOTOR_GEARSET_18, true);
pros::Motor l_intake(10, MOTOR_GEARSET_18);
pros::Motor r_intake(6, MOTOR_GEARSET_18, true);
pros::Motor tray(1, MOTOR_GEARSET_18);
pros::Motor arm(11, MOTOR_GEARSET_18);
//port 2, 3, 4, 5, 7, 8, 9  ded

//Sensors
pros::ADIPotentiometer tray_pot(5);
pros::ADIPotentiometer auton_selector(6);
//add port
pros::ADILineSensor cube_in(3);

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
    lb_drive.set_voltage_limit(10000);
    lf_drive.set_voltage_limit(10000);
    rf_drive.set_voltage_limit(10000);
    rb_drive.set_voltage_limit(10000);
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
    l_intake.move(input);
    r_intake.move(input);
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
    tray.set_zero_position(0);
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

int get_line(){
    return cube_in.get_value();
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
int t_target;
void set_tray_pid(int input)
{
    t_target = input;
}

void tray_pid(void *)
{
    while (true)
    {
        set_tray((t_target - get_tray_pos()) * 0.5);
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
    float kp = 0.8;
    float integral;
    float ki = 0.001;
    float error;
    float errorT;
    float integralActiveZone = 20;
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
        power = integral + proportion;
        set_arm(power);
        pros::delay(20);
    }
}

void drive_straight(int speed, int dis)
{
    reset_drive_encoder();
    //tank_brake();
    int l_output, r_output;
    int speed_output;
    int error = dis - get_left_drive_pos();
    float kp = 0.07;
    while (abs(error) > 10)
    {
        error = dis - get_left_drive_pos();
        speed_output = clipnum(error * kp, speed);

        l_output = speed_output;
        r_output = speed_output;
        set_tank(l_output, r_output);

        pros::delay(2);
    }
    set_tank(0, 0);
}

pros::Task tray_pid_t(tray_pid, nullptr, "name");
pros::Task arm_pid_t(arm_pid, nullptr, "name");

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