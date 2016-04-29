#include<semaphore.h>   // using semaphore headerfile to create functions for synchronization problems using semaphore..

sem_t aArrived;
sem_t bArrived;

//***Rendezvous Functions ***
void rendezvous(){
    //initializes semaphore and does error handling
    if(sem_init(&aArrived,0,0)==-1){
        perror("error initilalizing semaphore for rendezvous\n");
    }
    if (sem_init(&bArrived,0,0)==-1){
        perror("error initilalizing semaphore for rendezvous\n");
    }
}

void rendez_a_wait(){
    //rendezvous thread 1 wait
    sem_post(&aArrived);
    sem_wait(&bArrived);
}


void rendez_b_wait(){
    //rendezvous thread 2 wait
    sem_post(&bArrived);
    sem_wait(&aArrived);
}


//*** Mutex Functions ***

sem_t smutex;

void mutex(){
    if(sem_init(&smutex,0,1)==-1){
        perror("error initilalizing semaphore for mutex\n");
    }
}

void mutex_wait(){
    sem_wait(&smutex);
}

void mutex_signal(){
    sem_post(&smutex);
}



//*** Multiplex Functions ***
sem_t smultiplex;

void multiplex(int n){

    if(sem_init(&smultiplex,0,n)==-1){
        perror("error initilalizing semaphore for multiplex\n");
    }
}

void multiplex_wait(){
    sem_wait(&smultiplex);
}

void multiplex_signal(){
    sem_post(&smultiplex);
}



//*** Queues Functions***
sem_t slqueues;
sem_t sfqueues;
sem_t sqmutex;
sem_t sqrend;

int fcount, lcount;

void queues(){
    fcount = 0;
    lcount = 0;

    if(sem_init(&slqueues,0,0)==-1){
        perror("error initilalizing semaphore for leader queues\n");
    }    
    if(sem_init(&sfqueues,0,0)==-1){
        perror("error initilalizing semaphore for queues\n");
    }    
    if(sem_init(&sqmutex,0,1)==-1){
        perror("error initilalizing semaphore for queues\n");
    }
    if(sem_init(&sqrend,0,0)==-1){
        perror("error initilalizing semaphore for queues\n");
    }
}

void lqueues_wait(){
    sem_wait(&sqmutex);
    if(fcount>0){
        fcount--;
        sem_post(&sfqueues);
    }
    else{
        lcount++;
        sem_post(&sqmutex);
        sem_wait(&slqueues);
    }
}
void lqueues_signal(){
    sem_wait(&sqrend);
    sem_post(&sqmutex);

}

void fqueues_wait(){
    sem_wait(&sqmutex);
    if(lcount>0){
        lcount--;
        sem_post(&slqueues);
    }
    else{
        fcount++;
        sem_post(&sqmutex);
        sem_wait(&sfqueues);
    }
}

void fqueues_signal(){
    sem_post(&sqrend);
}
33333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333



//*** Barrier ***


sem_t smultiplex;

void multiplex(int n){

    if(sem_init(&smultiplex,0,n)==-1){
        perror("error initilalizing semaphore for multiplex\n");
    }
}

void multiplex_wait(){
    sem_wait(&smultiplex);
}

void multiplex_signal(){
    sem_post(&smultiplex);
}






//*** FIFO Queues ***


/** imp 3 - queue handling for fifo 

sem_t sqmutex2;

int pos;
void queues2(int queueSize){
    pos = 0;

    if(sem_init(&sqmutex2,0,1)==-1){
        perror("error initilalizing semaphore for queues\n");
    }
}

void squeues2_wait(sem_t mySem){
    sem_wait(&sqmutex2);
    squeues2[pos]=mySem;
    pos++;
    sem_post(&sqmutex2);
    sem_wait(mySem);
}


void squeues2_signal(){
    sem_wait(&sqmutex2);
    sem_t sem;
    pos--;
    sem=squeues2[pos];

    sem_post(&sqmutex2);
    sem_post(sem);

}
**/







/** imp 2 **
sem_t squeues2[100];
sem_t sqmutex2;

int pos;
void queues2(){
    pos = 0;

    if(sem_init(&sqmutex2,0,1)==-1){
        perror("error initilalizing semaphore for queues\n");
    }
}

void squeues2_wait(){

    sem_t mySem;

    if(sem_init(&mySem,0,0)==-1){
        perror("error initilalizing semaphore for queues\n");
    }

    printf("queue  wait - after if init..\n");
    sem_wait(&sqmutex2);
    printf("queue mutex waited....\n");
    squeues2[pos] = mySem;
    pos++;
    printf("queue mutex posted....\n");
    sem_post(&sqmutex2);
    printf("q outside mutex posted...\n");
    sem_wait(&mySem);   // hangs here.. 
    printf("queue SEM waited....\n");
}


void squeues2_signal(){
    sem_wait(&sqmutex2);
    sem_t sem;
    pos--;
    sem=squeues2[pos];

    sem_post(&sqmutex2);
    sem_post(&sem);

}


****imp 1 ***

sem_t squeues2[];
sem_t sqmutex2;

int pos;
void queues2(int queueSize){
    pos = 0;

    if(sem_init(&sqmutex2,0,1)==-1){
        perror("error initilalizing semaphore for queues\n");
    }
}

void squeues2_wait(sem_t mySem){
    sem_wait(&sqmutex2);
    squeues2[pos]=mySem;
    pos++;
    sem_post(&sqmutex2);
    sem_wait(mySem);
}


void squeues2_signal(){
    sem_wait(&sqmutex2);
    sem_t sem;
    pos--;
    sem=squeues2[pos];

    sem_post(&sqmutex2);
    sem_post(sem);

} **/

