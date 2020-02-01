#include "main.h"

//ASYNC DOESNT BLOCK, REGULAR BLOCK..... for CHASSISCONTROLLER
void init_protected(){
    profileController.generatePath({Point{0_in,0_in,0_deg}, Point{22_in,0_in,0_deg}},"A");
    profileController.generatePath({Point{0_in,0_in,0_deg}, Point{39_in,0_in,0_deg}},"B");
    // profileController.generatePath({Point{0_in,0_in,0_deg}, Point{5_in,0_in,0_deg}},"C");
}

void init_skills()
{
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{80_in, 0_in, 0_deg}}, "A");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{16_in, 0_in, 0_deg}}, "B");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{140_in, 0_in, 0_deg}}, "C");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{10_in, 0_in, 0_deg}}, "D");
}

void init_6cube(){
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{80_in, 0_in, 0_deg}}, "A");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{13_in, 0_in, 0_deg}}, "B");
}

void init_pickup(){
   profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{22_in, 0_in, 0_deg}}, "A");
   profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{31_in, -28_in, 0_deg}}, "B");
   profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{51_in, 0_in, 0_deg}}, "C");
}

void new_route_init(){
   profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{40_in, 0_in, 0_deg}}, "A");
   profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{20_in, 0_in, 0_deg}}, "B");
   profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{60_in, 0_in, 0_deg}}, "C");
}
