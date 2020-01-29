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

void preauton()
{
    normal_chassis();
    suspend_arm();
    set_arm(-50);
    set_intake(-127);
    set_tank(-80, -80);
    set_tray_pid(TRAY_IN);
    pros::delay(300);
    suspend_tray();
    reset_arm_encoder();
    set_arm(-10);
    set_intake(0);
    set_tank(0, 0);
}

void start_driver()
{
    //resets everything
    resume_tray();
    set_tray_pid(TRAY_IN);
    set_tank(0, 0);
    set_intake(12);
    chassisController.stop();
    suspend_tray();
    profileController.flipDisable();
    set_intake_speed(12000);
    normal_chassis();
    set_arm_pid(0);
}

void outtakeBit()
{
    reset_intake_encoder();
    set_intake(-80);
    while (get_left_intake_pos() > -130)
        pros::delay(5);
    set_intake(0);
}

void lowTower()
{
    resume_tray();
    set_intake(0);
    set_tray_pid(TRAY_IN+150);
    intake_hold();
    set_arm(127);
    reset_intake_encoder();
    set_intake(-127);
    while (get_left_intake_pos() > -515 && get_right_intake_pos() > -515)
        pros::delay(5);
    set_intake(0);
    resume_arm();
    set_arm_pid(LOW_TOWER);

    set_intake(-127);
    pros::delay(1000);

    set_arm_pid(0);
    while(get_arm_pos() > 20)
        pros::delay(5);
    suspend_arm();
    set_arm(-30);
    set_tray_pid(TRAY_IN);
    set_intake(127);
    suspend_tray();
}

void Actual_Route(){
    preauton();
    set_intake(100);
    set_arm(-20);
    slow_chassis(4800);

    //purple cube next to tower
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    
    //turn to face purple cube next to 3 stack
    chassisController.turnAngle(10_deg);
    chassisController.waitUntilSettled();

    //intake purple cube next to 3 stack
    profileController.setTarget("A");
    profileController.waitUntilSettled();

    //back up a bit
    profileController.setTarget("C", true);
    profileController.waitUntilSettled();

    //turn to face orange cube in outer protected
    chassisController.turnAngle(-70_deg);
    chassisController.waitUntilSettled();

    //intake orange cube in outer protected
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    
    //face second orange cube in protected
    chassisController.turnAngle(30_deg);
    chassisController.waitUntilSettled();

    //intake second orange cube in protected
    profileController.setTarget("A");
    profileController.waitUntilSettled();

    //face towards scoring zone
    resume_tray();
    chassisController.turnAngle(-70);
    chassisController.waitUntilSettled();

    outtakeBit();
    set_tray_pid(PROTECTED);

    //align with scoring zone
    set_tank(30, 30);
    pros::delay(1500);
    set_tank(0, 0);
    pros::delay(1000);

    //score
    fast_outtake();

    //back away
    resume_tray();
    set_tray_pid(TRAY_IN);
    while(get_tray_pos() > PROTECTED + 580)
        pros::delay(5);
    normal_chassis();
    suspend_tray();
    set_tank(-127, -127);
    set_intake(-127);
    pros::delay(200);

    //reset All
    drive_hold();
    pros::delay(20);
    set_tank(0, 0);
    set_intake(0);
}

void swing_turns(){
    //preauton
    preauton();
    set_intake(-100);
    set_arm(-30);
    slow_chassis(4700);
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    profileController.setTarget("B");
    profileController.waitUntilSettled();
    slow_chassis(12000);
    set_intake(127);
    profileController.setTarget("C");
    profileController.waitUntilSettled();
}

void new_route(){
    preauton();
    set_arm(-30);
    normal_chassis();
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    chassisController.turnAngle(-90_deg);
    chassisController.waitUntilSettled();
    set_intake(127);
    //////////////////////////////////////////////////// choose this if rng
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    resume_tray();
    //////////////////////////////////////////////////// end
    //
    //
    //////////////////////////////////////////////////// start of trying to intake 4 stack
    // slow_chassis(4500);
    // profileController.setTarget("B");
    // profileController.waitUntilSettled();
    // reset_drive_encoder();
    // set_ldrive(100,50);
    // set_rdrive(-100,50);
    // while(get_left_drive_pos()<90&&get_right_drive_pos()>-90){
    //     pros::delay(5);
    // }
    // profileController.setTarget("B", true);
    // profileController.waitUntilSettled();
    // profileController.setTarget("C");
    // profileController.waitUntilSettled();
    //////////////////////////////////////////////////////// end
    outtakeBit();
    set_tray_pid(PROTECTED);

    set_tank(30, 30);
    pros::delay(1500);
    set_tank(0, 0);
    pros::delay(1000);

    //score
    fast_outtake();

    //back away
    resume_tray();
    set_tray_pid(TRAY_IN);
    while(get_tray_pos() > PROTECTED + 580)
        pros::delay(5);
    normal_chassis();
    suspend_tray();
    set_tank(-127, -127);
    set_intake(-127);
    pros::delay(200);

    //reset All
    drive_hold();
    pros::delay(20);
    set_tank(0, 0);
    set_intake(0);
    
}

void one_cube()
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
    resume_tray();
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
    outtakeBit();
    //score
    tray_outtake();

    //resets everything
    profileController.removePath("B");
    profileController.removePath("C");
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
    resume_tray();
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
    outtakeBit();

    //score
    tray_outtake();

    //resets everything
    profileController.removePath("B");
    profileController.removePath("C");
}

void u_6cube(int color)
{
    //preauton
    preauton();

    //intake row
    set_intake(127);
    set_arm(-30);
    slow_chassis(4400);
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    
    chassisController.turnAngleAsync(color * -20_deg);
    chassisController.waitUntilSettled();
    slow_chassis(2400);
    profileController.setTarget("B");
    profileController.waitUntilSettled();
    slow_chassis(4800);


    //turn to score
    resume_tray();
    chassisController.turnAngleAsync(color * 105.35_deg);
    chassisController.waitUntilSettled();
    set_intake(25);
    outtakeBit();
    set_tray_pid(PROTECTED);
    

    //drive forward
    slow_chassis(5300);
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    set_tank(30,30);
    pros::delay(150);
    set_tank(0,0);
    pros::delay(200);

    //score
    fast_outtake();

    //back away
    resume_tray();
    set_tray_pid(TRAY_IN);
    while(get_tray_pos() > PROTECTED + 580)
        pros::delay(5);
    normal_chassis();
    set_tank(-127, -127);
    set_intake(-127);
    pros::delay(300);
    suspend_tray();

    //reset All
    drive_hold();
    pros::delay(20);
    set_tank(0, 0);
    set_intake(0);
    profileController.removePath("A");
    profileController.removePath("B");
}

void proBlue()
{
    //preauton
    preauton();

    set_intake(127);
    set_arm(-30);
    slow_chassis(4700);
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    
    //turn(20);
    chassisController.turnAngleAsync(-20_deg);
    chassisController.waitUntilSettled();

    set_intake(-127);
    pros::delay(1000);

    chassisController.turnAngleAsync(20.65_deg);
    chassisController.waitUntilSettled();
    //turn(-20);

    set_tank(-100,-100);
    pros::delay(500);
    set_tank(-30,-30);
    pros::delay(1200);
    set_tank(0,0);
    pros::delay(600);
    set_intake(127);
    slow_chassis(12000);
    profileController.setTarget("B");
    profileController.waitUntilSettled();
    slow_chassis(4700);
    chassisController.turnAngleAsync(-80_deg);
    chassisController.waitUntilSettled();


    //drive forward
    resume_tray();
    slow_chassis(5100);
    profileController.setTarget("C");
    profileController.waitUntilSettled();
    outtakeBit();
    set_tray_pid(PROTECTED);

    set_tank(30, 30);
    pros::delay(150);
    set_tank(0, 0);
    pros::delay(1000);

    //score
    fast_outtake();

    //back away
    resume_tray();
    set_tray_pid(TRAY_IN);
    while(get_tray_pos() > PROTECTED + 580)
        pros::delay(5);
    normal_chassis();
    set_tank(-127, -127);
    set_intake(-127);
    pros::delay(200);
    suspend_tray();

    //reset All
    drive_hold();
    pros::delay(20);
    set_tank(0, 0);
    set_intake(0);
    profileController.removePath("A");
    profileController.removePath("B");
}

void proRed()
{
    //preauton
    preauton();
    set_intake(-100);
    set_arm(-30);
    slow_chassis(4700);
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    slow_chassis(12000);
    set_intake(127);
    profileController.setTarget("B");
    profileController.waitUntilSettled();
}

void skills1()
{      
    //preauton
    preauton();

    //intake row
    set_intake(127);
    set_arm(-30);
    slow_chassis(4800);
    profileController.setTarget("A");
    profileController.waitUntilSettled();

    //turn towards tower
    chassisController.turnAngleAsync(-20_deg);
    chassisController.waitUntilSettled();
    slow_chassis(2400);

    //intake last cube
    profileController.setTarget("B");
    profileController.waitUntilSettled();
    slow_chassis(4800);

    //move away from tower
    profileController.setTarget("B", true);
    profileController.waitUntilSettled();

    //score low tower
    lowTower();

    //turns toward straight line of cubes
    chassisController.turnAngleAsync(20_deg);
    chassisController.waitUntilSettled();

    // profileController.setTarget("C");
    // profileController.waitUntilSettled();

    // chassisController.turnAngleAsync(40_deg);
    // chassisController.waitUntilSettled();

    // lowTower();

    // chassisController.turnAngleAsync(-30_deg);
    // chassisController.waitUntilSettled();

    // set_intake(25);
    // outtakeBit();
    // set_tray_pid(PROTECTED);
    
    // //drive forward
    // slow_chassis(5100);
    // profileController.setTarget("A");
    // profileController.waitUntilSettled();
    // set_tank(30,30);
    // pros::delay(150);
    // set_tank(0,0);
    // pros::delay(200);

    // //score
    // fast_outtake();

    // //places stack and resets everything
    // resume_tray();
    // set_tray_pid(TRAY_IN);
    // while(get_tray_pos() > PROTECTED + 580)
    //     pros::delay(5);
    // normal_chassis();
    // set_tank(-127, -127);
    // set_intake(-127);
    // pros::delay(200);
    // drive_hold();
    // pros::delay(20);
    // set_tank(0, 0);
    // set_intake(0);
    // profileController.removePath("A");
    // profileController.removePath("B");
    // endAuton();    
}

void skills2()
{
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
    resume_tray();
    chassisController.moveDistanceAsync(-20_in);
    resume_tray();
    set_tray_pid(LOCK_SAFE);
    chassisController.waitUntilSettled();

    //turn (backward) and wall align with row of cube
    chassisController.turnAngleAsync(225_deg);
    set_intake(127);
    chassisController.waitUntilSettled();
    set_tank(-60, -60);
    pros::delay(100);

    //3 cubes straight
    chassisController.moveDistanceAsync(22_in);
    set_tray_pid(TRAY_IN);
    chassisController.waitUntilSettled();

    //outtake a bit, so cube is in intake, not tray
    outtakeBit();

    //turn and tower on center
    chassisController.turnAngleAsync(45_deg);
    set_tray_pid(TRAY_IN+150);
    //arm
    set_arm_pid(HIGH_TOWER);
    chassisController.waitUntilSettled();
    
    //longer distance = greater voltage
    set_intake(-127);
    pros::delay(100);

    //turn
    chassisController.turnAngleAsync(59_deg);
    set_intake(0);
    set_tray_pid(TRAY_IN);
    
    //arm
    set_arm_pid(0);
    chassisController.waitUntilSettled();

    //tower in side tower
    chassisController.moveDistanceAsync(49.5_in);
    
    //outtake a bit, so cube is in intake, not tray
    outtakeBit();
    
    //arm
    set_tray_pid(TRAY_IN+150);
    set_arm_pid(LOW_TOWER);
    chassisController.waitUntilSettled();
    set_intake(-90);
    pros::delay(100);

    //come back with opposite angle (symmetric, lined up with last tower)
    chassisController.turnAngleAsync(-59_deg);
    set_intake(0);
    
    //arm
    set_arm_pid(0);
    set_tray_pid(TRAY_IN);
    chassisController.waitUntilSettled();
    chassisController.moveDistanceAsync(-49.5_in);
    
    //outtake a bit, so cube is in intake, not tray
    outtakeBit();
    
    //arm
    set_tray_pid(TRAY_IN+150);
    set_arm_pid(LOW_TOWER);
    chassisController.waitUntilSettled();

    //turn and tower
    chassisController.turnAngle(14_deg);
    //longer distance = greater voltage
    set_intake(-127);
    pros::delay(100);
}


void test(){
    //reset stack
    normal_chassis();
    set_intake(127);
    pros::delay(1000);
    set_intake(25);
    outtakeBit();
    set_tray_pid(PROTECTED);
    pros::delay(1000);
    fast_outtake();
    resume_tray();
    set_tray_pid(TRAY_IN);
    while (get_tray_pos() > PROTECTED + 580)
        pros::delay(5);
    normal_chassis();
    set_tank(-127, -127);
    set_intake(-127);
    pros::delay(200);
    drive_hold();
    pros::delay(20);
    set_tank(0, 0);
    set_intake(0);

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
            //Don't worry - trial and error
    //test whether cube amount screws pid (less friction from wheel... different weight distribution)
    //test whether initial chassis voltage is 10,000 or not (so distance is accurate with which voltage setting)
            //Don't worry - trial and error
    //test to see whether pid and voltage limitation is removed during driver op
    //test if angle is affected by voltage limiting
            //Don't worry - trial and error
    //test inertia sensor? (velocity * time to determine distance -> pid)
            //not yet