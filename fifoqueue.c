#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>


void *thr_fn(void *arg);
void *server_fn(void *arg);  // controller for ordering - calling threads in fifo order

sem_t squeues2[100];
sem_t sqmutex2;
int pos, count=0;
int numThreads=5;
int main(){

fprintf(stderr,"FIFO Queue starts\n");


int i;
pthread_t thr[numThreads], serverThr;  // creating threads using pthread.h
count=0;
pos = 0;

    if(sem_init(&sqmutex2,0,1)==-1){
        perror("error initilalizing semaphore for queues\n");
    }

printf("Creating threads ....\n");
for (i=0;i<numThreads;i++){
    if(pthread_create(&thr[i], NULL, thr_fn, NULL)==-1){
        printf("Error Creating thread a.\n");
    }
    // printf("Created a thread %u successfully \n", (unsigned)pthread_self());
}

if(pthread_create(&serverThr, NULL, server_fn, NULL)==-1){
        printf("Error Creating thread..\n");
    }

for (i=0;i<numThreads;i++){
    pthread_join(thr[i], NULL);
}

} // closing main

void squeues2_signal(){
    sem_wait(&sqmutex2);
    sem_t sem;
    pos--;
    sem=squeues2[pos];
    sem_post(&sqmutex2);
    sem_post(&sem);

}

void squeues2_wait(sem_t mySem){

    sem_wait(&sqmutex2);
    squeues2[pos]=mySem;
    pos++;
    sem_post(&sqmutex2);
   // printf("printing sem.. %s", mySem);
    sem_wait(&mySem);

}


void *server_fn(void *arg){
	while(count<numThreads){
	while(pos != 0){
        count++;
		squeues2_signal();
		printf("finished processing thread %u..\n",(unsigned)pthread_self() );
	}}
	return((void *)0);//return(NULL);
}

void *thr_fn(void *arg){
	sem_t mySem;
    if(sem_init(&mySem,0,0)==-1){
        perror("error initilalizing semaphore for queues\n");
    }

    printf("Created a thread %u successfully \n", (unsigned)pthread_self());
    squeues2_wait(mySem);
    return((void *)0);//return(NULL);
}
