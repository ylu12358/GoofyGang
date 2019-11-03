#include "main.h"

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
    while (!tray_pressed())
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