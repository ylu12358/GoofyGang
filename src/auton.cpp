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
    set_tray_pid(PROTECTED);
    pros::delay(1700);
    set_tray_pid(TRAY_IN);
}

void unproRed()
{
    //preauton
    preauton();
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

void unproBlue()
{
    //preauton
 preauton();
    //intake row
    set_intake(127);
    set_arm(-30);
    slow_chassis(5000);
    pros::delay(100);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{96_in, 0_in, 0_deg}}, "A");
    profileController.setTarget("A");
    profileController.waitUntilSettled();


        profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{60_in, -96_in, 0_deg}}, "C");
    profileController.setTarget("C", true);
    profileController.waitUntilSettled();
    profileController.removePath("C");   

    // chassisController.waitUntilSettled();
    // //grab last cube in row
    // chassisController.moveDistance(8_in);
    // chassisController.waitUntilSettled();




    // //swing turn
    // set_tank(-80, -15);
    // pros::delay(1600);

    // //score
    // intake_relative(-400, 180);
    // set_tray_pid(PROTECTED);
    // chassisController.moveDistance(43_in);
    // set_tank(20, 20);
    // pros::delay(400);
    // tray_outtake();

    // //resets everything
    // set_tank(-80, -80);
    // pros::delay(500);
    // set_tray_pid(TRAY_IN);
    // set_tank(0, 0);
    chassisController.stop();
}

void proRed()
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

void proBlue()
{
    //preauton
    normal_chassis();
    suspend_arm();
    set_arm(-50);
    set_intake(-127);
    set_tray_pid(TRAY_IN);
    pros::delay(100);
    set_arm(-10);

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
    //preauton

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

    normal_chassis();
    suspend_arm();
    set_arm(-50);
    set_intake(-127);
    set_tray_pid(TRAY_IN);
    pros::delay(100);
    set_arm(-10);

    //1 cube in tower
    set_intake(127);
    chassisController.moveDistance(43_in);
    chassisController.waitUntilSettled();
        //outtake a bit, so cube is in intake, not tray
            set_intake(-20);
            pros::delay(100);
            set_intake(0);
        //arm
            resume_arm();
            set_tray_pid(PROTECTED - 100);
            set_arm_pid(1180);
    set_intake(-90);
    pros::delay(100);

    //come back and wall align
    set_tank(-60,-60);
    set_intake(127);
        //arm
            set_arm_pid(0);
            pros::delay(500);
            set_tray_pid(TRAY_IN);


    //8 cubes straight
    chassisController.moveDistanceAsync(120_in);
        //disable arm
        suspend_arm();
        set_arm(-55);
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
    set_tray_pid(TRAY_IN);
    chassisController.waitUntilSettled();
    
    //turn (backward) and wall align with row of cube
    chassisController.turnAngleAsync(225_deg);
    set_intake(127);
    chassisController.waitUntilSettled();
    set_tank(-60,-60);
    pros::delay(100);

    //3 cubes straight
    chassisController.moveDistance(22_in);
    chassisController.waitUntilSettled();
        //outtake a bit, so cube is in intake, not tray
            set_intake(-20);
            pros::delay(100);
            set_intake(0);

    //turn and tower on center
    chassisController.turnAngleAsync(45_deg);
        //arm
            resume_arm();
            set_tray_pid(PROTECTED - 100);
            set_arm_pid(1180);
    chassisController.waitUntilSettled();
        //longer distance = greater voltage
        set_intake(-127);
        pros::delay(100);

    //turn
    chassisController.turnAngleAsync(59_deg);
    set_intake(0);
        //arm
        set_arm_pid(0);
        pros::delay(500);
        set_tray_pid(TRAY_IN);
    chassisController.waitUntilSettled();

    //tower in side tower
    chassisController.moveDistanceAsync(49.5_in);
        //outtake a bit, so cube is in intake, not tray
            set_intake(-20);
            pros::delay(100);
            set_intake(0);
        //arm
            set_tray_pid(PROTECTED - 100);
            set_arm_pid(1180);
    chassisController.waitUntilSettled();
    set_intake(-90);
    pros::delay(100);

    //come back with opposite angle (symmetric, lined up with last tower)
    chassisController.turnAngleAsync(-59_deg);
    set_intake(0);
        //arm
        set_arm_pid(0);
        pros::delay(500);
        set_tray_pid(TRAY_IN);
    chassisController.waitUntilSettled();
    chassisController.moveDistanceAsync(-49.5_in);
            //outtake a bit, so cube is in intake, not tray
            set_intake(-20);
            pros::delay(100);
            set_intake(0);
        //arm
            set_tray_pid(PROTECTED - 100);
            set_arm_pid(1180);
    chassisController.waitUntilSettled();

    //turn and tower
    chassisController.turnAngle(14_deg);
        //longer distance = greater voltage
        set_intake(-127);
        pros::delay(100);
}

void test(){
    //straight
    normal_chassis();
// //    drivepid(5500);
//     chassisController.moveDistance(54_in);
//     chassisController.waitUntilSettled();

    // //turn
    // slow_chassis(5000);
    // chassisController.turnAngle(90_deg);
    // chassisController.waitUntilSettled();
    
 //   pros::delay(500);
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
    
    //s curve
    // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{30_in, -48_in, 0_deg}}, "C");
    // profileController.setTarget("C", true);
    // profileController.waitUntilSettled();
    // profileController.removePath("C");   
}
    //test whether long distance screws pid
    //test whether cube amount screws pid (less friction from wheel... different weight distribution)
    //test whether initial chassis voltage is 10,000 or not (so distance is accurate with which voltage setting)
    //test to see whether pid and voltage limitation is removed during driver op
    //test if angle is affected by voltage limiting

    //test inertia sensor? (velocity * time to determine distance -> pid)