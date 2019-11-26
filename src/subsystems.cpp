#include "main.h"

int arm_counter = 0;

void tray_outtake()
{
    
    while (get_tray_pos() < 1470)
        set_tray(127);
    while (get_tray_pos() < 1760)
        set_tray(50);
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
    intake_coast();
}

void intake_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    intake_coast();
    while (true)
    {
        if (master.get_digital(DIGITAL_R1))
            set_intake(127); //Intake
        else if (master.get_digital(DIGITAL_R2) && arm_counter == -1)
            set_intake(-85); //Outtake
        else if (master.get_digital(DIGITAL_R2) && arm_counter == 1){
            set_intake(-65);
        } else if (master.get_digital(DIGITAL_R2) && arm_counter == 0){
            set_intake(-127);
        } else
            set_intake(10); //No movement
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


int tray_counter = 0;
pros::Task tray_pid_t(tray_pid, nullptr, "name");
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
            case 0:
            //intake
                tray_pid_t.resume();
                set_tray_pid(TRAY_IN);
                intake_coast();
                break;
            case 1:
            //protected (smaller horizontal space)
                set_tray_pid(PROTECTED);
                break;
            case 2: 
            //score
                tray_pid_t.suspend();
                tray_outtake();
                tray_counter = -1;
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
                case 0:
                    if(tray_counter==0)
                    {
                        //10
                        //arm down
                        set_arm_pid(0);
                        pros::delay(500);
                        set_tray_pid(TRAY_IN);
                    }
                    break;
                case 1:
                    if(tray_counter==0){
                        //first tower height
                        set_tray_pid(PROTECTED-100);
                        set_arm_pid(1117);
                        //1123
                    }
                    break;
                 case 2:
                    if(tray_counter==0){
                        //1700
                        //second tower height
                        set_arm_pid(1437);
                    }
                    arm_counter = -1;
                    break; 
            }
        } else if(tray_counter == 0 && arm_counter <= 0){
            arm_pid_t.suspend();
            set_arm(-25);
        }
        pros::delay(20);
    }
}