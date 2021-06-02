#include <stdio.h>
#include "semaphore.h"
#include <pthread.h>
void * producer(void *VoidPtr);
typedef struct {
	char *name;
	int N;
	int miliseg;
	sem_t *MutexPtr;  //Mutex semaph
	sem_t *Frog;       //Frog semaph
	sem_t *sTCandy;     //total candy semaph
	sem_t *sfull; //
	sem_t *sempty; //
	int *Tcandy;
	bool isFrog;        //bolean to producer to know if is frog or escargot
	 int frogonbelt;
	 int escargotonbelt;
	 int *beltPtr;
	 int *frogProduce;
	int *escargotProduce;


} PRODUCER_STRUCT;