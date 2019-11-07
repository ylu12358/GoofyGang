#include "main.h"

// Otherwise, you should specify the gearset and scales for your robot
ChassisControllerPID chassisController = ChassisControllerFactory::create(
    {11, 12}, {-20, 19},
    IterativePosPIDController::Gains{0.001, 0, 0.0001}, //{0.001, 0, 0.0001}}
    IterativePosPIDController::Gains{0.001, 0, 0.0001},
    IterativePosPIDController::Gains{0.01725, 0.025, 0.0004}, //0.01, 0.000325, 0.01425, 0.0004
    AbstractMotor::gearset::green,                            //0.0175, 0.01, 0.000375
    {4.125_in, 12.28125_in});

AsyncMotionProfileController profileController = AsyncControllerFactory::motionProfile(
    0.8,                // Maximum linear velocity of the Chassis in m/s
    1.75,               // Maximum linear acceleration of the Chassis in m/s/s
    15.0,               // Maximum linear jerk of the Chassis in m/s/s/s
    chassisController); // Chassis Controller

//Motors
pros::Motor lb_drive(14, MOTOR_GEARSET_18);
pros::Motor lf_drive(13, MOTOR_GEARSET_18);
pros::Motor rf_drive(15, MOTOR_GEARSET_18, true);
pros::Motor rb_drive(16, MOTOR_GEARSET_18, true);
pros::Motor l_intake(18, MOTOR_GEARSET_18);
pros::Motor r_intake(17, MOTOR_GEARSET_18, true);
pros::Motor tray(12, MOTOR_GEARSET_18);
pros::Motor arm(11, MOTOR_GEARSET_18);

//Sensors
pros::ADIPotentiometer tray_pot('E');
pros::ADIPotentiometer arm_pot('F');
pros::ADIPotentiometer auton_selector('B');

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
void set_tank(int input_l, int input_r)
{
    lb_drive.move(input_l);
    lf_drive.move(input_l);
    rf_drive.move(input_r);
    rb_drive.move(input_r);
}

void set_intake(int input)
{
    l_intake.move(input);
    r_intake.move(input);
}

void set_tray(int input)
{
    tray.move(input);
}

void set_arm(int input)
{
    arm.move(input);
}

//Stop Motors
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

void tray_hold()
{
    tray.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void tray_coast()
{
    tray.set_brake_mode(MOTOR_BRAKE_COAST);
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
    return arm_pot.get_value();
}

int get_auton_select()
{
    return auton_selector.get_value();
}

//Auto
void auto_selector()
{
    pros::delay(300);

    //RED FRONT
    if (get_auton_select() > 0 && get_auton_select() < 1000)
    {
        selector = 1;
        return;
    }

    //BLUE FRONT
    else if (get_auton_select() > 1000 && get_auton_select() < 2000)
    {
        selector = 2;
        return;
    }

    //RED BACK
    else if (get_auton_select() > 2000 && get_auton_select() < 3000)
    {
        selector = 3;
        return;
    }

    //BLUE BACK
    else if (get_auton_select() > 3000 && get_auton_select() < 4096)
    {
        selector = 4;
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
        set_tray((t_target - get_tray_pos()) * -0.5);
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
    while (true)
    {
        set_arm((a_target - get_arm_pos()) * -0.5);
        pros::delay(20);
    }
}
