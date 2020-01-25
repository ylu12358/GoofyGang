#include "main.h"

//ASYNC DOESNT BLOCK, REGULAR BLOCK..... for CHASSISCONTROLLER

void init_pr()
{
    // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{24_in, 0_in, 0_deg}}, "A");
    // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{51_in, 0_in, 0_deg}}, "B");
}

void init_pb()
{
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{20_in, 0_in, 0_deg}}, "A");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{20_in, 0_in, 0_deg}}, "B");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{80_in, 0_in, 0_deg}}, "C");
}

void init_upr()
{
    // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{28_in, 0_in, 0_deg}}, "A");
    // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{31_in, -28_in, 0_deg}}, "B");
    // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{51_in, 0_in, 0_deg}}, "C");
}

void init_upb()
{
    // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{28_in, 0_in, 0_deg}}, "A");
    // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{31_in, -28_in, 0_deg}}, "B");
    // profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{51_in, 0_in, 0_deg}}, "C");
}

void init_skill()
{
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{80_in, 0_in, 0_deg}}, "A");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{16_in, 0_in, 0_deg}}, "B");

}

void init_short_un(){
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{80_in, 0_in, 0_deg}}, "A");
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{10_in, 0_in, 0_deg}}, "B");
}


