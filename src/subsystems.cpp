#include "main.h"

int arm_counter = 0;
int tray_counter = 0;
bool cube = false;
bool intake;
bool tank = true;
bool arm_ready = false;
bool in_ready = false;

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
    intake_hold();
    while (true)
    {
        if(master.get_digital(DIGITAL_L2)){
            while(!arm_ready){
                pros::delay(1);
            }
            in_ready = true;
            // if(arm_counter == 1){
                intake_hold();
                int l_intake_value = get_left_intake_pos();
                intake_relative(-525,-200);		
                while(get_left_intake_pos()-l_intake_value>=-510){
                    pros::lcd::set_text(4, "in");
                    pros::delay(5);
                    if(get_left_intake_pos()-l_intake_value>=-510){
                        set_intake(-75);
                    }
                    else {
                        continue;
                    }
                }
                pros::lcd::set_text(4, "out");
            // }
        }
        else if (master.get_digital(DIGITAL_R1)) {
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
        pros::delay(20);
    }
}

void drive_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    drive_coast();
    normal_chassis();
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
                case 1: //protected
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

    while(true){
        if(master.get_digital(DIGITAL_L2))
        {
            arm_counter++;
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
                    set_tray_pid(TRAY_IN);
                    set_intake_speed(12000);
                }
                break;
            case 1: //first tower height
                if (tray_counter == 0)
                {
                    arm_ready = true;
                    while(!in_ready){
                        pros::delay(1);
                    }
                    resume_arm();
                    set_arm_pid(1300);
                    set_tray_pid(1990);
                    set_intake_speed(8500);
                }
                break;
            case 2: //second tower height
                if (tray_counter == 0)
                {
                    set_arm_pid(1600);
                    set_intake_speed(10000);
                }
                arm_counter = -1;
                break; 
            }
        } else if(get_arm_pos() < 20 && arm_counter == 1){
            suspend_arm();
            //remove this when pid is tuned?
            set_arm(-10);
            reset_arm_encoder();
            set_intake_speed(12000);
        }
        pros::delay(20);
    }
}