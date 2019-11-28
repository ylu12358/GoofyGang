#include "main.h"

int arm_counter = 0;
int tray_counter = 0;
pros::Task tray_pid_t(tray_pid, nullptr, "name");
pros::Task arm_pid_t(arm_pid, nullptr, "name");

void tray_outtake()
{
    while (get_tray_pos() < 1470)
        set_tray(127);
    while (get_tray_pos() < 1760)
        set_tray(50);
        set_intake(-40);
    while (get_tray_pos() < TRAY_OUT)
    {
        set_tray(20);
        intake_coast();
    }
    
    set_tray(0);
    set_intake(0);
}

void intake_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    intake_coast();
    while (true)
    {
        if (master.get_digital(DIGITAL_R1))
            set_intake(127);
        else if (arm_counter == 0)
            set_intake(10);
        else
            set_intake(0);
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
        if(!tank) //arcade
            set_tank((master.get_analog(ANALOG_LEFT_X) + master.get_analog(ANALOG_RIGHT_Y)), (-master.get_analog(ANALOG_LEFT_X) + master.get_analog(ANALOG_RIGHT_Y)));
        else if(tank) //tank
            set_tank(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_Y));
        if(master.get_digital(DIGITAL_DOWN)){
            while (master.get_digital(DIGITAL_DOWN))
                pros::delay(10);
            tank = !tank;
        }
        pros::delay(20);
    }
}

void tray_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    tray_coast();
    pros::delay(100);
    while (true)
    {
        if (master.get_digital(DIGITAL_L1))
        {
            tray_counter++;
            while (master.get_digital(DIGITAL_L1))
                pros::delay(10);
            switch (tray_counter)
            {
            case 0: //intake
                tray_pid_t.resume();
                set_tray_pid(TRAY_IN);
                intake_coast();
                break;
            case 1: //protected (smaller horizontal space)
                set_tray_pid(PROTECTED);
                break;
            case 2: //score
                tray_pid_t.suspend();
                tray_outtake();
                tray_counter = -1;
                break;
            }
        }
        pros::delay(20);
    }
}

void arm_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    set_arm(-80);
    pros::delay(100);
    reset_arm_encoder();
    set_arm(0);
    set_arm_pid(0);
    arm_coast();
    while(true){
        if(master.get_digital(DIGITAL_L2))
        {
            set_arm(0);
            arm_counter++;
            arm_pid_t.resume();                
            while(master.get_digital(DIGITAL_L2))
                pros::delay(10);
            switch(arm_counter)
            {
            case 0: //arm down
                if (tray_counter == 0)
                {
                    set_arm_pid(0);
                    pros::delay(500);
                    set_tray_pid(TRAY_IN);
                    set_intake_speed(12000);
                }
                break;
            case 1: //first tower height
                if (tray_counter == 0)
                {
                    set_tray_pid(PROTECTED - 100);
                    set_arm_pid(1117);
                    set_intake_speed(8500);
                }
                break;
            case 2: //second tower height
                if (tray_counter == 0)
                {
                    set_arm_pid(1437);
                    set_intake_speed(6500);
                }
                arm_counter = -1;
                break; 
            }
        } else if(tray_counter == 0 && arm_counter <= 0){
            arm_pid_t.suspend();
            set_arm(-25);
            reset_arm_encoder();
            set_intake_speed(12000);
        }
        pros::delay(20);
    }
}