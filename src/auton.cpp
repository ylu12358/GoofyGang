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
    //preauton
    normal_chassis();
    suspend_arm();
    set_tray_pid(TRAY_IN);
    set_arm(-20);

    //
    set_tank(-30,-30);
    set_intake(-127);
    pros::delay(1000);

    //slows down drivetrain, so intake not push cubes
    slow_chassis(5000);
    profileController.setTarget("A");
    pros::delay(100);
    set_intake(127);
    //generate path when theres time
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{1.3_ft, 2.9_ft, 40_deg}}, "B");
    profileController.waitUntilSettled();
    normal_chassis();
    //curve to second row
    profileController.setTarget("B", true);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3.1_ft, 0_ft, 0_deg}}, "C");
    profileController.waitUntilSettled();
    //wall align
    set_tank(-35, -35);
    pros::delay(2000);
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
    //preauton
    normal_chassis();
    suspend_arm();
    set_tray_pid(TRAY_IN);
    set_arm(-10);

    //
    set_tank(-30,-30);
    set_intake(-127);
    pros::delay(1000);

    //slows down drivetrain, so intake not push cubes
    slow_chassis(5000);
    profileController.setTarget("A");
    pros::delay(100);
    set_intake(127);
    //generate path when theres time
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{2_ft, -2.3_ft, -40_deg}}, "B");
    profileController.waitUntilSettled();
    normal_chassis();
    //curve to second row
    profileController.setTarget("B", true);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3.1_ft, 0_ft, 0_deg}}, "C");
    profileController.waitUntilSettled();
    //wall align
    set_tank(-35, -35);
    pros::delay(2000);
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
    normal_chassis();
    set_tank(100,100);
    pros::delay(100);
    set_tank(-100,-100);
    suspend_arm();
    set_arm(-50);
    set_tray_pid(TRAY_IN);
    set_intake(-127);
    pros::delay(100);

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

void ActRedPro(){
        //preauton
    slow_chassis(5000);
    suspend_arm();
    set_tray_pid(TRAY_IN);
    set_arm(-10);

    //
    set_tank(60,60);
    pros::delay(650);
    set_tank(-30,-30);
    set_intake(-127);
    pros::delay(800);

    set_tank(0,0);
    pros::delay(200);
    //
    set_tank(100,100);
    set_intake(127);
    pros::delay(900);

    //
    set_tank(-90,90);
    pros::delay(600);
        set_tank(0,0);
    pros::delay(200);

    set_tank(100,100);
    pros::delay(1000);

    set_tank(-90,90);
    pros::delay(370);
    set_tank(0,0);
    pros::delay(200);

    set_tank(40,40);
    pros::delay(1600);


    set_tank(-25,-25);
    pros::delay(100);		

    set_intake(-127);
    pros::delay(4000);

    set_tank(-50,-50);
    set_intake(0);
    pros::delay(500);

    set_tank(0,0);
                        // int l_intake_value = get_left_intake_pos();

    // intake_relative(-600,-200);
    // set_tank(-25,-25);
    // pros::delay(200);		
    //                 // while(get_left_intake_pos()-l_intake_value>=-510){
	// 	            // pros::lcd::set_text(4, "in");
    //                 //     pros::delay(5);
    //                 //     if(get_left_intake_pos()-l_intake_value>=-510){
    //                 //         set_intake(-75);
    //                 //     }
    //                 //     else
    //                 //     {
    //                 //         continue;
    //                 //     }
                        
    //                 // }

    // tray_outtake();
    // set_tank(-80, -80);
    // set_intake(-100);
    // pros::delay(800);
    // set_tank(0, 0);


    // //small distance
    // chassisController.moveDistance(10_in);
    // chassisController.waitUntilSettled();
    // chassisController.turnAngle(40_deg);
    // chassisController.waitUntilSettled();
    
    // //turn to face 4 stack. Slow chassis to intake, not push, cube
    // slow_chassis(9000);
    // set_intake(127);
    // chassisController.moveDistance(56_in); //originally 50 in
    // chassisController.waitUntilSettled();
    // normal_chassis();
    
    // //turn to collect 2 cubes
    // chassisController.moveDistance(-17_in); 
    // chassisController.waitUntilSettled();
    // chassisController.turnAngle(140_deg);
    // chassisController.waitUntilSettled();
    
    // //go forward to grab cube
    // // set_tank(127,127);
    // // pros::delay(100);
    // // set_tank(0,0);
    // // pros::delay(100);
    // chassisController.moveDistance(46_in);
    // chassisController.waitUntilSettled();
    
    // //come back to score
    // chassisController.moveDistance(-46_in);
    // chassisController.waitUntilSettled();
    
    // //turn to face score zone
    // chassisController.turnAngle(-45_deg);
    // chassisController.waitUntilSettled();
    
    // //score
    // chassisController.moveDistance(30_in);
    // chassisController.waitUntilSettled();
    // set_intake(0);
    // tray_outtake();
    // set_tank(-80, -80);
    // pros::delay(800);
    // set_tank(0, 0);
    
    //remove pid
    profileController.flipDisable();
    chassisController.stop();

}

void newRedPro(){
    //preauton
    slow_chassis(5000);
    suspend_arm();
    set_tray_pid(TRAY_IN);
    set_arm(-10);

    //
    set_tank(60,60);
    pros::delay(500);
    set_tank(-30,-30);
    set_intake(-127);
    pros::delay(500);

    set_tank(0,0);
    pros::delay(200);
    //
    set_tank(100,100);
    set_intake(127);
    pros::delay(900);

    //
    set_tank(90,-90);
    pros::delay(600);
        set_tank(0,0);
    pros::delay(200);

    set_tank(100,100);
    pros::delay(1000);

    set_tank(90,-90);
    pros::delay(370);
    set_tank(0,0);
    pros::delay(200);

    set_tank(40,40);
    pros::delay(1600);


    set_intake(0);
    pros::delay(100);
                        // int l_intake_value = get_left_intake_pos();

                        intake_relative(-525,-200);		
                    // while(get_left_intake_pos()-l_intake_value>=-510){
		            // pros::lcd::set_text(4, "in");
                    //     pros::delay(5);
                    //     if(get_left_intake_pos()-l_intake_value>=-510){
                    //         set_intake(-75);
                    //     }
                    //     else
                    //     {
                    //         continue;
                    //     }
                        
                    // }

    tray_outtake();
    set_tank(-80, -80);
    pros::delay(800);
    set_tank(0, 0);


    // //small distance
    // chassisController.moveDistance(10_in);
    // chassisController.waitUntilSettled();
    // chassisController.turnAngle(40_deg);
    // chassisController.waitUntilSettled();
    
    // //turn to face 4 stack. Slow chassis to intake, not push, cube
    // slow_chassis(9000);
    // set_intake(127);
    // chassisController.moveDistance(56_in); //originally 50 in
    // chassisController.waitUntilSettled();
    // normal_chassis();
    
    // //turn to collect 2 cubes
    // chassisController.moveDistance(-17_in); 
    // chassisController.waitUntilSettled();
    // chassisController.turnAngle(140_deg);
    // chassisController.waitUntilSettled();
    
    // //go forward to grab cube
    // // set_tank(127,127);
    // // pros::delay(100);
    // // set_tank(0,0);
    // // pros::delay(100);
    // chassisController.moveDistance(46_in);
    // chassisController.waitUntilSettled();
    
    // //come back to score
    // chassisController.moveDistance(-46_in);
    // chassisController.waitUntilSettled();
    
    // //turn to face score zone
    // chassisController.turnAngle(-45_deg);
    // chassisController.waitUntilSettled();
    
    // //score
    // chassisController.moveDistance(30_in);
    // chassisController.waitUntilSettled();
    // set_intake(0);
    // tray_outtake();
    // set_tank(-80, -80);
    // pros::delay(800);
    // set_tank(0, 0);
    
    //remove pid
    profileController.flipDisable();
    chassisController.stop();
}
void newNewRedUnpro(){
    //preauton
    normal_chassis();
    suspend_arm();
    set_tray_pid(TRAY_IN);
    set_arm(-10);

    //take first cube in the way
    set_intake(127);
    set_tank(100,100);
    pros::delay(600);

    //go back
    set_tank(-35,-35);
    pros::delay(2600);
    set_tank(40,40);
    pros::delay(500);

    //turn towards goal
    set_tank(-50, 50);
    pros::delay(700);
    set_tank(0, 0);
    set_intake(0);
    
    //release cube
    set_intake(-127);	
    resume_arm();
    set_arm_pid(1300);
    pros::delay(190);
    set_intake(0);
    while(get_arm_pos() < 1290)
        pros::delay(10);
    set_intake(-127);
    pros::delay(500);
    set_intake(0);
    set_arm_pid(0);
    set_tank(50, -50);
    pros::delay(700);
    set_tank(0, 0);
    set_tank(-35, -35);
    pros::delay(1000);
    set_tank(0, 0);
    pros::delay(10);
    //48
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{40_in, 0_in, 0_deg}}, "A");

    //grab stack
    set_intake(127);
    pros::delay(10);
    profileController.setTarget("A");
    profileController.waitUntilSettled();
	pros::Controller master(CONTROLLER_MASTER);
	master.set_text(0, 0, "1");

    //turn towards goal
    turn(130);
    set_tray_pid(PROTECTED);
    master.set_text(0, 0, "2");
    
    //move towards goal
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    
    //slowly align
    set_intake(0);
    set_tank(30,30);
    pros::delay(1000);

    //score
    tray_outtake();
    set_tank(-80, -80);
    set_intake(-40);
    pros::delay(800);
    set_tank(0, 0);
    

    //remove pid
    profileController.flipDisable();
}

void newRedUnpro(){
    //preauton
    normal_chassis();
    set_tank(100,100);
    pros::delay(100);
    set_tank(-100,-100);
    suspend_arm();
    set_arm(-50);
    set_tray_pid(TRAY_IN);
    set_intake(-127);
    pros::delay(100);
    
    //straight 4 cubes, including preload
    set_intake(127);
    chassisController.moveDistance(24.5_in); //originally 22
    chassisController.waitUntilSettled();
    normal_chassis();
    
    //2nd row
    //chassisController.turnAngle(26.565_deg);
    //set_tank(-127,-127);
    //pros::delay(100);
    //set_tank(0,0);
    //pros::delay(100);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{48_in, -24_in, 0_deg}}, "A");
    profileController.setTarget("A", true);
    profileController.waitUntilSettled();
    profileController.removePath("A");
    slow_chassis(9000);
    
    //straight (5 cube)
    chassisController.moveDistance(60_in); //originally 54
    chassisController.waitUntilSettled();
    normal_chassis();
    
    //turn to face score zone
    chassisController.turnAngle(-158_deg);
    chassisController.waitUntilSettled();
    
    //drive to score
    chassisController.moveDistanceAsync(33_in);
    // set_intake(-20);
    // pros::delay(100);
    chassisController.waitUntilSettled();
    set_intake(0);
    
    //score
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
    normal_chassis();
    suspend_arm();
    set_arm(-50);
    set_tray_pid(TRAY_IN);
    set_intake(-127);
    pros::delay(100);

    //small distance
    chassisController.moveDistance(10_in);
    chassisController.waitUntilSettled();
    chassisController.turnAngle(-40_deg);
    chassisController.waitUntilSettled();
    
    //turn to face 4 stack. Slow chassis to intake, not push, cube
    slow_chassis(9000);
    set_intake(127);
    chassisController.moveDistance(56_in); //originally 50 in
    chassisController.waitUntilSettled();
    normal_chassis();
    
    //turn to collect 2 cubes
    chassisController.moveDistance(-17_in);
    chassisController.waitUntilSettled();
    chassisController.turnAngle(-140_deg);
    chassisController.waitUntilSettled();
    
    //go forward to grab cube
    // set_tank(127,127);
    // pros::delay(100);
    // set_tank(0,0);
    // pros::delay(100);
    chassisController.moveDistance(46_in);
    chassisController.waitUntilSettled();
    
    //come back to score
    chassisController.moveDistance(-46_in);
    chassisController.waitUntilSettled();
    
    //turn to face score zone
    chassisController.turnAngle(45_deg);
    chassisController.waitUntilSettled();
    
    //score
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
    normal_chassis();
    set_tank(100,100);
    pros::delay(100);
    set_tank(-100,-100);
    suspend_arm();
    set_arm(-50);
    set_tray_pid(TRAY_IN);
    set_intake(-127);
    pros::delay(100);

    //straight 4 cubes, including preload
    set_intake(127);
    chassisController.moveDistance(24.5_in); //originally 22
    chassisController.waitUntilSettled();
    normal_chassis();
    
    //2nd row
    //chassisController.turnAngle(-26.565_deg);
    //set_tank(-127,-127);
    //pros::delay(100);
    //set_tank(0,0);
    //pros::delay(100);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{48_in, 24_in, 0_deg}}, "A");
    profileController.setTarget("A", true);
    profileController.waitUntilSettled();
    profileController.removePath("A");
    slow_chassis(9000);

    //straight (5 cube)
    chassisController.moveDistance(60_in); //originally 54
    chassisController.waitUntilSettled();
    normal_chassis();

    //turn to face score zone
    chassisController.turnAngle(158_deg);
    chassisController.waitUntilSettled();

    //drive to score
    chassisController.moveDistanceAsync(33_in);
    // set_intake(-20);
    // pros::delay(100);
    chassisController.waitUntilSettled();
    set_intake(0);

    //score
    tray_outtake();
    set_tank(-80, -80);
    pros::delay(800);
    set_tank(0, 0);
    
    //remove pid
    profileController.flipDisable();
    chassisController.stop();

}
void test(){
    //straight
    chassisController.moveDistance(72_in);
    chassisController.waitUntilSettled();

    //turn
    slow_chassis(5000);
    chassisController.turnAngle(90_deg);
    chassisController.waitUntilSettled();
    
    //straight
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, 0_ft, 0_deg}}, "A");
    profileController.setTarget("A");
    profileController.waitUntilSettled();
    profileController.removePath("A");
    
    //turn
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{0_ft, 0_ft, 90_deg}}, "B");
    profileController.setTarget("B");
    profileController.waitUntilSettled();
    profileController.removePath("B");
    
    //s curve
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, -2_ft, 0_deg}}, "C");
    profileController.setTarget("C", true);
    profileController.waitUntilSettled();
    profileController.removePath("C");   

    //test whether long distance screws pid
    //test whether cube amount screws pid (less friction from wheel... different weight distribution)
    //test whether initial chassis voltage is 10,000 or not (so distance is accurate with which voltage setting)
    //test to see whether pid and voltage limitation is removed during driver op
    //test if angle is affected by voltage limiting

    //test inertia sensor? (velocity * time to determine distance -> pid)

}