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
    //forward (score)
    set_tank(70, 70);
    pros::delay(700);
    //backward
    set_tank(-70, -70);
    pros::delay(700);
    set_tank(0, 0);
    //deploy
    set_tray_pid(PROTECTED);
    pros::delay(1700);
    set_tray_pid(TRAY_IN);
}

void unproRed1()
{
    //preauton deploy
    suspend_arm();
    set_arm(127);
    suspend_tray();
    set_tray(100);
    pros::delay(300);
    set_arm(-55);
    while (get_tray_pos() < PROTECTED + 100)
        set_tray(127);
    set_tray(0);
    resume_tray();
    set_tray_pid(TRAY_IN);
    //slows down drivetrain, so intake not push cubes
    slow_chassis(5000);
    profileController.setTarget("A");
    pros::delay(100);
    set_intake(127);
    //generate path when theres time
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3_ft, 3_ft, 0_deg}}, "B");
    profileController.waitUntilSettled();
    normal_chassis();
    //curve to second row
    profileController.setTarget("B", true);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3.1_ft, 0_ft, 0_deg}}, "C");
    profileController.waitUntilSettled();
    //wall align
    set_tank(-127, -127);
    pros::delay(600);
    set_tank(0, 0);
    profileController.removePath("B");
    slow_chassis(5000);
    //intake row
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    normal_chassis();

    //remove pid   
    profileController.removePath("A");
    profileController.removePath("C");
    profileController.flipDisable();
    chassisController.stop();

    //score

    // turn(300);
    // profileController.setTarget("C");
    // set_intake(-20);
    // pros::delay(280);
    // //increase time - grip
    // set_intake(20);
    // profileController.waitUntilSettled();
    // set_tank(20, 20);
    // pros::delay(300);
    // tray_outtake();
    // set_tank(-127, -127);
    // pros::delay(1000);
    // set_tank(0, 0);
}

void unproRed2()
{
    //preauton
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
    //grab last cube in row
    chassisController.moveDistance(8_in);
    chassisController.waitUntilSettled();

    //swing turn
    set_tank(-15.0, -78.75);
    pros::delay(1600);

    //score
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
    //preauton deploy
    suspend_arm();
    set_arm(127);
    suspend_tray();
    set_tray(100);
    pros::delay(300);
    set_arm(-55);
    while (get_tray_pos() < PROTECTED + 100)
        set_tray(127);
    set_tray(0);
    resume_tray();
    set_tray_pid(TRAY_IN);
    //slows down drivetrain, so intake not push cubes
    slow_chassis(5000);
    profileController.setTarget("A");
    pros::delay(100);
    set_intake(127);
    //generate path when theres time
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3_ft, -2.3_ft, 0_deg}}, "B");
    profileController.waitUntilSettled();
    normal_chassis();
    //curve to second row
    profileController.setTarget("B", true);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3.1_ft, 0_ft, 0_deg}}, "C");
    profileController.waitUntilSettled();
    //wall align
    set_tank(-127, -127);
    pros::delay(600);
    set_tank(0, 0);
    profileController.removePath("B");
    slow_chassis(5000);
    //intake row
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    normal_chassis();

    //remove pid   
    profileController.removePath("A");
    profileController.removePath("C");
    profileController.flipDisable();
    chassisController.stop();

    //score

    // turn(-300);
    // profileController.setTarget("C");
    // set_intake(-20);
    // pros::delay(280);
    // //increase time - grip
    // set_intake(20);
    // profileController.waitUntilSettled();
    // set_tank(20, 20);
    // pros::delay(300);
    // tray_outtake();
    // set_tank(-127, -127);
    // pros::delay(1000);
    // set_tank(0, 0);
}

void unproBlue2()
{
    //preauton
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
    //grab last cube in row
    chassisController.moveDistance(8_in);
    chassisController.waitUntilSettled();

    //swing turn
    set_tank(-80, -15);
    pros::delay(1600);

    //score
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

void proRed1()
{
    //preauton
    suspend_arm();
    set_arm(127);
    suspend_tray();
    set_tray(100);
    slow_chassis(5000);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{.8_ft, 0_ft, 0_deg}}, "A");
    set_arm(-50);
    while (get_tray_pos() < PROTECTED + 100)
        set_tray(127);
    set_tray(0);
    resume_tray();
    set_tray_pid(TRAY_IN);
    pros::delay(100);

    //off route
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    turn(-70);
    //turn to face 4 stack. Slow chassis to intake, not push, cube
    slow_chassis(2400);
    set_intake(60);
    profileController.setTarget("B");
    //generate path during down time
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3.5_ft, 0_ft, 0_deg}}, "C");
    pros::delay(2000);
    set_intake(127);   
    //intakes cube
    profileController.waitUntilSettled();
    //lifts tray: clear tower
    set_tray_pid(1000);
    slow_chassis(8000);
    //turn towards goal
    turn(-277);
    //drive toward goal
    profileController.setTarget("C");
    profileController.waitUntilSettled();
    //outtake a bit, so the cubes are lower to the ground
    set_intake(-30);
    pros::delay(300);
    //score
    set_tank(35, 35);
    set_intake(20);
    pros::delay(100);
    tray_outtake();
    set_tank(-80, -80);
    pros::delay(800);
    set_tank(0, 0);
    //remove pid
    profileController.removePath("A");
    profileController.removePath("B");
    profileController.removePath("C");
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
    //go backward
    normal_chassis();
    profileController.setTarget("C", true);
    profileController.waitUntilSettled();
    //turn towards wall
    turn(-300);
    //picks up one more cube
    profileController.setTarget("C");
    profileController.waitUntilSettled();

    //turn to face and intake last cube
    turn(270);
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    profileController.removePath("A");
    //drive back from wall
    set_tank(-30,-30);
    set_intake(-10);
    pros::delay(200);
    
    //turn to score
    turn(-270);
    //align an score
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
    slow_chassis(5000);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{.8_ft, 0_ft, 0_deg}}, "A");
    set_arm(-50);
    while (get_tray_pos() < PROTECTED + 100)
        set_tray(127);
    set_tray(0);
    resume_tray();
    set_tray_pid(TRAY_IN);
    pros::delay(100);

    //off route
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    turn(72);
    //turn to face 4 stack. Slow chassis to intake, not push, cube
    slow_chassis(2400);
    set_intake(60);
    profileController.setTarget("B");
    //generate path during down time
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3.5_ft, 0_ft, 0_deg}}, "C");
    pros::delay(1500);
    set_intake(127);   
    //intakes cube
    profileController.waitUntilSettled();
    //lifts tray: clear tower
    set_tray_pid(1000);
    slow_chassis(8000);
    //turn towards goal
    turn(285);
    //drive toward goal
    profileController.setTarget("C");
    profileController.waitUntilSettled();
    //outtake a bit, so the cubes are lower to the ground
    set_intake(-20);
    pros::delay(300);
    //score
    set_tank(20, 20);
    set_intake(20);
    pros::delay(100);
    tray_outtake();
    set_tank(-80, -80);
    pros::delay(800);
    set_tank(0, 0);
    //remove pid
    profileController.removePath("A");
    profileController.removePath("B");
    profileController.removePath("C");
    profileController.flipDisable();
    chassisController.stop();
}

void skills()
{      
}

void newRedPro(){
    //preauton
    suspend_arm();
    set_arm(127);
    suspend_tray();
    set_tray(100);
    set_arm(-50);
    pros::delay(100);
    while (get_tray_pos() < PROTECTED + 100)
        set_tray(127);
    set_tray(0);
    resume_tray();
    set_tray_pid(TRAY_IN);
    pros::delay(100);

    //off route
    chassisController.moveDistance(10_in);
    chassisController.waitUntilSettled();
    chassisController.turnAngle(40);
    chassisController.waitUntilSettled();
    //turn to face 4 stack. Slow chassis to intake, not push, cube
    slow_chassis(9000);
    set_intake(127);
    chassisController.moveDistance(50_in);
    chassisController.waitUntilSettled();
    //generate path during down time
    chassisController.moveDistance(-17_in);
    chassisController.waitUntilSettled();
    chassisController.turnAngle(140);
    chassisController.waitUntilSettled();
    //
    set_tank(127,127);
    pros::delay(100);
    set_tank(0,0);
    pros::delay(100);
    chassisController.moveDistance(46_in);
    chassisController.waitUntilSettled();
    //
    chassisController.moveDistance(-46);
    chassisController.waitUntilSettled();
    chassisController.turnAngle(-45_deg);
    chassisController.waitUntilSettled();
    chassisController.moveDistance(30_in);
    chassisController.waitUntilSettled();
    set_intake(0);
    tray_outtake();
    set_tank(-80, -80);
    pros::delay(800);
    set_tank(0, 0);
    //remove pid
    profileController.flipDisable();
    chassisController.stop();
}
void newRedUnpro(){
    //preauton
    suspend_arm();
    set_arm(127);
    suspend_tray();
    set_tray(100);
    slow_chassis(9000);
    pros::delay(100);
    set_arm(-50);
    while (get_tray_pos() < PROTECTED + 100)
        set_tray(127);
    set_tray(0);
    resume_tray();
    set_tray_pid(TRAY_IN);
    pros::delay(100);
    //straight
    set_intake(127);
    chassisController.moveDistance(54_in);
    chassisController.waitUntilSettled();
    normal_chassis();
    //2nd row
    //chassisController.turnAngle(-26.565_deg);
    //set_tank(-127,-127);
    //pros::delay(100);
    //set_tank(0,0);
    //pros::delay(100);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, 2_ft, 0_deg}}, "A");
    profileController.setTarget("A", true);
    profileController.waitUntilSettled();
    profileController.removePath("A");
    slow_chassis(9000);
    //straight
    chassisController.moveDistance(22_in);
    chassisController.waitUntilSettled();
    normal_chassis();
    //turn
    set_intake(0);
    chassisController.turnAngle(-135_deg);
    chassisController.waitUntilSettled();
    //score
    chassisController.moveDistanceAsync(30_in);
    // set_intake(-20);
    // pros::delay(100);
    chassisController.waitUntilSettled();
    tray_outtake();
    set_tank(-80, -80);
    pros::delay(800);
    set_tank(0, 0);
    //remove pid
    profileController.flipDisable();
    chassisController.stop();
}
void newBluePro(){
    //preauton
    suspend_arm();
    set_arm(127);
    suspend_tray();
    set_tray(100);
    set_arm(-50);
    pros::delay(100);
    while (get_tray_pos() < PROTECTED + 100)
        set_tray(127);
    set_tray(0);
    resume_tray();
    set_tray_pid(TRAY_IN);
    pros::delay(100);

    //off route
    chassisController.moveDistance(10_in);
    chassisController.waitUntilSettled();
    chassisController.turnAngle(40);
    chassisController.waitUntilSettled();
    //turn to face 4 stack. Slow chassis to intake, not push, cube
    slow_chassis(9000);
    set_intake(127);
    chassisController.moveDistance(50_in);
    chassisController.waitUntilSettled();
    //generate path during down time
    chassisController.moveDistance(-17_in);
    chassisController.waitUntilSettled();
    chassisController.turnAngle(140);
    chassisController.waitUntilSettled();
    //
    set_tank(127,127);
    pros::delay(100);
    set_tank(0,0);
    pros::delay(100);
    chassisController.moveDistance(46_in);
    chassisController.waitUntilSettled();
    //
    chassisController.moveDistance(-46);
    chassisController.waitUntilSettled();
    chassisController.turnAngle(-45_deg);
    chassisController.waitUntilSettled();
    chassisController.moveDistance(30_in);
    chassisController.waitUntilSettled();
    set_intake(0);
    tray_outtake();
    set_tank(-80, -80);
    pros::delay(800);
    set_tank(0, 0);
    //remove pid
    profileController.flipDisable();
    chassisController.stop();
}
void newBlueUnpro(){
    //preauton
    suspend_arm();
    set_arm(127);
    suspend_tray();
    set_tray(100);
    slow_chassis(9000);
    pros::delay(100);
    set_arm(-50);
    while (get_tray_pos() < PROTECTED + 100)
        set_tray(127);
    set_tray(0);
    resume_tray();
    set_tray_pid(TRAY_IN);
    pros::delay(100);
    //straight
    set_intake(127);
    chassisController.moveDistance(54_in);
    chassisController.waitUntilSettled();
    normal_chassis();
    //2nd row
    //chassisController.turnAngle(26.565_deg);
    //set_tank(-127,-127);
    //pros::delay(100);
    //set_tank(0,0);
    //pros::delay(100);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, -2_ft, 0_deg}}, "A");
    profileController.setTarget("A", true);
    profileController.waitUntilSettled();
    profileController.removePath("A");
    slow_chassis(9000);
    //straight
    chassisController.moveDistance(22_in);
    chassisController.waitUntilSettled();
    normal_chassis();
    //turn
    set_intake(0);
    chassisController.turnAngle(135_deg);
    chassisController.waitUntilSettled();
    //score
    chassisController.moveDistanceAsync(30_in);
    // set_intake(-20);
    // pros::delay(100);
    chassisController.waitUntilSettled();
    tray_outtake();
    set_tank(-80, -80);
    pros::delay(800);
    set_tank(0, 0);
    //remove pid
    profileController.flipDisable();
    chassisController.stop();

}
void test(){
    chassisController.moveDistance(72_in);
    chassisController.waitUntilSettled();
    
    chassisController.turnAngle(90_deg);
    chassisController.waitUntilSettled();
    
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, 0_ft, 0_deg}}, "A");
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    profileController.removePath("A");
    
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{0_ft, 0_ft, 90_deg}}, "B");
    profileController.setTarget("B");
    profileController.waitUntilSettled();
    profileController.removePath("B");
    
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, -2_ft, 0_deg}}, "C");
    profileController.setTarget("C", true);
    profileController.waitUntilSettled();
    profileController.removePath("C");   
}