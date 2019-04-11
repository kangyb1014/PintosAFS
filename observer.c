#include <stdio.h>
#include <string.h>

#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"

#include "devices/timer.h"

#include <stdlib.h>

#include <stdbool.h>
#include "variables.h"
#include "components.h"


void furnace3(){
    while(true){
        /*wait signal from observer*/
        sema_down(&observer_s);

        /*critical section*/
        sema_down(&merging_s);
        sema_down(&global_s);
        if(ironInFurnace3 == ironNeed && coInFurnace3 == coNeed){
            if(heatTimeFurnace3 == 3){
                ironInFurnace3 = 0;
                coInFurnace3 = 0;
                CoFeIng++;
                heatTimeFurnace3 = 0;
            }
            else{
                heatTimeFurnace3++;
            }
        }
        sema_up(&global_s);
        sema_up(&merging_s);

        /*send signal to robot arms*/
        sema_up(&furnace3_iron_s);
        sema_up(&furnace3_co_s);
    }
}


void timer(){
    while(true){
        /*if time change*/
        sema_up(&timer_s);
        /*wait for time change*/
    }
}

void observer(){
    /*더 이상 못 만들 때까지*/
    int i = 0;
    while(i < 10){
        sema_up(&observer_s);
        /* copper 만들면 사용 */
        //sema_up(&observer_s);
        sema_down(&belt1_s);
        //sema_down(&belt2_s);
        sema_down(&timer_s);

        /*critical section, output*/
        printf("%d second\n",i++);

        sema_down(&ironLine_s);
        sema_down(&copperLine_s);
        sema_down(&merging_s);
        sema_down(&global_s);
        printf("X X X X X X X X X X");
        
        sema_up(&global_s);
        sema_up(&merging_s);
        sema_up(&copperLine_s);
        sema_up(&ironLine_s);
    }
    printf("finished!\n");
    /*kill threads*/
}