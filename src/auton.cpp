#include "main.h"

void turn(int target)
{
    //Set parameters
    drive_hold();

    //Const Ints
    int thresh = 1;
    float kp = 0.4;
    int l_first = get_left_drive_pos();
    int r_first = get_right_drive_pos();

    //Ints
    int l_error = target - (get_left_drive_pos() - l_first);
    int r_error = -target - (get_right_drive_pos() - r_first);

    while (abs(l_error) > thresh && abs(r_error) > thresh)
    {
        //Recalculate error in loop
        l_error = target - (get_left_drive_pos() - l_first);
        r_error = -target - (get_right_drive_pos() - r_first);

        //Set motors to error*kp (p controller)
        set_slow_tank((l_error * kp) + (sgn(l_error) + 10), (r_error * kp) + (sgn(r_error) + 10));

        pros::delay(10);
    }
    set_tank(0, 0);

    //Give time for the braketype to initiate
    pros::delay(250);
}

void oneCube()
{
    set_tank(70, 70);
    pros::delay(700);
    set_tank(-70, -70);
    pros::delay(700);
    set_tank(0, 0);
    set_tray_pid(PROTECTED);
    pros::delay(1700);
    set_tray_pid(TRAY_IN);
}

void unproRed1()
{
    suspend_arm();
    set_arm(127);
    suspend_tray();
    set_tray(100);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{5_ft, 0_ft, 0_deg}}, "A");
    set_arm(-55);
    while (get_tray_pos() < PROTECTED + 100)
        set_tray(127);
    set_tray(0);
    resume_tray();
    set_tray_pid(TRAY_IN);
    slow_chassis(5000);
    profileController.setTarget("A");
    pros::delay(100);
    set_intake(127);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3_ft, 3_ft, 0_deg}}, "B");
    profileController.waitUntilSettled();
    normal_chassis();
    profileController.setTarget("B", true);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3.1_ft, 0_ft, 0_deg}}, "C");
    profileController.waitUntilSettled();
    set_tank(-127, -127);
    pros::delay(600);
    set_tank(0, 0);
    profileController.removePath("B");
    slow_chassis(5000);
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    normal_chassis();
    turn(300);
    profileController.setTarget("C");
    set_intake(-20);
    pros::delay(280);
    //increase time - grip
    set_intake(20);
    profileController.waitUntilSettled();
    set_tank(20, 20);
    pros::delay(300);
    tray_outtake();
    set_tank(-127, -127);
    pros::delay(1000);
    set_tank(0, 0);
}

void unproRed2()
{
    drive_hold();

    set_tank(127, 127);
    pros::delay(230);
    set_tank(-70, -70);
    set_tray_pid(PROTECTED);
    pros::delay(300);
    set_tray_pid(TRAY_IN);

    //intake row
    set_intake(127);
    set_arm(-30);
    pros::delay(100);
    chassisController.moveDistance(44_in);
    chassisController.waitUntilSettled();
    chassisController.moveDistance(8_in);
    chassisController.waitUntilSettled();

    //swing turn
    set_tank(-15.0, -78.75);
    pros::delay(1600);

    //outtake
    intake_relative(-400, 180);
    set_tray_pid(PROTECTED);
    chassisController.moveDistance(43_in);
    set_tank(20, 20);
    pros::delay(400);
    tray_outtake();

    //resets everything
    set_tank(-80, -80);
    pros::delay(500);
    set_tray_pid(TRAY_IN);
    set_tank(0, 0);
    chassisController.stop();
}

void unproBlue1()
{
    suspend_arm();
    set_arm(127);
    suspend_tray();
    set_tray(100);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{5_ft, 0_ft, 0_deg}}, "A");
    set_arm(-55);
    while (get_tray_pos() < PROTECTED + 100)
        set_tray(127);
    set_tray(0);
    resume_tray();
    set_tray_pid(TRAY_IN);
    slow_chassis(5000);
    profileController.setTarget("A");
    pros::delay(100);
    set_intake(127);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3_ft, -3_ft, 0_deg}}, "B");
    profileController.waitUntilSettled();
    normal_chassis();
    profileController.setTarget("B", true);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3.1_ft, 0_ft, 0_deg}}, "C");
    profileController.waitUntilSettled();
    set_tank(-127, -127);
    pros::delay(600);
    set_tank(0, 0);
    profileController.removePath("B");
    slow_chassis(5000);
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    normal_chassis();
    turn(-300);
    profileController.setTarget("C");
    set_intake(-20);
    pros::delay(280);
    //increase time - grip
    set_intake(20);
    profileController.waitUntilSettled();
    set_tank(20, 20);
    pros::delay(300);
    tray_outtake();
    set_tank(-127, -127);
    pros::delay(1000);
    set_tank(0, 0);
}

void unproBlue2()
{
    drive_hold();
    /* preauton
    set_tank(127,127);
    pros::delay(100);
    set_tank(-70,-70);
    set_tray_pid(PROTECTED);
    pros::delay(200);
    set_tray_pid(TRAY_IN);
*/
    //intake row
    set_intake(127);
    set_arm(-20);
    pros::delay(100);
    chassisController.moveDistance(44_in);
    chassisController.waitUntilSettled();
    chassisController.moveDistance(8_in);
    chassisController.waitUntilSettled();

    //swing turn
    set_tank(-80, -15);
    pros::delay(1600);

    //outtake
    intake_relative(-400, 180);
    set_tray_pid(PROTECTED);
    chassisController.moveDistance(44_in);
    tray_outtake();

    //resets everything
    set_tank(-80, -80);
    pros::delay(500);
    set_tray_pid(TRAY_IN);
    set_tank(0, 0);
    chassisController.stop();
}

void proRed1()
{
    //preauton
    suspend_arm();
    set_arm(127);
    suspend_tray();
    set_tray(100);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{0.7_ft, 0_ft, 0_deg}}, "A");
    set_arm(-50);
    while (get_tray_pos() < PROTECTED + 100)
        set_tray(127);
    set_tray(0);
    resume_tray();
    set_tray_pid(TRAY_IN);
    pros::delay(100);

    //off route
    set_intake(127);
    profileController.setTarget("A");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{10.4_ft, 0_ft, 0_deg}}, "B");
    profileController.waitUntilSettled();
    turn(-60);
    //turn to face 4 stack, hopefully intake cube next to tower
    slow_chassis(2400);
    profileController.setTarget("B");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3.5_ft, 0_ft, 0_deg}}, "C");    
    profileController.waitUntilSettled();
    set_tray_pid(1000);
    normal_chassis();
    //turn towards wall
    turn(-285);
    //picks up one more cube
    profileController.setTarget("C");
    profileController.waitUntilSettled();

    set_intake(-20);
    pros::delay(300);

    //turn to face and drive to score zone
    set_tank(20, 20);
    set_intake(20);
    pros::delay(100);
    tray_outtake();
    set_tank(-127, -127);
    pros::delay(800);
    set_tank(0, 0);
    //remove pid
    profileController.flipDisable();
    chassisController.stop();
}

void proRed2()
{
    //preauton
    suspend_arm();
    set_arm(127);
    suspend_tray();
    set_tray(100);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{2_ft, 0_ft, 0_deg}}, "A");
    set_arm(-55);
    while (get_tray_pos() < PROTECTED + 100)
        set_tray(127);
    set_tray(0);
    resume_tray();
    set_tray_pid(TRAY_IN);
    pros::delay(100);

    //off route
    set_intake(127);
    profileController.setTarget("A");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{10_ft, 0_ft, 0_deg}}, "B");
    profileController.waitUntilSettled();
    turn(-80);
    //turn to face 4 stack, hopefully intake cube next to tower
    slow_chassis(2000);
    profileController.setTarget("B");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{1.8_ft, 0_ft, 0_deg}}, "C");    
    profileController.waitUntilSettled();
    normal_chassis();
    profileController.setTarget("C", true);
    profileController.waitUntilSettled();

    //turn towards wall
    turn(-300);
    //picks up one more cube
    profileController.setTarget("C");
    profileController.waitUntilSettled();

    //turn to face and drive to score zone
    turn(270);
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    profileController.removePath("A");

    set_tank(-30,-30);
    set_intake(-10);
    //align with zone
    pros::delay(200);
    
    turn(-270);
    set_tank(20, 20);
    set_intake(20);
    pros::delay(200);
    tray_outtake();
    set_tank(-127, -127);
    pros::delay(1000);
    set_tank(0, 0);
    //remove pid
    profileController.flipDisable();
    chassisController.stop();
}


void proBlue()
{
    //preauton
    suspend_arm();
    set_arm(127);
    suspend_tray();
    set_tray(100);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{0.7_ft, 0_ft, 0_deg}}, "A");
    set_arm(-55);
    while (get_tray_pos() < PROTECTED + 100)
        set_tray(127);
    set_tray(0);
    resume_tray();
    set_tray_pid(TRAY_IN);
    pros::delay(100);

    //off route
    set_intake(127);
    profileController.setTarget("A");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{10.4_ft, 0_ft, 0_deg}}, "B");
    profileController.waitUntilSettled();
    turn(50);
    //turn to face 4 stack, hopefully intake cube next to tower
    slow_chassis(2400);
    profileController.setTarget("B");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3.5_ft, 0_ft, 0_deg}}, "C");    
    profileController.waitUntilSettled();
    set_tray_pid(1000);
    normal_chassis();
    //turn towards wall
    turn(285);
    //picks up one more cube
    profileController.setTarget("C");
    profileController.waitUntilSettled();

    //turn to face and drive to score zone
    set_tank(20, 20);
    set_intake(20);
    pros::delay(200);
    tray_outtake();
    set_tank(-127, -127);
    pros::delay(800);
    set_tank(0, 0);
    //remove pid
    profileController.flipDisable();
    chassisController.stop();
}

void skills()
{      
}