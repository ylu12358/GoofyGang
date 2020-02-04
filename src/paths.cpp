#include "main.h"

//ASYNC DOESNT BLOCK, REGULAR BLOCK..... for CHASSISCONTROLLER
void init_protected(){
    profileController -> generatePath({{0_in,0_in,0_deg}, {22_in,0_in,0_deg}},"A");
    profileController -> generatePath({{0_in,0_in,0_deg}, {39_in,0_in,0_deg}},"B");
    // profileController -> generatePath({{0_in,0_in,0_deg}, 5_in,0_in,0_deg}},"C");
}

void init_skills()
{
    profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {80_in, 0_in, 0_deg}},"A");
    profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {16_in, 0_in, 0_deg}},"B");
    profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {140_in, 0_in, 0_deg}},"C");
    profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {10_in, 0_in, 0_deg}},"D");
}

void init_6cube(){
    profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {80_in, 0_in, 0_deg}},"A");
    profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {13_in, 0_in, 0_deg}},"B");
}

void init_pickup(){
   profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {22_in, 0_in, 0_deg}},"A");
   profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {31_in, -28_in, 0_deg}},"B");
   profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {51_in, 0_in, 0_deg}},"C");
}

void new_route_init(){
   profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {40_in, 0_in, 0_deg}},"A");
   profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {20_in, 0_in, 0_deg}},"B");
   profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {60_in, 0_in, 0_deg}},"C");
}
