/*semaphores for interconnection*/
extern struct semaphore robotArm1_s,robotArm2_s,robotArm3_s,robotArm4_s,robotArm5_s,robotArm6_s;
extern struct semaphore furnace1_s, furnace2_s, furnace3_iron_s, furnace3_co_s;
extern struct semaphore belt1_s,belt2_s,belt3_s,belt4_s;
extern struct semaphore observer_s, timer_s;

/*const values*/
extern const int ironNeed, coNeed;

/*critical sections between iron line*/
extern bool onBelt1[3];
extern bool onBelt3[3];
extern int heatTimeFurnace1;
/*semaphore for mutual exclusion*/
extern struct semaphore ironLine_s;

/*criticla sections between copper line*/
extern bool onBelt2[3];
extern bool onBelt4[3];
extern int heatTimeFurnace2;
/*semaphore for mutual exclusion*/
extern struct semaphore copperLine_s;


/*critical sections among furnace3 and robot arm5,robot arm6, */
extern int ironInFurnace3, coInFurnace3;
extern int heatTimeFurnace3;
/*semaphore for mutual exclusion*/
extern struct semaphore merging_s;

/*critical sections between observer and others*/
extern int remainIron, remainCo;
extern int CoFeIng;
/*semaphore for mutual exclusion*/
extern struct semaphore global_s;