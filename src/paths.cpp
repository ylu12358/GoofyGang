#include "main.h"

//ASYNC DOESNT BLOCK, REGULAR BLOCK..... for CHASSISCONTROLLER
void init_protected(){
    profileController.generatePath({Point{0_in,0_in,0_deg}, Point{18_in,0_in,0_deg}},"A");
    profileController.generatePath({Point{0_in,0_in,0_deg}, Point{28_in,0_in,0_deg}},"B");
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

void init_pickup(){

   profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{22_in, 0_in, 0_deg}}, "A");
   profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{31_in, -28_in, 0_deg}}, "B");
   profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{51_in, 0_in, 0_deg}}, "C");

}
