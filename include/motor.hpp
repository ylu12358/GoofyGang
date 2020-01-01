#ifndef MOTOR_HPP
#define MOTOR_HPP

#include "okapi/api.hpp"
using namespace okapi;

extern ChassisControllerPID chassisController;
extern AsyncMotionProfileController profileController;

extern int selector;

int sgn(int input);
int clipnum(int input, int clip);

void set_tank(double input_l, double input_r);
void set_slow_tank(int input_l, int input_r);
void slow_chassis(int volt);
void normal_chassis();
void drive_hold();
void drive_coast();
void set_intake(int input);
void intake_relative(int pos, int vel);
void set_intake_speed(int32_t input);
void intake_hold();
void intake_coast();
void set_tray(int input);
void tray_hold();
void tray_coast();
void set_arm(int input);
void arm_hold();
void arm_coast();
void reset_drive_encoder();
void reset_intake_encoder();
void reset_tray_encoder();
void reset_arm_encoder();
int get_left_drive_pos();
int get_right_drive_pos();
int get_left_drive_spe();
int get_right_drive_spe();
int get_tray_pos();
int get_arm_pos();
int get_line();
int get_auton_select();
bool tray_pressed();
void auto_selector();
void set_tray_pid(int input);
void tray_pid(void *);
void set_arm_pid(int input);
void arm_pid(void *);
void drive_straight(int speed, int dis);
void suspend_tray();
void resume_tray();
void suspend_arm();
void resume_arm();
int get_left_intake_pos();
int get_right_intake_pos();


#define TRAY_OUT 3520
#define PROTECTED 2400
#define TRAY_IN 1990

//#define CUBE_IN

#endif