#include "main.h"

//ASYNC DOESNT BLOCK, REGULAR BLOCK..... for CHASSISCONTROLLER
void init_protected(){
    profileController.generatePath({Point{0_in,0_in,0_deg}, Point{6_in,0_in,0_deg}},"A");
}

void init_skills()
{
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{80_in, 0_in, 0_deg}}, "A");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{16_in, 0_in, 0_deg}}, "B");
}

void init_6cube(){
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{80_in, 0_in, 0_deg}}, "A");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{13_in, 0_in, 0_deg}}, "B");
}


