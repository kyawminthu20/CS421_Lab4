#include <stdio.h>
#include <pthread.h>	/* for pthread functions */
#include <stdlib.h>
#include <semaphore.h>
#define NUM_THREADS 5


/* the thread runs in this function */
void *runner(void *param);
void *producer(void *param);
void *consumer(void *param);

int main(int argc, char *argv[]) {

  int mainProgramSleep;
  int prodThreadCount, conThreadCount;
  int n = 10; //Buffer size
  sem_t mutex;
  sem_t empty;
  sem_t full;

  
  printf("\t=====================\n");
  printf("\tCS 421-01 Fall 2022\n");
  printf("\tKyaw Min Thu - gb6499\n");
  printf("\t=====================\n");

  printf("\targc     : %d\n", argc);
  printf("\targv[0]  : %s\n", argv[0]);

  printf("\n\t1. Get command line arguments\n");

  //mainProgramSleep = (int)argv[1];
  //prodThreadCount = (int)argv[2];
  //conThreadCount = (int)argv[3];

  mainProgramSleep = (int)argv[1];
  prodThreadCount = (int)argv[2];
  //conThreadCount = (int)argv[3];

  printf("\t\tThe length of time the program should run : %d\n", mainProgramSleep );
  printf("\t\tThe number of Producer Thread : %d\n", prodThreadCount );
  printf("\t\tThe length of Consumer Thread : %d\n", conThreadCount );

  printf("\n\t2. Initialize Buffer\n");

  int i;
	int localtid[NUM_THREADS];
	pthread_t tid[NUM_THREADS]; 	/* the thread identifier */
	pthread_attr_t attr; 		/* set of attributes for the thread */
  

	/* get the default attributes */
	pthread_attr_init(&attr);

  printf("\n\t3. Create producer threads.\n");
  /* create the threads */
	for (i = 0; i < NUM_THREADS; i++) { 
		localtid[i-1] = i;
		/* Note that we are passing the thread id by reference */
		pthread_create(&tid[i],&attr,producer,(void *) &localtid[i-1]); 
		printf("\t\t\tProducer: Created child %d with thread id = %lu\n", i, tid[i]);
  }


  printf("\n\t4. Create consumer threads.\n");

  	for (i = 0; i < NUM_THREADS; i++) { 
		localtid[i-1] = i;
		/* Note that we are passing the thread id by reference */
		pthread_create(&tid[i],&attr,consumer,(void *) &localtid[i-1]); 
		printf("\t\t\tConsumer: Created child %d with thread id = %lu\n", i, tid[i]);
  }

  printf("\n\t5. Sleep.\n");
  sleep(mainProgramSleep);

  printf("\n\t6. Main thread exits.\n");

	/**
	 * Now join on each thread
	 */
	printf("Main: Parent thread joining on all children\n");
	for (i = 0; i < NUM_THREADS; i++){ 
		pthread_join(tid[i], NULL);
	}

	printf("Main: Parent thread exiting\n");
	exit(0);
  return 0;
}

/**
 * The thread will begin control in this function.
 */
void *runner(void *tid) 
{
	int i;
	i = *((int *) tid);
	printf("Thread ID %d doing some work\n", i);

	/* do some work ... */

	pthread_exit(0);
}

void *producer(void *tid) 
{
  int item, timeToSleep;

  int i;
	i = *((int *) tid);
	printf("\t\tProducer Thread ID %d doing some work\n", i);
  timeToSleep = (rand() % 4) + 1;;
  sleep(timeToSleep);
  item = rand() % 10;
  printf("\t\tProducer produced %d\n", item);
  /*
  while(1){
    wait(empty);
    wait(mutex);
    

    signal(mutex);
    signal(empty);
    
  }
  */
  pthread_exit(0);
}

void *consumer(void *tid)
{
  int item, timeToSleep;

  int i;
	i = *((int *) tid);
	printf("\t\tConsumer Thread ID %d doing some work\n", i);
  timeToSleep = (rand() % 4) + 1;;
  sleep(timeToSleep);
  item = rand() % 10;
  printf("\t\tConsumer produced %d\n", item);
  /*
  while(1){
    wait(empty);
    wait(mutex);
    

    signal(mutex);
    signal(empty);
    
  }
  */
  pthread_exit(0);
  
}