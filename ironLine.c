#include <string.h>

#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include <stdlib.h>

#include "variables.h"
#include "components.h"

void belt1(){
    while(true){
        /*wait for robot arm1 signal*/
        sema_down(&robotArm1_s);

        /*critical section*/
        sema_down(&ironLine_s);
        sema_down(&global_s);
        if(onBelt1[2] == false){
            for(int i = 2; i > 0; i--){
                onBelt1[i] = onBelt1[i-1];
            }
        }
        if(remainIron > 0){
            onBelt1[0] = true;
            remainIron--;
        }
        sema_up(&global_s);
        sema_up(&ironLine_s);

        /*send signal to observer*/
        sema_up(&belt1_s);
    }
}

void robotArm1(){
    while(true){
        /*wait signal from furnace*/
        sema_down(&furnace1_s);

        /*critical section*/
        sema_down(&ironLine_s);
        if(heatTimeFurnace1 == 0 && onBelt1[2]){
            onBelt1[2] = false;
            heatTimeFurnace1++;
        }
        sema_up(&ironLine_s);

        /*send signal to belt*/
        sema_up(&robotArm1_s);
    }
}

void furnace1(){
    while(true){
        /*wait for robot Arm 3*/
        sema_down(&robotArm3_s);

        /*critical section*/
        sema_down(&ironLine_s);
        if(heatTimeFurnace1 < 2){
            heatTimeFurnace1++;
        }
        sema_up(&ironLine_s);

        sema_up(&furnace1_s);
    }
}

void robotArm3(){
    while(true){
        /*wait for Belt 3*/
        sema_down(&belt3_s);

        /*critical section*/
        sema_down(&ironLine_s);
        if(onBelt3[0] == false && heatTimeFurnace1 == 2){
            onBelt3[0] == true;
            heatTimeFurnace1 = 0;
        }
        sema_up(&ironLine_s);

        /*send signal to furnace 1*/
        sema_up(&robotArm3_s);
    }
}

void belt3(){
    while(true){
        /*wait for robot Arm 5*/
        sema_down(&robotArm5_s);

        /*critical section*/
        sema_down(&ironLine_s);
        if(onBelt3[2] == false){
            for(int i = 2; i > 0; i--){
                onBelt3[i] = onBelt3[i-1];
            }
            onBelt3[0] = false;
        }
        sema_up(&ironLine_s); 

        /*send signal*/
        sema_up(&belt3_s);
    }
}

void robotArm5(){
    while(true){
        /*wait signal from furnace3*/
        sema_down(&furnace3_iron_s);

        /*critical section*/
        sema_down(&ironLine_s);
        sema_down(&merging_s);
        if(ironInFurnace3 < ironNeed && onBelt3[2]){
            onBelt3[2] = false;
            ironInFurnace3++;
            if(ironInFurnace3 == ironNeed && coInFurnace3 == coNeed)
            heatTimeFurnace3++;
        }
        sema_up(&merging_s);
        sema_up(&ironLine_s);

        /*send signal to belt3*/
        sema_up(&robotArm5_s);

    }
}