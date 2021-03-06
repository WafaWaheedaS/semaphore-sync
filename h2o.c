
//A C PROGRAM TO IMPLEMENT THE H2O PROBLEM USING SEMAPHORES
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include "semlib.h"

sem_t smutex,oxyQueue,hydroQueue;

int oxygen=0,hydregen=0;

pthread_t oxyThread,hydroThread1,hydroThread2;

int bond(void){
    static int i=0;
    i++;
    if((i%3)==0)
        printf("** Molecule no. %d created**\n\n",i/3);
    sleep(2);
    return(0);
}

void* oxyFn(void* arg){

    while(1){
        sem_wait(&smutex);

        oxygen+=1;

        if(hydregen>=2){
            sem_post(&hydroQueue);
            sem_post(&hydroQueue);
            hydregen-=2;
            sem_post(&oxyQueue);
            oxygen-=1;
        }
        else {
            sem_post(&smutex);
        }

        sem_wait(&oxyQueue);
        printf("Oxygen Bond\n");
        bond();

        barrier_wait();
        sem_post(&smutex);
    }
}

void* hydroFn(void* arg){
    while(1){
        sem_wait(&smutex);

        hydregen+=1;

        if(hydregen>=2 && oxygen>=1){
            sem_post(&hydroQueue);
            sem_post(&hydroQueue);
            hydregen-=2;
            sem_post(&oxyQueue);
            oxygen-=1;
        }
        else{
            sem_post(&smutex);
        }

        sem_wait(&hydroQueue);

        printf("Hydrogen Bond\n");
        bond();

        barrier_wait();
        }

}

main(){

    if(sem_init(&smutex,0,1)==-1){
        perror("error initilalizing semaphore\n");
    }
    if(sem_init(&oxyQueue,0,0)==-1){
        perror("error initilalizing semaphore\n");
    }
    if(sem_init(&hydroQueue,0,0)==-1){
        perror("error initilalizing semaphore\n");
    }

    barrier(3);

    pthread_create(&oxyThread,0,oxyFn, NULL);
    pthread_create(&hydroThread1,0,hydroFn, NULL);
    pthread_create(&hydroThread2,0,hydroFn, NULL);

    for(;;);

}



