#include "main.h"

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

void unproRed()
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

void unproBlue()
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

void protectedTime()
{

    drive_hold();
    // preauton
    set_tank(127, 127);
    pros::delay(330);
    set_tank(-70, -70);
    set_intake(0);
    set_tray_pid(PROTECTED);
    set_arm(-20);
    pros::delay(400);
    set_tank(-10, -10);
    pros::delay(1000);
    set_tray_pid(TRAY_IN);

    //intake row
    set_intake(90);
    set_tank(40, 40);
    pros::delay(1500);

    //point turn
    set_tank(-40, 40);
    pros::delay(1400);

    //row
    set_tank(40, 40);
    pros::delay(1000);

    //turn
    /*    set_tank(-40,40);
    pros::delay(600);
    intake_relative(-400,180);
*/
    //score
    set_tank(40, 40);
    pros::delay(900);

    //turn
    /*
    set_tank(-40,40);

    pros::delay(750);*/
    //drive
    set_tank(20, 20);
    //intake_relative(-400,180);
    set_intake(0);
    set_tray_pid(PROTECTED);

    pros::delay(4000);
    set_tank(0, 0);
    pros::delay(100);
    tray_outtake();

    //resets everything
    set_tank(-80, -80);
    pros::delay(500);
    set_tray_pid(TRAY_IN);
    set_tank(0, 0);
}

void skillsTime()
{
    drive_hold();
    //
    set_tank(127, 127);
    pros::delay(230);
    set_tank(-70, -70);
    set_tray_pid(PROTECTED);
    pros::delay(300);
    set_tray_pid(TRAY_IN);
    //

    //intake row
    set_intake(127);
    set_arm(-20);

    set_tank(25.3, 25.0);
    pros::delay(16000);
    /*    set_tank(0,20);
    pros::delay(100);
    set_tank(30,30);
    pros::delay(100);
    set_tank(20,0);
    pros::delay(100);
    set_tank(50,50);
    pros::delay(2000);
    */
    //remove momentum
    set_tank(-20, -20);
    pros::delay(1000);
    //point turn
    set_tank(40, -40);
    set_tray_pid(PROTECTED);
    pros::delay(1700);

    //drive to score
    set_tank(30, 30);
    set_intake(0);
    pros::delay(5000);
    set_tank(20, 0);
    intake_relative(-250, 180);
    pros::delay(1000);
    tray_outtake();

    //resets everything
    set_tank(-80, -80);
    pros::delay(500);
    set_tray_pid(TRAY_IN);
    set_tank(0, 0);
}