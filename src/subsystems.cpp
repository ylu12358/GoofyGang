#include "main.h"

int arm_counter = 0;
int tray_counter = 0;
bool tank = true;
bool safe = false;
int last_tray = TRAY_IN;
int intake_time = 0;
bool intake = true;

void tray_outtake()
{
    while (get_tray_pos() < 1600)
        set_tray(127);
    intake_coast();
    
    while (get_tray_pos() < 2150)
    {
        set_tray(70);
        set_intake(13);
    }
    
    while (get_tray_pos() < 2600)
    {
        set_tray(40);
        set_intake(13);
    }

    while (get_tray_pos() < TRAY_OUT)
    {
        set_intake(-13);
        set_tray(30);
    }
    
    set_tray(0);
    set_intake(0);
}

void fast_outtake()
{
    while (get_tray_pos() < 2200)
        set_tray(127);
    intake_coast();

    while (get_tray_pos() < TRAY_OUT - 250)
    {
        set_intake(-13);
        set_tray(40);
    }

    set_tray(0);
    set_intake(0);
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
        if(master.get_digital(DIGITAL_A)) //switch
        {
            while (master.get_digital(DIGITAL_A))
                pros::delay(10); //blocking - only executes once
            tank = !tank;
        }
        pros::delay(20);
    }
}

void tray_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    tray_coast();
    last_tray = TRAY_IN;
    pros::delay(100); // allow potentiometer to settle
    while (true)
    {
        if (master.get_digital(DIGITAL_RIGHT)){

            resume_tray();
            set_tray_pid(LOCK_SAFE);
            safe = true;
        }
        else if (master.get_digital(DIGITAL_L1))
        {
            if(arm_counter == 0)
            {
                tray_counter++;
                switch (tray_counter)
                {
                    case 0: //intake
                        resume_tray();
                        set_tray_pid(TRAY_IN);
                        intake_coast();
                        last_tray = TRAY_IN;
                        break;
                    case 1: //protected
                        set_tray_pid(PROTECTED);
                        last_tray = PROTECTED;
                        break;
                    case 2: //score
                        suspend_tray();
                        if(master.get_digital(DIGITAL_Y))
                            fast_outtake();
                        else
                            tray_outtake();
                        tray_counter = -1;
                        break;
                }
                while (master.get_digital(DIGITAL_L1))
                    pros::delay(10);
            }
        }
        else if (safe) 
        {
            set_tray_pid(last_tray);
            safe = false;
        } 
        pros::delay(20);
    }
}

void arm_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    set_arm(-100);
    pros::delay(100);
    reset_arm_encoder();
    set_arm(0);
    set_arm_pid(0);
    arm_coast();

    while(true){
        if(master.get_digital(DIGITAL_L2))
        {
            if(tray_counter == 0){
                arm_counter++;
                set_arm(0);
                while(master.get_digital(DIGITAL_L2))
                    pros::delay(10);
                switch(arm_counter)
                {
                case 0: //arm down
                    if (tray_counter == 0)
                    {
                        set_tray_pid(TRAY_IN);
                        //cube = true;
                        set_arm_pid(0);
                        set_intake_speed(12000);
                    }
                    break;
                case 1: //first tower height
                    if (tray_counter == 0)
                    {
                        intake = false;
                        while(intake_time>70){
                            set_intake(0);
                            intake_time--;
                            pros::delay(10);
                        }
                        //increase height of tray - no friction from rubberband
                        set_tray_pid(TRAY_IN+20);
                        //lift arm - fast, clear as quickly as possible
                        set_arm(127);
                        reset_intake_encoder();
                        //get cubes to the right pos on the intake
                        set_intake(-127);
                        while (get_left_intake_pos() > -505 && get_right_intake_pos() > -505)
                            pros::delay(5);
                        set_intake(0);
                        //set arm to the right pos
                        resume_arm();
                        set_arm_pid(LOW_TOWER);
                        set_intake_speed(8500);
                        intake = true;
                    }
                    break;
                case 2: //second tower height
                    if (tray_counter == 0)
                    {
                        resume_arm();
                        set_arm_pid(HIGH_TOWER);
                        set_intake_speed(9300);
                    }
                    arm_counter = -1;
                    break; 
                }
            }
        }
        else if (master.get_digital(DIGITAL_R1)&&intake)
        {
            set_intake(127);
            intake_time = 100;
        }
    else if (master.get_digital(DIGITAL_R2)&&intake)
        {
            set_intake(-127);
            intake_time = 100;
        }
        else if (get_arm_pos()< 200 && arm_counter == 0)
        {
            stacking_state();
            intake_time--;
        }   
        else
        {
            set_intake(0);
            intake_time--;
        }
        pros::delay(20);
    }
}

void stacking_state()
{
    suspend_arm();
    set_arm(-12);
    reset_arm_encoder();
    set_intake_speed(12000);
    intake_hold();
    set_intake(10);
}