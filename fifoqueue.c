#include<semaphore.h>
#include<pthread.h> //debate
#include<stdio.h>


// #include</home/wafa/semt1/semlib.h> // importing the library for synchronisation using semaphores from path


void *thr_fn(void *arg);
void *server_fn(void *arg);

sem_t squeues2[100];
sem_t sqmutex2;
int pos;

int main(){

fprintf(stderr,"Queues start..\n");

int numThreads=5;
int i;
pthread_t thr[numThreads], serverThr;  // creating threads using pthread.h 

pos = 0;

    if(sem_init(&sqmutex2,0,1)==-1){
        perror("error initilalizing semaphore for queues\n");
    }
 // calling rendezvous function from semlib.h
printf("starting for ....\n");
for (i=0;i<numThreads;i++){
    if(pthread_create(&thr[i], NULL, thr_fn, NULL)==-1){
        printf("Error Creating thread a.\n");
    }
}

if(pthread_create(&serverThr, NULL, server_fn, NULL)==-1){
        printf("Error Creating thread a.\n");
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
	pos++;
 	sem_wait(&sqmutex2);
    squeues2[pos]=mySem;
    printf("printging pos:%d", pos);    
    sem_post(&sqmutex2);
    printf("sem wait entering...\n");
   // printf("printing sem.. %s", mySem);
    sem_wait(&mySem);
    printf("sem wait exiting...\n");

}

void *server_fn(void *arg){
	while(pos != 0){
		squeues2_signal();
		printf("finish processing thread..\n");
	}
}

void *thr_fn(void *arg){
printf("starting thread fn....\n");

	sem_t mySem;

    if(sem_init(&mySem,0,0)==-1){
        perror("error initilalizing semaphore for queues\n");
    }
squeues2_wait(mySem);
    /**sem_wait(&sqmutex2);
    squeues2[pos]=mySem;
    pos++;
    sem_post(&sqmutex2);
    printf("sem wait entering...\n");
    sem_wait(&mySem);
    printf("sem wait exiting...\n"); **/

printf("Executing queue -- i am entering.. \n");
//squeues2_signal();

printf("Executing queue -- i am exit.. \n");
}
