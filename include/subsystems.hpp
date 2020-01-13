#ifndef SUBSYSTEMS_HPP
#define SUBSYSTEMS_HPP

void print_counters();

void tray_outtake();
void intake_control(void *);
void drive_control(void *);
void tray_control(void *);
void arm_control(void *);
extern bool intake;
extern bool tank;

#endif