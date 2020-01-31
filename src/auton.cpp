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
    //normal speed limit
    normal_chassis();
    //set constant on arm for cube intake
    suspend_arm();
    set_arm(-50);
    //deploy
    set_intake(-127);
    //wall align
    set_tank(-80, -80);
    //reset tray
    set_tray_pid(TRAY_IN);
    pros::delay(300);
    //remove tray pid - doesnt break tray
    suspend_tray(); 
    tray_coast();
    set_tray(0);
    //reset
    reset_arm_encoder();
    set_arm(-10);
    set_intake(0);
    set_tank(0, 0);
}

void start_driver()
{
    //resets tray pid
    resume_tray();
    set_tray_pid(TRAY_IN);
    //reset drive
    set_tank(0, 0);
    //reset intake
    set_intake(12);
    //suspend drive pid
    chassisController.stop();
    //suspend tray pid
    suspend_tray(); 
    tray_coast(); 
    set_tray(0);
    //suspend drive pid
    profileController.flipDisable();
    //reset speed limit
    set_intake_speed(12000);
    normal_chassis();
    //reset arm
    set_arm_pid(0);
}

void outtakeBit()
{
    //outtake to correct position
    reset_intake_encoder();
    set_intake(-80);
    while (get_left_intake_pos() > -140)
        pros::delay(5);
    set_intake(0);
}

void lowTower()
{
    //resume tray pid
    resume_tray();
    //raise arm
    set_intake(0);
    set_tray_pid(TRAY_IN+150);
    intake_hold();
    set_arm(127);
    reset_intake_encoder();
    //outtake to correct position
    set_intake(-127);
    while (get_left_intake_pos() > -515 && get_right_intake_pos() > -515)
        pros::delay(5);
    set_intake(0);
    //correct arm pos
    resume_arm();
    set_arm_pid(LOW_TOWER);
    //outtake
    set_intake(-127);
    pros::delay(1000);
    //disable pid
    set_arm_pid(0);
    while(get_arm_pos() > 20)
        pros::delay(5);
    //reset
    suspend_arm();
    set_arm(-30);
    set_tray_pid(TRAY_IN);
    set_intake(127);
    suspend_tray(); 
    tray_coast(); 
    set_tray(0);
}

void protected_auton(int color){
    //deploy and prep
    preauton();
    set_intake(127);
    set_arm(-20);
    normal_chassis();
    pros::delay(1000);

    //first cube
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    slow_chassis(4400);

    //turn towards tower cube
    chassisController.turnAngleAsync(color * 49_deg);
    chassisController.waitUntilSettled();
    normal_chassis();

    //tower cube
    profileController.setTarget("B");
    profileController.waitUntilSettled();

    //return
    profileController.setTarget("B", true);
    profileController.waitUntilSettled();
    slow_chassis(4400);
        
    //turn to face goal
    resume_tray();
    chassisController.turnAngleAsync(color * 105_deg);
    chassisController.waitUntilSettled();
    reset_intake_encoder();
    set_intake(-80);
    outtakeBit();

    //align with scoring zone
    set_tank(30, 30);
    pros::delay(1500);
    set_tank(0, 0);
    pros::delay(1000);

    //score
    fast_outtake();

    //back away - resume all
    resume_tray();
    set_tray_pid(TRAY_IN);
    while(get_tray_pos() > PROTECTED + 580)
        pros::delay(5);
    normal_chassis();
    suspend_tray(); 
    tray_coast(); 
    set_tray(0);
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
    //preauton();
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
    tray_coast(); 
    set_tray(0);

    //reset All
    drive_hold();
    pros::delay(20);
    set_tank(0, 0);
    set_intake(0);
    profileController.removePath("A");
    profileController.removePath("B");
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
    tray_coast(); 
    set_tray(0);
    tray_outtake();

    //come back
    resume_tray();
    chassisController.moveDistanceAsync(-20_in);
    resume_tray();
    set_tray_pid(LOCK_SAFE);
    chassisController.waitUntilSettled();
}

void test(){
    //straight
    drivepid(5500);
    chassisController.moveDistance(54_in);
    chassisController.waitUntilSettled();

    //turn
    slow_chassis(5000);
    chassisController.turnAngle(90_deg);
    chassisController.waitUntilSettled();
    
    //straight
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{48_in, 0_ft, 0_deg}}, "A");
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    profileController.removePath("A");
    
    //turn
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{0_ft, 0_ft, 90_deg}}, "B");
    profileController.setTarget("B");
    profileController.waitUntilSettled();
    profileController.removePath("B");
    
    //s curve
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{52_in, -28_in, 0_deg}}, "C");
    profileController.setTarget("C", true);
    profileController.waitUntilSettled();
    profileController.removePath("C");   
}

void pickup()
{
   //preauton
   preauton();
 
   //intake row
   set_intake(127);
   set_arm(-30);
   slow_chassis(9000);
   pros::delay(100);
   profileController.setTarget("A");
   profileController.waitUntilSettled();
 
   //s-curve to 2nd row
   normal_chassis();
   resume_tray();
   profileController.setTarget("B", true);
   set_tray_pid(LOCK_SAFE);
   set_intake(25);
   profileController.waitUntilSettled();
 
   //intake row
   slow_chassis(9000);
   set_intake(127);
   profileController.setTarget("C");
   set_tray_pid(TRAY_IN);
   profileController.waitUntilSettled();

    //reset
    set_intake(12);
    set_tank(0,0);
    suspend_tray();
    set_tray(0);
}
