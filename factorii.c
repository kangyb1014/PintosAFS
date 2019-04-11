#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"

#include "devices/timer.h"

#include "components.h"

/*semaphores for interconnection*/
struct semaphore robotArm1_s,robotArm2_s,robotArm3_s,robotArm4_s,robotArm5_s,robotArm6_s;
struct semaphore furnace1_s, furnace2_s, furnace3_iron_s, furnace3_co_s;
struct semaphore belt1_s,belt2_s,belt3_s,belt4_s;
struct semaphore observer_s, timer_s;

/*const values*/
const int ironNeed = 3, coNeed = 0;

/*critical sections between iron line*/
bool onBelt1[3] = {0,0,0};
bool onBelt3[3] = {0,0,0};
int heatTimeFurnace1 = 0;
/*semaphore for mutual exclusion*/
struct semaphore ironLine_s;

/*criticla sections between copper line*/
bool onBelt2[3] = {0,0,0};
bool onBelt4[3] = {0,0,0};
int heatTimeFurnace2 = 0;
/*semaphore for mutual exclusion*/
struct semaphore copperLine_s;


/*critical sections among furnace3 and robot arm5,robot arm6, */
int ironInFurnace3 = 0, coInFurnace3 = 0;
int heatTimeFurnace3 = 0;
/*semaphore for mutual exclusion*/
struct semaphore merging_s;

/*critical sections between observer and others*/
int remainIron = 6, remainCo = 0;
int CoFeIng = 0;
/*semaphore for mutual exclusion*/
struct semaphore global_s;

void run_factorii(char **argv){
        /*initialize sp*/
        sema_init(&robotArm1_s,0);
        sema_init(&robotArm2_s,0);
        sema_init(&robotArm3_s,0);
        sema_init(&robotArm4_s,0);
        sema_init(&robotArm5_s,0);
        sema_init(&robotArm6_s,0);
        sema_init(&furnace1_s,0);
        sema_init(&furnace2_s,0);
        sema_init(&furnace3_iron_s,0);
        sema_init(&furnace3_co_s,0);
        sema_init(&belt1_s,0);
        sema_init(&belt2_s,0);
        sema_init(&belt3_s,0);
        sema_init(&belt4_s,0);
        sema_init(&observer_s,0);
        sema_init(&timer_s,0);

        /*initialize semaphores for critical sections*/
        sema_init(&ironLine_s,1);
        sema_init(&copperLine_s,1);
        sema_init(&merging_s,1);
        sema_init(&global_s,1);

        thread_create("observer",PRI_DEFAULT,observer,NULL);
        
        thread_create("timer",PRI_DEFAULT,timer,NULL);

        
        thread_create("furnace1",PRI_DEFAULT,furnace1,NULL);
        //thread_create("furnace2",PRI_DEFAULT,furnace2,NULL);
        thread_create("furnace3",PRI_DEFAULT,furnace3,NULL);
        thread_create("robotArm1",PRI_DEFAULT,robotArm1,NULL);
        //thread_create("robotArm2",PRI_DEFAULT,robotArm2,NULL);
        thread_create("robotArm3",PRI_DEFAULT,robotArm3,NULL);
        //thread_create("robotArm4",PRI_DEFAULT,robotArm4,NULL);
        thread_create("robotArm5",PRI_DEFAULT,robotArm5,NULL);
        //thread_create("robotArm6",PRI_DEFAULT,robotArm6,NULL);
        thread_create("belt1",PRI_DEFAULT,belt1,NULL);
        //thread_create("belt2",PRI_DEFAULT,belt2,NULL);
        thread_create("belt3",PRI_DEFAULT,belt3,NULL);
        //thread_create("belt4",PRI_DEFAULT,belt4,NULL);


        printf("implement factorii !\n");

        return 0;
}
