#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>


#include "semlib.h" // importing the library for synchronisation using semaphores from path


void *leader_fn(void *arg);
void *follower_fn(void *arg);

int main(){

fprintf(stderr,"Queues start..\n");

int numThreads=5;
int i;
pthread_t f[numThreads];  // creating thread 1 & 2 using pthread.h 
pthread_t l[numThreads];

queues(); // calling rendezvous function from semlib.h

for (i=0;i<numThreads;i++){
    if(pthread_create(&l[i], NULL, leader_fn, NULL)==-1){
        printf("Error Creating thread a.\n");
    }
}

for (i=0;i<numThreads;i++){
    if(pthread_create(&f[i], NULL, follower_fn, NULL)==-1){
        printf("Error Creating thread a.\n");
    }
}

for (i=0;i<numThreads;i++){
    pthread_join(f[i], NULL);
    pthread_join(l[i], NULL);
}



} // closing main

void *leader_fn(void *arg){
lqueues_wait();
printf("I am dancing with a follower... \n");
lqueues_signal();
printf("I am done dancing...\n");
return((void *)0);//return(NULL);
}

void *follower_fn(void *arg){
fqueues_wait();
printf("I am dancing with a leader... \n");
fqueues_signal();
printf("I am done dancing...\n");
return((void *)0);//return(NULL);
}
