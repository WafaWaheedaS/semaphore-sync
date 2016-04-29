
#include<pthread.h>
#include<stdio.h>
#include</home/wafa/semt1/semlib.h> // importing the library for synchronisation using semaphores from path

void *thrA_fn(void *arg);
void *thrB_fn(void *arg);

int main(){

fprintf(stderr,"Rendezvous start..\n");

pthread_t a;  // creating thread 1 & 2 using pthread.h 
pthread_t b;

rendezvous(); // calling rendezvous function from semlib.h

if( pthread_create(&a, NULL, thrA_fn, NULL)==-1){
	// using pthread.h function create for creating thread 1
    printf("Error Creating thread a.\n");
}

if( pthread_create(&b, NULL, thrB_fn, NULL)==-1){
    // using pthread.h function create for creating thread 2
    printf("Error Creating thread b.\n");
}

pthread_join(a, NULL); // using pthread.h join --- tells processor main to wait for threads to finsh executing..
    
pthread_join(b,NULL);

fprintf(stderr,"Main end\n");

}

void *thrA_fn(void *arg){
printf("I am thread A, now waiting for the other thread\n");
//sem_post(&aArrived);
//sem_wait(&bArrived);
rendez_a_wait(); // using semlib.h fn to wait for thread1

printf("I am thread A, finished all tasks.\n");
return((void *)0);//return(NULL);
}

void *thrB_fn(void *arg){
printf("I am thread B, now waiting for the other thread\n");
//sem_post(&bArrived);
//sem_wait(&aArrived);
rendez_b_wait();

printf("I am thread B, finished all tasks.\n");
return((void *)0);//return(NULL);
}
