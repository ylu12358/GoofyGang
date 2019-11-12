#include "main.h"

void tray_outtake()
{
    while (get_tray_pos() < 1420)
        set_tray(127);
    while (get_tray_pos() < 1800)
        set_tray(40);
    while (get_tray_pos() < TRAY_OUT)
    {
        set_intake(-40);
        set_tray(20);
        intake_coast();
    }
    set_tray(0);
    set_intake(0);
}

void tray_intake()
{
    while (get_tray_pos() > TRAY_IN)
        set_tray(-127);
    set_tray(0);
    intake_hold();
}

void intake_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    intake_hold();
    while (true)
    {
        if (master.get_digital(DIGITAL_R1))
            set_intake(127); //Intake
        else if (master.get_digital(DIGITAL_R2))
            set_intake(-127); //Outtake
        else
            set_intake(0); //No movement
        pros::delay(20);
    }
}

void drive_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    drive_coast();
    bool tank = true;
    while (true)
    {
        if(!tank){
            set_tank((master.get_analog(ANALOG_LEFT_X) + master.get_analog(ANALOG_RIGHT_Y)), (-master.get_analog(ANALOG_LEFT_X) + master.get_analog(ANALOG_RIGHT_Y)));
        } else if(tank){
            set_tank(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_Y));
        }
        if(master.get_digital(DIGITAL_DOWN)){
            while (master.get_digital(DIGITAL_DOWN))
                pros::delay(10);
            tank = !tank;
        }
        pros::delay(20);
    }
}

pros::Task tray_pid_t(tray_pid, nullptr, "name");

void tray_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    int counter = 0;
    tray_hold();
    pros::delay(100);
    while (true)
    {
        if (master.get_digital(DIGITAL_L1))
        {
            counter++;
            while (master.get_digital(DIGITAL_L1))
                pros::delay(10);
            switch (counter)
            {
            case 0:
                tray_pid_t.resume();
                set_tray_pid(TRAY_IN);
                intake_hold();
                break;
            case 1:
                set_tray_pid(PROTECTED);
                break;
            case 2: 
                tray_pid_t.suspend();
                tray_outtake();
                counter = -1;
                break;
            }
        }
        pros::delay(20);
    }
}


//change power for next remake
//negative power raises the arm
void arm_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    set_arm(-80);
    pros::delay(100);
    reset_arm_encoder();
    set_arm(0);
    pros::Task arm_pid_t(arm_pid, nullptr, "name");
    set_arm_pid(0);
    int counter = 0;
    arm_hold();
    while(true){
        if(master.get_digital(DIGITAL_L2))
        {
            counter++;
            while(master.get_digital(DIGITAL_L2))
                pros::delay(10);
            switch(counter)
            {
                case 0:
                    set_arm_pid(-20);
                    pros::delay(500);
                    set_tray_pid(TRAY_IN);
                    arm_pid_t.suspend();
                    set_arm(-5);
                    break;
                case 1:
                    arm_pid_t.resume();
                    set_tray_pid(PROTECTED-100);
                    set_arm_pid(364);
                    break;
                case 2:
                    set_arm_pid(450);
                    break;
                case 3:
                    set_arm_pid(605);
                    counter = -1;
                    break;
            }
        }
        pros::delay(20);
    }
}