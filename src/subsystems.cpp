#include "main.h"

//618 is back
//1100 is protect
//1900 is score
//positive power is score
//negative reset
void tray_outtake()
{
    while (get_tray_pos() < 1500)
        set_tray(100);
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
            set_tank((-master.get_analog(ANALOG_LEFT_Y)+master.get_analog(ANALOG_RIGHT_X)),(master.get_analog(ANALOG_LEFT_Y)+master.get_analog(ANALOG_RIGHT_X)));
        } else if(tank){
            set_tank(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_Y));
        }
        if(master.get_digital(DIGITAL_DOWN)){
            tank = !tank;
        }
        pros::delay(20);
    }
}

void tray_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    int counter = 0;
    tray_hold();
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
                tray_intake();
                break;
            case 1: 
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
//doesnt work, doesnt grip
void arm_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    pros::Task arm_t(arm_pid, nullptr, "name");
    set_arm_pid(1325);
    int counter = 0;
    arm_hold();
    while(true){
        if(master.get_digital(DIGITAL_A))
        {
            counter++;
            while(master.get_digital(DIGITAL_A))
            {
                pros::delay(10);
            }
            switch(counter)
            {
                case 0:
                //1340
                    master.set_text(0, 0, "ZERO");
                    set_arm_pid(1320);
                    break;
                case 1:
                    master.set_text(0, 0, "ONE");
                    set_arm_pid(2200);
                    break;
                case 2:
                    master.set_text(0, 0, "TWO");
                    set_arm_pid(2500);
                    break;
                case 3:
                //2215
                    master.set_text(0, 0, "THREE");
                    set_arm_pid(3000);
                    counter = -1;
                    break;
            }
        }
        pros::delay(20);
    }
}