#include "main.h"

//ASYNC DOESNT BLOCK, REGULAR BLOCK..... for CHASSISCONTROLLER

void chassis_straight()
{
    chassisController.moveDistanceAsync(36_in);
}

void chassis_turn()
{
    chassisController.turnAngle(90_deg);
}
/*


protected zone



drive forward (push cube)
drive backward
deploy tray

intake
drive forward

curve a bit to get last cube

drive backward
point turn to goal (only variable in code, blue or red)
drive forward

outake
tray outake

drive backward
reset tray

*/

void init_pr()
{
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{12_ft, 0_ft, 0_deg}}, "B");
}

void init_pb()
{
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{12_ft, 0_ft, 0_deg}}, "B");
}

void init_upr()
{
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{6_ft, 0_ft, 0_deg}}, "A");
    // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, 0_ft, 0_deg}}, "A");
    // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, -2_ft, 0_deg}}, "B");
    // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, -2_ft, 275_deg}}, "C");
    // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3_ft, 0_ft, 0_deg}}, "D");
}

void init_upb_maybe()
{
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{2_ft, 0_ft, 0_deg}}, "A");
    //25_in
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, 2.2_ft, 0_deg}}, "B");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, -2_ft, 95_deg}}, "C");
    //53.5_in
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{2.55_ft, 0_ft, 0_deg}}, "D");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{.458_ft, 0_ft, 0_deg}}, "E");
    //5.5_in
}

void init_upb(){
        profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{6_ft, 0_ft, 0_deg}}, "A");

    // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{30.5_in, 0_ft, 0_deg}}, "A");
    // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{.458_ft, 0_ft, 0_deg}}, "B");
    // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{.916_ft, 0_ft, 0_deg}},"E");
    // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{43.5_in, 2_ft, 4.5_deg}}, "C");
    // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{4_ft, -1_ft, 95_deg}}, "D");
    // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{1_ft, 0_ft, 0_deg}}, "F");
    
    //intake, 
    //30.5_ft
    //E,E
    //s-curve (may need to chunk)
    //intake, A, E, E, E, intake, C, D, deploy
}