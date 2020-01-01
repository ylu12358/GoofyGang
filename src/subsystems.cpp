#include "main.h"

int arm_counter = 1;
int tray_counter = 0;
bool cube = false;
bool intake;

void tray_outtake()
{
    while (get_tray_pos() < 2400)
        set_tray(127);
    intake_coast();
    while (get_tray_pos() < 2800)
    {
        set_tray(100);
        set_intake(13);
    }
    while (get_tray_pos() < TRAY_OUT)
    {
        set_intake(-13);
        set_tray(50);
    }
    
    set_tray(0);
    set_intake(0);
}

void intake_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    //intake_coast();
    intake_hold();
    while (true)
    {
        // if(intake){
        //     master.print(0, 0, "%f", "test:" + intake);
            if (master.get_digital(DIGITAL_R1)) {
                set_intake(127);
                cube = true;
            }
            else if (master.get_digital(DIGITAL_R2))
                set_intake(-127);
            // else {
            //     if(cube){
            //         //change sensor value
            //         while(get_line()<0){
            //             //test if outtake voltage is usable for all amount of cubes -> might be non-linear
            //             set_intake(-20);
            //             pros::delay(20);
            //         }
            //     } else{
            //         set_intake(0);
            //     }
            //}
            else if (arm_counter == 1){

                set_intake(10);
            }
            else
                set_intake(0);
//        }
        pros::delay(20);

    }
}

void drive_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    drive_coast();
    normal_chassis();
    bool tank = true;
    while (true)
    {
        if(!tank) //arcade
            set_tank((master.get_analog(ANALOG_LEFT_X) + master.get_analog(ANALOG_RIGHT_Y)), (-master.get_analog(ANALOG_LEFT_X) + master.get_analog(ANALOG_RIGHT_Y)));
        else if(tank) //tank
            set_tank(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_Y));
        if(master.get_digital(DIGITAL_DOWN)){ //switch
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
            if(arm_counter == 1)
            {
                tray_counter++;
                switch (tray_counter)
                {
                case 0: //intake
                    resume_tray();
                    set_tray_pid(TRAY_IN);
                    intake_coast();
                    break;
                case 1: //protected (smaller horizontal space)
                    set_tray_pid(PROTECTED);
                    break;
                case 2: //score
                    cube = false;
                    suspend_tray();
                    tray_outtake();
                    tray_counter = -1;
                    intake_hold();
                    break;
                }
            while (master.get_digital(DIGITAL_L1))
                pros::delay(10);
            }
        }
        pros::delay(20);
    }
}

void arm_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    
    set_arm(-50);
    pros::delay(100);
    reset_arm_encoder();
    set_arm(0);
    set_arm_pid(0);
    arm_coast();
    bool pid_on = true;

    while(true){
        if(master.get_digital(DIGITAL_L2))
        {
            set_arm(0);
            while(master.get_digital(DIGITAL_L2))
                pros::delay(10);
            switch(arm_counter)
            {
            case 0: //arm down
                if (tray_counter == 0)
                {
                    //cube = true;
                    set_arm_pid(0);
                    set_intake_speed(12000);
                    arm_counter++;
                }
                break;
            case 1: //first tower height
                if (tray_counter == 0)
                {
                    intake = true;
                    pros::delay(20);
                    intake_relative(-10000.0,-200);		
                    cube = false;
                    resume_arm();
                    
                    //500
                    set_arm_pid(1300);
                    //change time delay
                    pros::delay(190);
                    intake = false;
                    set_intake_speed(8500);
                    arm_counter++;
                }
                break;
            case 2: //second tower height
                if (tray_counter == 0)
                {
                    //800
                    set_arm_pid(1600);
                    //6500
                    set_intake_speed(10000);
                }
                arm_counter = 0;
                break; 
            }
        } else if(get_arm_pos() < 20 && arm_counter == 1){
            suspend_arm();
            set_arm(-10);
            reset_arm_encoder();
            set_intake_speed(12000);
        }
        pros::delay(20);
    }
}