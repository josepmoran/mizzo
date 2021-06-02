#include "semaphore.h"
#include <pthread.h>
#include <queue>


typedef struct {
	char *name;
	int N;
	int miliseg;
	sem_t *MutexPtr; //Mutex semaphore
	sem_t *Frog;		//semaphore of frog
	sem_t *sTCandy;
	sem_t *sexitmain;
	sem_t *sfull;
	sem_t *sempty;
	int *Tcandy;
	 int *beltPtr;
	 int *consumerSlot;
	int *frogConsume;
	int *escargotConsume;




} CONSUMER_STRUCT;


void * consumer(void *VoidPtr);
