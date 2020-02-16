#include "main.h"

//switch case
int arm_counter = 0;
int tray_counter = 0;
//arcade
bool tank = true;
//antitip
bool safe = false;
int last_tray = TRAY_IN;
//cube lock
int intake_time = 0;
bool intake = true;

void tray_outtake()
{
    while (get_tray_pos() < 1700)
        set_tray(127);
    intake_coast();
    
    while (get_tray_pos() < 2000)
    {
        set_tray(50);
        set_intake(13);
    }
    
    while (get_tray_pos() < 2480)
    {
        set_tray(30);
        set_intake(13);
    }

    while (get_tray_pos() < TRAY_OUT)
    {
        set_intake(-13);
        set_tray(30);
    }
    tray_hold(); //tray doesnt flip forward and knock stack
    set_tray(0);
    set_intake(0);
}

void fast_outtake()
{
    while (get_tray_pos() < 1850)
        set_tray(127);
    intake_coast();

    while (get_tray_pos() < TRAY_OUT - 250)
    {
        set_intake(-13);
        set_tray(40);
    }
    tray_hold(); //tray doesnt flip forward and knock stack
    set_tray(0);
    set_intake(0);
}

void drive_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    drive_coast(); //motor isnt running
    normal_chassis(); //reset drive speed
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
    tray_coast(); // motor isnt running
    last_tray = TRAY_IN;
    pros::delay(100); // allow potentiometer to settle
    while (true)
    {
        if (master.get_digital(DIGITAL_RIGHT)){
            //antitip safe
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
                        //wait for tray pos to reach
                        while(get_tray_pos() > TRAY_IN + 20)
                            pros::delay(5);
                        //disable pid
                        suspend_tray();
                        set_tray(0);
                        tray_coast();
                        intake_hold();
                        //pos to return if antitip
                        last_tray = TRAY_IN;
                        break;
                    case 1: //protected
                        resume_tray();
                        set_tray_pid(PROTECTED);
                        //pos to return if antitip
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
            //wait for tray to get to pos
            while(get_tray_pos() > last_tray + 20)
                pros::delay(5);
            safe = false;
            //disable tray - no break
            suspend_tray();
            set_tray(0);
        } 
        pros::delay(20);
    }
}

void arm_control(void *)
{
    //reset
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
                        resume_tray();
                        set_tray_pid(TRAY_IN);
                        suspend_tray();
                        set_tray(0);
                        //cube = true;
                        set_arm_pid(0);
                        set_intake_speed(12000);
                    }
                    break;
                case 1: //first tower height
                    if (tray_counter == 0)
                    {
                        //stop intake
                        intake = false;
                        resume_tray();
                        //wait for cubes to settle
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
                        while (get_left_intake_pos() > -515 && get_right_intake_pos() > -515)
                            pros::delay(5);
                        set_intake(0);
                        //set arm to the right pos
                        resume_arm();
                        if (master.get_digital(DIGITAL_Y)){
                            set_arm_pid(LOW_DESCORE);
                        } else {
                            set_arm_pid(LOW_TOWER);
                        }
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
            if(arm_counter == 0){
                if(get_arm_pos()<200){
                    stacking_state();
                }
            }
            set_intake(127);
            //reset countdown
            intake_time = 100;
        }
        else if (master.get_digital(DIGITAL_R2)&&intake)
        {
            if(arm_counter == 0){
                if(get_arm_pos()<200){
                    stacking_state();
                }
            }
            set_intake(-127);
            //reset countdown
            intake_time = 100;
        }
        else if (get_arm_pos()< 200 && arm_counter == 0)
        {
            stacking_state();
            set_arm(0);
            arm_hold();
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
    //reset - ready to stack
    suspend_arm();
    set_arm(-20);
    reset_arm_encoder();
    intake_hold();
}