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
    int l_error = target - (get_left_drive_pos() - l_first); //idk why its subtract l_fist
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
    set_intake(-127);
    set_tank(-30,-30);
    pros::delay(300);
    set_intake(127);                            //start intaking
    set_tank(0,0);
    pros::delay(750);


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
    chassisController -> stop();
    //suspend tray pid
    suspend_tray(); 
    tray_coast(); 
    set_tray(0);
    //suspend drive pid
    profileController -> flipDisable();
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
    while (get_left_intake_pos() > -300) //530
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
    pros::delay(200);
    //correct arm pos
    resume_arm();
    set_arm_pid(LOW_TOWER);
    //outtake
    profileController -> setTarget("D");
    profileController -> waitUntilSettled();
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

void skills1()
{      
    //preauton
    preauton();

    //intake row
    set_intake(127);
    set_arm(-30);
    slow_chassis(4800);
    profileController -> setTarget("A");
    profileController -> waitUntilSettled();

    //turn towards tower
    chassisController -> turnAngleAsync(-20_deg);
    chassisController -> waitUntilSettled();
    slow_chassis(2400);

    //intake last cube
    profileController -> setTarget("B");
    profileController -> waitUntilSettled();
    slow_chassis(4800);

    //move away from tower
    profileController -> setTarget("D", true);
    profileController -> waitUntilSettled();

    //score low tower
    lowTower();

    //turns toward straight line of cubes
    // chassisController -> turnAngleAsync(16_deg);
    // chassisController -> waitUntilSettled();

        //turn to score
    profileController -> setTarget("D", true);
    resume_tray();
    chassisController -> turnAngleAsync(105.35_deg);
    chassisController -> waitUntilSettled();
    set_intake(25);
    set_tray_pid(PROTECTED);
    

    //drive forward
    slow_chassis(5300);
    profileController -> setTarget("A");
    profileController -> waitUntilSettled();
    set_tank(30,30);
    pros::delay(150);
    intake_coast();
    set_tank(0,0);
    outtakeBit();

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

}

void skills2()
{
    //8 cubes straight
    profileController -> setTarget("C");
    //disable arm
    suspend_arm();
    set_arm(-30);
    reset_arm_encoder();
    suspend_tray(); 
    tray_coast(); 
    set_tray(0);
    profileController -> waitUntilSettled();

    //turn and score
    chassisController -> turnAngle(45_deg);
    chassisController -> waitUntilSettled();
    set_tank(40,40);
    pros::delay(700);
    set_intake(0);
    tray_outtake();

    //come back
    resume_tray();
    set_tank(-100,-100);
    resume_tray();
    set_tray_pid(LOCK_SAFE);
    pros::delay(700);
}

void test(){
    // intake stack

    // profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {16_in, 0_ft, 0_deg}}, "A");
    // profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {7_in, 0_ft, 0_deg}}, "D");

    // profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {2_in, 0_ft, 0_deg}}, "B");
    // profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {4_in, 0_ft, 0_deg}}, "C");
    // set_intake(127);
    // profileController -> setTarget("D");
    // profileController -> waitUntilSettled();

    // float left = (get_left_drive_pos());
    // float right = (get_right_drive_pos());


    // turnAng(45);
    // while(get_left_drive_pos()-left<((45*5)-2) && right-get_right_drive_pos()<((45*5)-2)){
    //     pros::delay(20);
    // }
    // set_intake(-127);
    // left = get_left_drive_pos();
    // right = get_right_drive_pos();
    // pros::delay(500);
    // turnAng(-45);
    // while(left-get_left_drive_pos()<((45*5)-2) && get_right_drive_pos()-right<((45*5)-2)){
    //     pros::delay(20);
    // }

    // set_intake(127);


    // set_arm_pid(HIGH_TOWER);
    // profileController -> setTarget("A");
    // profileController -> waitUntilSettled();
    // suspend_arm();
    // while(get_arm_pos()> 100){
    //     set_arm(-80);
    // }
    // profileController -> setTarget("B", true);
    // set_arm(-20);
    // profileController -> waitUntilSettled();

    // pros::delay(1000);
    // profileController -> setTarget("C");
    // profileController -> waitUntilSettled();
}

void new_skills(){
    //move forward - first row
    preauton();
    set_intake(127);
    profileController -> generatePath({{0_in,0_in,0_deg}, {40_in,0_in,0_deg}},"A");
    profileController -> setTarget("A");
    profileController -> waitUntilSettled();
    
    //score tower
    turn(45);
    profileController -> generatePath({{0_in,0_in,0_deg}, {22_in,0_in,0_deg}},"B");
    profileController -> setTarget("B");
    profileController -> waitUntilSettled();
    lowTower();

    //move back and score in tower
    turn(180);
    profileController -> generatePath({{0_in,0_in,0_deg}, {40_in,0_in,0_deg}},"C");
    profileController -> setTarget("C");
    profileController -> waitUntilSettled();
    lowTower();

    //turn and score in tower
    turn(-120);
    profileController -> generatePath({{0_in,0_in,0_deg}, {40_in,0_in,0_deg}},"D");
    profileController -> setTarget("D");
    profileController -> waitUntilSettled();
    lowTower();

    //second row
        turn(-90);
        //wall align
        set_tank(-127,-127);
        pros::delay(100);
    profileController -> generatePath({{0_in,0_in,0_deg}, {80_in,0_in,0_deg}},"E");
    profileController -> setTarget("E");
    profileController -> waitUntilSettled();

    //tower in high
    turn(-100);
    profileController -> generatePath({{0_in,0_in,0_deg}, {20_in,0_in,0_deg}},"F");
    profileController -> setTarget("F");
    profileController -> waitUntilSettled();

    //tower
    profileController -> generatePath({{0_in,0_in,0_deg}, {40_in,0_in,0_deg}},"G");
    profileController -> setTarget("G", true);
    profileController -> waitUntilSettled();
    turn(100);
    profileController -> generatePath({{0_in,0_in,0_deg}, {40_in,0_in,0_deg}},"H");
    profileController -> setTarget("H");
    profileController -> waitUntilSettled();
    turn(90);
    profileController -> generatePath({{0_in,0_in,0_deg}, {20_in,0_in,0_deg}},"I");
    profileController -> setTarget("I");
    profileController -> waitUntilSettled();
    lowTower();

    //score stack
    turn(-100);
    profileController -> generatePath({{0_in,0_in,0_deg}, {40_in,0_in,0_deg}},"J");
    profileController -> setTarget("J");
    profileController -> waitUntilSettled();
    outtakeBit();
    fast_outtake();

    //third row
    profileController -> generatePath({{0_in,0_in,0_deg}, {10_in,0_in,0_deg}},"L");
    profileController -> setTarget("L", true);
    profileController -> waitUntilSettled();
    turn(-100);
    set_intake(127);
    profileController -> generatePath({{0_in,0_in,0_deg}, {40_in,0_in,0_deg}},"M");
    profileController -> setTarget("M");
    profileController -> waitUntilSettled();
    
    //tower
    turn(-45);
    profileController -> generatePath({{0_in,0_in,0_deg}, {20_in,0_in,0_deg}},"N");
    profileController -> setTarget("N");
    profileController -> waitUntilSettled();
    lowTower();

    //tower again
    turn(180);
    profileController -> generatePath({{0_in,0_in,0_deg}, {40_in,0_in,0_deg}},"O");
    profileController -> setTarget("O");
    profileController -> waitUntilSettled();
    lowTower();

    //rush to last tower


    //score whatever
}








void unprotect(int color){

    // profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {26_in, 0_in, 0_deg}}, "A");
    // profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {28_in, 0_in, 0_deg}}, "B");

    // profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {145_in, 0_in, 0_deg}}, "C");
    // profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {90_in, 0_in, 0_deg}}, "D");

    preauton();
    profileController -> setTarget("A");
    profileController -> waitUntilSettled();
    turnAng(45*-color, 60);
    set_tray_pid(AUTON_LIFT);
    pros::delay(410);
    profileController -> setTarget("B", true);
    profileController -> waitUntilSettled();
    turnAng(-38*-color,60);
    pros::delay(410);
    set_tank(0,0);
    pros::delay(150);
    set_tank(-70,-70);
    pros::delay(500);
    set_tray_pid(TRAY_IN);
    slow_chassis(5500);
    profileController -> setTarget("C");
    profileController -> waitUntilSettled();
    profileController -> setTarget("D", true);
    profileController -> waitUntilSettled();

    suspend_tray();
    turnAng(-125*-color,80);
    pros::delay(1500);
    set_tank(40,40);
    pros::delay(600);
    outtakeBit();
    fast_outtake();
    set_intake(-100);
    set_tank(-100,-100);
    pros::delay(800);
    set_tank(0,0);
    set_intake(0);

}

void protect(int color){
     
    // calculate different paths needed - included in autonomous for easy reference
    // profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {10_in, 0_in, 0_deg}}, "A");
    // profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {24_in, 0_in, 0_deg}}, "B");
    // profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {20_in, 0_in, 0_deg}}, "C");
    // profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {23_in, 0_in, 0_deg}}, "D");

    preauton();                                 //deploy tray

    profileController -> setTarget("A");        //picks up the first red cube
    profileController -> waitUntilSettled();    //waits until action is completed
    turnAng(13*color,30);                            //turn to face tower in the middle of the field
    pros::delay(500);

    profileController -> setTarget("B");        //picks up tower cube
    profileController -> waitUntilSettled();
    set_tank(60,60);
    pros::delay(300);
    profileController -> setTarget("D", true);  //backs up
    profileController -> waitUntilSettled();
    turnAng(66*color,30);                            //turn to face tower on our side of the field
    pros::delay(800);
    profileController -> setTarget("C");        //picks up both cubes
    profileController -> waitUntilSettled();
    set_tank(60,60);
    pros::delay(350);
    profileController -> setTarget("B", true);  //backs up
    profileController -> waitUntilSettled();
    turnAng(130*color,60);                           //turn to face goal
    outtakeBit();                               //outtake a bit - cube is not in the arm when scoring
    pros::delay(1200);
    set_tank(40,40);                            //drives forward a bit - align
    pros::delay(600);
    set_tank(0,0);
    pros::delay(300);
    fast_outtake();                             //fast score for stacks with less than 8 cubes
    set_intake(-100);                           //moves the stack out from rollers
    set_tank(-100,-100);                        //moves back from stack
    pros::delay(300);
    //stops all movement
    set_tank(0,0);
    set_intake(0);



}

void skill(){

    preauton();                                 //deploy

    profileController -> setTarget("A");        //first entire row of cubes
    profileController -> waitUntilSettled();    //wait until action completes
    turnAng(45,60);
    pros::delay(600);
    profileController -> setTarget("E");
    profileController -> waitUntilSettled();
    turnAng(-90, 60);
    pros::delay(1800);
    profileController -> setTarget("E");
    profileController -> waitUntilSettled();
    turnAng(45, 60);
    profileController -> setTarget("A");


    turnAng(45,60);                             //turn to face goal
    pros::delay(600);
    profileController -> setTarget("B");        //move towards goal
    profileController -> waitUntilSettled();
    outtakeBit();                               //outtake - cube doesnt fall
    fast_outtake();                             //fast score
    
    profileController -> setTarget("B", true);  //move out of goal
    set_intake(-127);                           //move stack out of intake
    profileController -> waitUntilSettled();
    
    turnAng(-120, 70);                          //turn to face tower
    set_intake(127);                            //intake
    pros::delay(2000);
    profileController -> setTarget("C");        //grab tower cube
    profileController -> waitUntilSettled();
    lowTower();                                 //tower cube
    
    turnAng(90,60);                             //turn to face second row
    pros::delay(1500);
    profileController -> setTarget("A");        //intake row
    profileController -> waitUntilSettled();
    
    profileController -> setTarget("B", true);  //back away from wall to turn
    profileController -> waitUntilSettled();
    turnAng(-30, 50);                           //turn to face goal
    pros::delay(1000);
    profileController -> setTarget("D");        //move towards goal
    profileController -> waitUntilSettled();
    outtakeBit();                               //outtake - cube doesnt fall
    fast_outtake();                             //fast score
    set_intake(-100);
    set_tank(-100,-100);

}