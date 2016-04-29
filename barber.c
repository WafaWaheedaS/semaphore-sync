#define _REENTRANT
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#include </home/wafa/semt1/semlib.h> // Our semaphore library - header file;

#define TRUE 1
#define FALSE 0
#define MIN_TIME 4
#define MAX_TIME 8

#define MAX_NUM_CUSTOMERS 50

void *customer(void *num); // Prototype for customer thread
void *barber(void *); // Prototype of barber thread 
int UD(int, int); // Random number generator
int doneWithAllCustomers = FALSE; // Flag indicating the barber can go home

int main(int argc, char **argv){

  if(argc < 3){
    printf("enter this for proper execution: ./barber <no of customers> <no of chairs> \n");
    exit(0);
  }

  int numCustomers = atoi(argv[1]); // Number of customers
  int numWaitingChairs = atoi(argv[2]); // Number of waiting chairs in the barber shop

  srand((long)time(NULL)); // sInitialize randomizer
 
  if(numCustomers > MAX_NUM_CUSTOMERS){
    printf("Number of customers exceeds the maximum capacity of the barber \n");
    printf("Resetting the number of customers to %d \n", (int)MAX_NUM_CUSTOMERS);
    numCustomers = MAX_NUM_CUSTOMERS;
  }
  
  sbarber(numWaitingChairs);  // calling semaphore sbarber fn - which initializess semaphores

  pthread_t btid; // ID for the barber thread
  pthread_t tid[MAX_NUM_CUSTOMERS]; // IDs for customer threads

  /* Create barber thread */
  pthread_create(&btid, 0, barber, 0); 

  /* Create customer threads and give each an ID */
  int customerID[MAX_NUM_CUSTOMERS]; // Customer IDs
  int i;
  for(i = 0; i < numCustomers; i++){
    customerID[i] = i;
    pthread_create(&tid[i], 0, customer, &customerID[i]);
  }
  
  for(i = 0; i < numCustomers; i++)
    pthread_join(tid[i], 0);

  doneWithAllCustomers = TRUE;
  sbarber_bed_signal(); // Wake up barber
  pthread_join(btid, 0);
}

void *barber(void *junk){

  while(!doneWithAllCustomers){ // Customers remain to be serviced
    printf("Barber:- Sleeping** \n");
    sbarber_bed_wait(); // Barber goes back to sleeping
    if(!doneWithAllCustomers){
      printf("Barber:- Cutting hair.. \n");
      int waitTime = UD(MIN_TIME, MAX_TIME); // wait time for every customer
      sleep(waitTime); // reflected on the terminal
      sbarber_doneCust_signal(); // Indicate that chair is free
    }
    else{
      printf("Barber:- Done for the day..Going home.... :) \n");
    }
  }
}

void *customer(void *customerNumber){
  int number = *(int *)customerNumber;
  printf("C%d:- Leaving for barber shop \n", number);
  int waitTime = UD(MIN_TIME, MAX_TIME); // Simulate going to the barber shop
  sleep(waitTime);
  printf("C%d:- Arrived at barber shop \n", number);
  sbarber_waitingRoom_wait(); // Wait to get into the barber shop
  printf("C%d:- Entering waiting room \n", number);

  sbarber_bSeat_wait();    // Wait for the barber to become free
  sbarber_waitingRoom_signal();   // Let people waiting outside the shop know

  sbarber_bed_signal();   // Wake up barber
  sbarber_doneCust_wait();  // Wait until hair is cut
  sbarber_bSeat_signal();  // Give up seat

  printf("C%d:- Done. Leaving barer shop \n", number);
}


int UD(int min, int max){
  // Returns a random number between min and max
  return((int)floor((double)(min + (max - min + 1)*((float)rand()/(float)RAND_MAX))));
}



