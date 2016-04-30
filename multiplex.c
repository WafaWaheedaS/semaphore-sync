#include <pthread.h>
#include <stdio.h>
#include "semlib.h"

void *thr_fn(void *arg);

int main(){

fprintf(stderr,"Main start\n");

int numThreads=5;
int allowedThr=3;
int i;

pthread_t thread[numThreads];

multiplex(allowedThr);

for (i=0;i<numThreads;i++){
    if(pthread_create(&thread[i], NULL, thr_fn, NULL)==-1){
        printf("Error Creating thread a.\n");
    }
}

for (i=0;i<numThreads;i++){
    pthread_join(thread[i], NULL);
}


}

void *thr_fn(void *arg){

multiplex_wait();

printf("I am thread %u: Entering critical section\n",(unsigned)pthread_self());
sleep(2);

multiplex_signal();
printf("%u: Exiting critical section.\n",(unsigned)pthread_self());
return((void *)0);//return(NULL);
}
