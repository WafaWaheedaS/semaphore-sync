#include <pthread.h>
#include <stdio.h>
#include "semlib.h"

void *thr_fn(void *arg);

int numThreads=5;
int numTask=5;

int main(){

int i;

pthread_t thread[numThreads];

barrier(numThreads);

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

int j=0;

for(j=0;j<numTask;j++){
printf("I am thread %u: finishing task %d\n",(unsigned)pthread_self(),j);
sleep(2);
printf("I am thread %u: waiting at barrier\n",(unsigned)pthread_self());
barrier_wait();
}
printf("I am thread %u:finished all tasks...\n",(unsigned)pthread_self());
return((void *)0);//return(NULL);
}

