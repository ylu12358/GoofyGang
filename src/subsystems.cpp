#include "main.h"

//618 is back
//1100 is protect
//1900 is score
//positive power is score
//negative reset
void tray_outtake()
{
    while (get_tray_pos() < 3500)
        set_tray(-127);
    while (get_tray_pos() < 5200)
        set_tray(-40);
    while (get_tray_pos() < TRAY_OUT)
    {
        set_tray(-20);
        intake_coast();
    }
    set_tray(0);
    
}

void tray_intake()
{
 //   while (!tray_pressed())
        set_tray(127);
    set_tray(0);
    reset_tray_encoder();
    intake_hold();
}

void intake_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    intake_hold();
    while (true)
    {
        if (master.get_digital(DIGITAL_X) && master.get_digital(DIGITAL_R1))
            set_intake(60);
        else if (master.get_digital(DIGITAL_X) && master.get_digital(DIGITAL_R2))
            set_intake(-60);
        else if (master.get_digital(DIGITAL_R1))
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
    while (true)
    {
        set_tank(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_Y));
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
            while (master.get_digital(DIGITAL_L1))
                pros::delay(10);
            switch (counter)
            {
            case 0:
                tray_intake();
                counter++;
                break;

            case 1:
                tray_outtake();
                counter = 0;
                break;
            }
        }
        pros::delay(20);
    }
}

//negative power raises the arm
//no rubber band yet, don't run

void arm_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    int counter = 0;
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
                //tweek this, cause its opposite the other conditions
                    int height1 = 0;
                    while(abs(get_arm_pos()-height1)<10){
                        if(get_arm_pos()>height1){
                            set_arm(-20);
                        } else if(get_arm_pos()<height1){
                            int power = (height1-get_arm_pos())*0.01;
                            if(power>127){
                                power = 127;
                            }
                            set_arm(power);
                        } pros::delay(10);
                    }
                    counter++;
                    break;

                case 1:
                    int height2 = 10;
                    while(abs(get_arm_pos()-height2)<10){
                        if(get_arm_pos()>height2){
                            set_arm(-20);
                        } else if(get_arm_pos()<height2){
                            int power = (height2-get_arm_pos())*0.01;
                            if(power>127){
                                power = 127;
                            }
                            set_arm(power);
                        } pros::delay(10);
                    }
                    counter++;
                    break;

                case 2:
                    int height3 = 20;
                    while(abs(get_arm_pos()-height3)<10){
                        if(get_arm_pos()>height3){
                            set_arm(-20);
                        } else if(get_arm_pos()<height3){
                            int power = (height3-get_arm_pos())*0.01;
                            if(power>127){
                                power = 127;
                            }
                            set_arm(power);
                        } pros::delay(10);
                    }
                    counter++;
                    break;

                case 4:
                    int height4 = 30;
                    while(abs(get_arm_pos()-height4)<10){
                        if(get_arm_pos()>height4){
                            set_arm(-20);
                        } else if(get_arm_pos()<height4){
                            int power = (height4-get_arm_pos())*0.01;
                            if(power>127){
                                power = 127;
                            }
                            set_arm(power);
                        } pros::delay(10);
                    }
                    counter=0;
                    break;
            }
        }
        pros::delay(20);
    }
}