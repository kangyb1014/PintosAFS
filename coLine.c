#include <string.h>

#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include <stdlib.h>

#include "variables.h"
#include "components.h"

void belt2(){
    while(true){
        /*wait for robot arm2 signal*/
        sema_down(&robotArm2_s);

        /*critical section*/
        sema_down(&copperLine_s);
        sema_down(&global_s);
        if(onBelt2[2] == false){
            for(int i = 2; i > 0; i--){
                onBelt2[i] = onBelt2[i-1];
            }
            onBelt2[0] = false;
            if(remainCo > 0){
                onBelt2[0] = true;
                remainCo--;
            }
        }
        sema_up(&global_s);
        sema_up(&copperLine_s);

        /*send signal to observer*/
        sema_up(&belt2_s);

    }
}

void robotArm2(){
    while(true){
        /*wait signal from furnace2*/
        sema_down(&furnace2_s);

        /*critical section*/
        sema_down(&copperLine_s);
        if(heatTimeFurnace2 == 0 && onBelt2[2]){
            onBelt2[2] = false;
            heatTimeFurnace2 = 1;
        }
        sema_up(&copperLine_s);

        /*send signal to belt2*/
        sema_up(&robotArm2_s);
    }
}

void furnace2(){
    while(true){
        /*wait for robot Arm 4*/
        sema_down(&robotArm4_s);

        /*critical section*/
        sema_down(&copperLine_s);
        if(heatTimeFurnace2 > 0){
            heatTimeFurnace2++;
        }
        sema_up(&copperLine_s);

        sema_up(&furnace2_s);
    }
}

void robotArm4(){
    while(true){
        /*wait for Belt 4*/
        sema_down(&belt4_s);

        /*critical section*/
        sema_down(&copperLine_s);
        if(onBelt4[0] == false && heatTimeFurnace2 > 1){
            onBelt4[0] = true;
            heatTimeFurnace2 = 0;
        }
        sema_up(&copperLine_s);
        
        /*send signal to furnace 2*/
        sema_up(&robotArm4_s);

    }
}

void belt4(){
    while(true){
        /*wait for robot Arm 6*/
        sema_down(&robotArm6_s);

        /*critical section*/
        sema_down(&copperLine_s);
        if(onBelt4[2] == false){
            for(int i = 2; i > 0; i--){
                onBelt4[i] = onBelt4[i-1];
            }
            onBelt4[0] = false;
        }
        sema_up(&copperLine_s); 

        /*send signal to robot arm 4*/
        sema_up(&belt4_s);
    }
}

void robotArm6(){
    while(true){
        /*wait signal from furnace3*/
        sema_down(&furnace3_co_s);
        /*critical section*/
        sema_down(&copperLine_s);
        sema_down(&merging_s);
        if(coInFurnace3 < coNeed && onBelt4[2]){
            onBelt4[2] = false;
            coInFurnace3++;
            if(ironInFurnace3 == ironNeed && coInFurnace3 == coNeed)
            heatTimeFurnace3++;
        }
        sema_up(&merging_s);
        sema_up(&copperLine_s);

        /*send signal to belt4*/
        sema_up(&robotArm6_s);

    }
}