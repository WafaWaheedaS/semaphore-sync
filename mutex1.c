#include<pthread.h>
#include<stdio.h>
#include</home/haya/semt1/semlib.h>

void *thr_fn(void *arg);

int count = 0 ;

int main(){

fprintf(stderr,"Main start\n");

int numThreads=3;
int i,j;

pthread_t thread[numThreads];

mutex();

for (i=0;i<numThreads;i++){
    if(pthread_create(&thread[i], NULL, thr_fn, NULL)==-1){
        printf("Error Creating thread a.\n");
    }
}

for (j=0;j<numThreads;j++){
    pthread_join(thread[j], NULL);
}


}

void *thr_fn(void *arg){

mutex_wait();

count++;
printf("%d: Entering critical section\n",count);
mutex_signal();
printf("Exiting critical section.\n");
return((void *)0);//return(NULL);
}
