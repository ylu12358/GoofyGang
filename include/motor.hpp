#ifndef MOTOR_HPP
#define MOTOR_HPP

#include "okapi/api.hpp"
using namespace okapi;

extern ChassisControllerPID chassisController;
extern AsyncMotionProfileController profileController;

extern int selector;

int sgn(int input);
int clipnum(int input, int clip);

void set_tank(int input_l, int input_r);
void set_intake(int input);
void set_tray(int input);
void set_arm(int input);
void drive_hold();
void drive_coast();
void intake_hold();
void intake_coast();
void tray_hold();
void tray_coast();
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
int get_auton_select();
bool tray_pressed();
void auto_selector();
void set_arm_pid(int input);
void arm_pid(void *);

#define TRAY_OUT 6100

#endif