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

void preauton(){
    normal_chassis();
    suspend_arm();
    set_arm(-50);
    set_intake(-127);
    set_tray_pid(TRAY_IN);
    pros::delay(100);
    set_arm(-10);
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
    preauton();
}

void unproRed()
{
    //preauton
    preauton();

    //intake row
    set_intake(127);
    set_arm(-30);
    slow_chassis(9000);
    pros::delay(100);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{28_in, 0_in, 0_deg}}, "A");
    profileController.setTarget("A");
    profileController.waitUntilSettled();

    //s-curve to 2nd row
    normal_chassis();
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{31_in, -28_in, 0_deg}}, "B");
    profileController.setTarget("B", true);
    set_tray_pid(LOCK_SAFE);
    set_intake(25);
    profileController.waitUntilSettled();

    //intake row
    slow_chassis(9000);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{51_in, 0_in, 0_deg}}, "C");
    set_intake(127);
    profileController.setTarget("C");
    set_tray_pid(TRAY_IN);
    profileController.waitUntilSettled();

    //turn to score
    chassisController.turnAngleAsync(13.25_deg);
    set_intake(25);
    set_tray_pid(PROTECTED);
    chassisController.waitUntilSettled();

    //drive forward
    normal_chassis();
    profileController.setTarget("C");
    profileController.waitUntilSettled();
    set_tank(30,30);
    pros::delay(150);
    set_tank(0,0);

    //outtake a bit
    reset_intake_encoder();
    set_intake(-127);
    while (get_left_intake_pos() > -515)
    {
        pros::delay(5);
    }
    set_intake(0);

    //score
    tray_outtake();

    //resets everything
    intake_rpm(200);
    drive_rpm(200);
    pros::delay(500);
    set_tray_pid(TRAY_IN);
    set_tank(0, 0);
    set_intake(0);
    chassisController.stop();
    profileController.removePath("A");
    profileController.removePath("B");
    profileController.removePath("C");
    profileController.flipDisable();
    set_intake_speed(12000);
    normal_chassis();
}

void unproBlue()
{
    //preauton
    preauton();

    //intake row
    set_intake(127);
    set_arm(-30);
    slow_chassis(9000);
    pros::delay(100);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{28_in, 0_in, 0_deg}}, "A");
    profileController.setTarget("A");
    profileController.waitUntilSettled();

    //s-curve to 2nd row
    normal_chassis();
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{31_in, -28_in, 0_deg}}, "B");
    profileController.setTarget("B", true);
    set_tray_pid(LOCK_SAFE);
    set_intake(25);
    profileController.waitUntilSettled();

    //intake row
    slow_chassis(9000);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{51_in, 0_in, 0_deg}}, "C");
    set_intake(127);
    profileController.setTarget("C");
    set_tray_pid(TRAY_IN);
    profileController.waitUntilSettled();

    //turn to score
    chassisController.turnAngleAsync(13.25_deg);
    set_intake(25);
    set_tray_pid(PROTECTED);
    chassisController.waitUntilSettled();

    //drive forward
    normal_chassis();
    profileController.setTarget("C");
    profileController.waitUntilSettled();
    set_tank(30,30);
    pros::delay(150);
    set_tank(0,0);

    //outtake a bit
    reset_intake_encoder();
    set_intake(-127);
    while (get_left_intake_pos() > -515)
    {
        pros::delay(5);
    }
    set_intake(0);

    //score
    tray_outtake();

    //resets everything
    intake_rpm(200);
    drive_rpm(200);
    pros::delay(500);
    set_tray_pid(TRAY_IN);
    set_tank(0, 0);
    set_intake(0);
    chassisController.stop();
    profileController.removePath("A");
    profileController.removePath("B");
    profileController.removePath("C");
    profileController.flipDisable();
    set_intake_speed(12000);
    normal_chassis();
}

void shortUnRed(){
    //preauton
    preauton();

    //intake row
    set_intake(127);
    set_arm(-30);
    slow_chassis(9000);
    pros::delay(100);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{51_in, 0_in, 0_deg}}, "A");
    set_intake(127);
    profileController.setTarget("A");
    profileController.waitUntilSettled();

    //turn to score
    chassisController.turnAngleAsync(13.25_deg);
    set_intake(25);
    set_tray_pid(PROTECTED);
    chassisController.waitUntilSettled();

    //drive forward
    normal_chassis();
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    set_tank(30,30);
    pros::delay(150);
    set_tank(0,0);

    //outtake a bit
    reset_intake_encoder();
    set_intake(-127);
    while (get_left_intake_pos() > -515)
    {
        pros::delay(5);
    }
    set_intake(0);

    //score
    tray_outtake();

    //resets everything
    intake_rpm(200);
    drive_rpm(200);
    pros::delay(500);
    set_tray_pid(TRAY_IN);
    set_tank(0, 0);
    set_intake(0);
    chassisController.stop();
    profileController.removePath("A");
    profileController.flipDisable();
    set_intake_speed(12000);
    normal_chassis();
}

void shortUnBlue(){
    //preauton
    preauton();

    //intake row
    set_intake(127);
    set_arm(-30);
    slow_chassis(9000);
    pros::delay(100);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{51_in, 0_in, 0_deg}}, "A");
    set_intake(127);
    profileController.setTarget("A");
    profileController.waitUntilSettled();

    //turn to score
    chassisController.turnAngleAsync(13.25_deg);
    set_intake(25);
    set_tray_pid(PROTECTED);
    chassisController.waitUntilSettled();

    //drive forward
    normal_chassis();
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    set_tank(30,30);
    pros::delay(150);
    set_tank(0,0);

    //outtake a bit
    reset_intake_encoder();
    set_intake(-127);
    while (get_left_intake_pos() > -515)
    {
        pros::delay(5);
    }
    set_intake(0);

    //score
    tray_outtake();

    //resets everything
    intake_rpm(200);
    drive_rpm(200);
    pros::delay(500);
    set_tray_pid(TRAY_IN);
    set_tank(0, 0);
    set_intake(0);
    chassisController.stop();
    profileController.removePath("A");
    profileController.flipDisable();
    set_intake_speed(12000);
    normal_chassis();
}

void proRed()
{
    //preauton
    preauton();
    normal_chassis();
    
    //grab to remove cube
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{24_in, 0_in, 0_deg}}, "A");
    set_intake(127);
    profileController.setTarget("A");
    profileController.waitUntilSettled();

    //eject cube
    chassisController.turnAngle(45_deg);
    chassisController.waitUntilSettled();
    set_intake(-127);
    chassisController.turnAngle(-45_deg);
    chassisController.waitUntilSettled();

    //intake 4 stack
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{51_in, 0_in, 0_deg}}, "B");
    set_intake(127);
    profileController.setTarget("B");
    profileController.waitUntilSettled();

    //turn to score
    chassisController.turnAngleAsync(45_deg);
    set_tray_pid(PROTECTED);
    chassisController.waitUntilSettled();

    //drive forward
    normal_chassis();
    profileController.setTarget("B");
    profileController.waitUntilSettled();
    set_intake(25);
    set_tank(30,30);
    pros::delay(150);
    set_tank(0,0);

    //outtake a bit
    reset_intake_encoder();
    set_intake(-127);
    while (get_left_intake_pos() > -515)
    {
        pros::delay(5);
    }
    set_intake(0);

    //score
    tray_outtake();

    //resets everything
    intake_rpm(200);
    drive_rpm(200);
    pros::delay(500);
    set_tray_pid(TRAY_IN);
    set_tank(0, 0);
    set_intake(0);
    chassisController.stop();
    profileController.removePath("A");
    profileController.removePath("B");
    profileController.flipDisable();
    set_intake_speed(12000);
    normal_chassis();
}

void proBlue()
{
    //preauton
    preauton();
    normal_chassis();
    
    //grab to remove cube
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{24_in, 0_in, 0_deg}}, "A");
    set_intake(127);
    profileController.setTarget("A");
    profileController.waitUntilSettled();

    //eject cube
    chassisController.turnAngle(45_deg);
    chassisController.waitUntilSettled();
    set_intake(-127);
    chassisController.turnAngle(-45_deg);
    chassisController.waitUntilSettled();

    //intake 4 stack
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{51_in, 0_in, 0_deg}}, "B");
    set_intake(127);
    profileController.setTarget("B");
    profileController.waitUntilSettled();

    //turn to score
    chassisController.turnAngleAsync(45_deg);
    set_tray_pid(PROTECTED);
    chassisController.waitUntilSettled();

    //drive forward
    normal_chassis();
    profileController.setTarget("B");
    profileController.waitUntilSettled();
    set_intake(25);
    set_tank(30,30);
    pros::delay(150);
    set_tank(0,0);

    //outtake a bit
    reset_intake_encoder();
    set_intake(-127);
    while (get_left_intake_pos() > -515)
    {
        pros::delay(5);
    }
    set_intake(0);

    //score
    tray_outtake();

    //resets everything
    intake_rpm(200);
    drive_rpm(200);
    pros::delay(500);
    set_tray_pid(TRAY_IN);
    set_tank(0, 0);
    set_intake(0);
    chassisController.stop();
    profileController.removePath("A");
    profileController.removePath("B");
    profileController.flipDisable();
    set_intake_speed(12000);
    normal_chassis();
}

void skills()
{      
    //preauton
    preauton();

    //maybe drive forward
    
        // set_tank(40,40);
        // pros::delay(100);
        // set_tank(-40,-40);
        // pros::delay(100);
        
        // chassisController.moveDistance(12_in);
        // chassisController.waitUntilSettled();
        // chassisController.moveDistance(-12_in);
        // chassisController.waitUntilSettled();
    // set_tank(100,100);
    // pros::delay(100);
    // set_tank(-100,-100);


    //1 cube in tower
    set_intake(127);
    chassisController.moveDistance(43_in);
    chassisController.waitUntilSettled();
        //outtake a bit, so cube is in intake, not tray
            reset_intake_encoder();
            set_intake(-127);
            while (get_left_intake_pos() > -515)
            {
                pros::delay(5);
            }
            set_intake(0);
        //arm
            set_arm_pid(LOW_TOWER);
    set_intake(-90);
    pros::delay(100);

    //come back and wall align
    set_tray_pid(LOCK_SAFE);
    set_tank(-60,-60);
    set_intake(127);
        //arm
            set_arm_pid(0);

    //8 cubes straight
    chassisController.moveDistanceAsync(120_in);
        //disable arm
        suspend_arm();
        set_arm(-30);
        reset_arm_encoder();
    chassisController.waitUntilSettled();

    //turn and score
    chassisController.turnAngle(-45_deg);
    chassisController.waitUntilSettled();
    chassisController.moveDistance(20_in);
    chassisController.waitUntilSettled();
    set_intake(0);
    suspend_tray();
    tray_outtake();

    //come back
    chassisController.moveDistanceAsync(-20_in);
    resume_tray();
    set_tray_pid(LOCK_SAFE);
    chassisController.waitUntilSettled();
    
    //turn (backward) and wall align with row of cube
    chassisController.turnAngleAsync(225_deg);
    set_intake(127);
    chassisController.waitUntilSettled();
    set_tank(-60,-60);
    pros::delay(100);

    //3 cubes straight
    chassisController.moveDistanceAsync(22_in);
    set_tray_pid(TRAY_IN);
    chassisController.waitUntilSettled();
        //outtake a bit, so cube is in intake, not tray
            reset_intake_encoder();
            set_intake(-127);
            while (get_left_intake_pos() > -515)
            {
                pros::delay(5);
            }
            set_intake(0);

    //turn and tower on center
    chassisController.turnAngleAsync(45_deg);
        //arm
            set_arm_pid(HIGH_TOWER);
    chassisController.waitUntilSettled();
        //longer distance = greater voltage
        set_intake(-127);
        pros::delay(100);

    //turn
    chassisController.turnAngleAsync(59_deg);
    set_intake(0);
        //arm
        set_arm_pid(0);
    chassisController.waitUntilSettled();

    //tower in side tower
    chassisController.moveDistanceAsync(49.5_in);
        //outtake a bit, so cube is in intake, not tray
            reset_intake_encoder();
            set_intake(-127);
            while (get_left_intake_pos() > -515)
            {
                pros::delay(5);
            }
            set_intake(0);
        //arm
            set_arm_pid(LOW_TOWER);
    chassisController.waitUntilSettled();
    set_intake(-90);
    pros::delay(100);

    //come back with opposite angle (symmetric, lined up with last tower)
    chassisController.turnAngleAsync(-59_deg);
    set_intake(0);
        //arm
        set_arm_pid(0);
    chassisController.waitUntilSettled();
    chassisController.moveDistanceAsync(-49.5_in);
        //outtake a bit, so cube is in intake, not tray
            reset_intake_encoder();
            set_intake(-127);
            while (get_left_intake_pos() > -515)
            {
                pros::delay(5);
            }
            set_intake(0);
        //arm
        set_arm_pid(LOW_TOWER);
    chassisController.waitUntilSettled();

    //turn and tower
    chassisController.turnAngle(14_deg);
        //longer distance = greater voltage
        set_intake(-127);
        pros::delay(100);
}








void test(){
    normal_chassis();
//    //straight
//     drivepid(5500);
//     chassisController.moveDistance(54_in);
//     chassisController.waitUntilSettled();

    // //turn
    // slow_chassis(5000);
    // chassisController.turnAngle(90_deg);
    // chassisController.waitUntilSettled();
    
    // //straight
    // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{48_in, 0_ft, 0_deg}}, "A");
    // profileController.setTarget("A");
    // profileController.waitUntilSettled();
    // profileController.removePath("A");
    
    // //turn
    // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{0_ft, 0_ft, 90_deg}}, "B");
    // profileController.setTarget("B");
    // profileController.waitUntilSettled();
    // profileController.removePath("B");
    
    // //s curve
    // //34, 18
    // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{52_in, -28_in, 0_deg}}, "C");
    // profileController.setTarget("C", true);
    // profileController.waitUntilSettled();
    // profileController.removePath("C");   
}
    //test whether long distance screws pid
            //screw this - trial and error
    //test whether cube amount screws pid (less friction from wheel... different weight distribution)
    //test whether initial chassis voltage is 10,000 or not (so distance is accurate with which voltage setting)
            //screw this - trial and error
    //test to see whether pid and voltage limitation is removed during driver op
    //test if angle is affected by voltage limiting
            //screw this - trial and error
    //test inertia sensor? (velocity * time to determine distance -> pid)
            //not yet