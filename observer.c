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

#define isOre(x) (x? 'o' : ' ')
#define isIngot(x) (x? 'i': ' ')
#define melting(x) (x < 1? ' ':(x > 1 ? 'i':'o'))

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
    int i = 0;
    bool flag = false;
    while(!flag){
        sema_up(&observer_s);
        /* copper 만들면 사용 */
        //sema_up(&observer_s);
        sema_down(&belt1_s);
        //sema_down(&belt2_s);
        sema_down(&timer_s);

        /*critical section, output*/
        sema_down(&ironLine_s);
        sema_down(&copperLine_s);
        sema_down(&merging_s);
        sema_down(&global_s);

        printf("\n%d second, %d CoFeIng created is %d\n",++i,CoFeIng);

        printf("X X X X X X X X X X\n");
        printf("%c %c %c @ %c @ %c %c %c @\n",
        isOre(onBelt1[0]),isOre(onBelt1[1]), isOre(onBelt1[2]),
        melting(heatTimeFurnace1),
        isIngot(onBelt3[0]),isIngot(onBelt3[1]),isIngot(onBelt3[2])
        );
        printf("X X X X X X X X X \n");
        printf("%c %c %c @ %c @ %c %c %c @\n",
        isOre(onBelt2[0]),isOre(onBelt2[1]), isOre(onBelt2[2]),
        melting(heatTimeFurnace2),
        isIngot(onBelt4[0]),isIngot(onBelt4[1]),isIngot(onBelt4[2])
        );
        printf("X X X X X X X X X X\n");

        /*terminate condition*/
        if(ironInFurnace3 < ironNeed || coInFurnace3 < coNeed){
            if(!onBelt1[0] && !onBelt1[1] && !onBelt1[2] && 
            !onBelt3[0] && !onBelt3[1] && !onBelt3[2] && heatTimeFurnace1 == 0)
            flag = true;
            
            else if(!onBelt2[0] && !onBelt2[1] && !onBelt2[2] && 
            !onBelt4[0] && !onBelt4[1] && !onBelt4[2] && heatTimeFurnace2 == 0)
            flag = true;
        }

        sema_up(&global_s);
        sema_up(&merging_s);
        sema_up(&copperLine_s);
        sema_up(&ironLine_s);
    }
    printf("finished!\n");
    /*kill threads*/
}