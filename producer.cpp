#include <stdio.h>
#include <pthread.h>
#include "producer.h"
#include "semaphore.h"
#include <string.h>
#include <unistd.h>
#include "io.h"
//#include "io.c"

void * producer(void *VoidPtr)
	{
	int x=0;
	PRODUCER_STRUCT *producer = (PRODUCER_STRUCT *) VoidPtr;

	fflush(stdout);

	int tcandy=0;

	ProductType prod;


	while(*(producer->Tcandy) <100){

		sem_post(producer->sTCandy);

	  	if(producer->isFrog)///////If the candy is frog true, else escart
	  	{
		  	prod = FrogBite;

		  	sem_wait(producer->sempty);
		  	sem_wait(producer ->Frog);

			//begin critical section for producer frog
			sem_wait(producer-> MutexPtr);

			producer->beltPtr[*(producer->Tcandy)]=0;

			*(producer->Tcandy)= *(producer->Tcandy)+1;
			//x++;

			*(producer->frogProduce)= *(producer->frogProduce)+1;

			sem_post(producer-> MutexPtr);

			//sem_wait(producer ->Frog);

			sem_post(producer->sfull);


			//printf("consum frog:  %d\n",x);
			int produced [] = {*(producer->frogProduce),*(producer->escargotProduce)};
			io_add_type(prod,producer->beltPtr,produced);


			//End critical section for producer frog
			usleep(producer->miliseg*1000);
	  	}else{

			//  printf("This is the belt Line-----------  %s from %s  \n",*(producer->belt),producer->name );

			prod = Escargot;

			sem_wait(producer->sempty);
			//begin critical section for producer Escargot
			sem_wait(producer-> MutexPtr);



			producer->beltPtr[*(producer->Tcandy)]=1;
			//x++;
			//increment the total candy
			*(producer->Tcandy)= *(producer->Tcandy)+1;

			//increment the escargotcounter
			*(producer->escargotProduce)= *(producer->escargotProduce)+1;

			//printf("this if from %s %d\n",producer->name,x);

			sem_post(producer-> MutexPtr);

			sem_post(producer->sfull);
				
			int produced [] = {*(producer->frogProduce),*(producer->escargotProduce)};
			io_add_type(prod,producer->beltPtr,produced);
			//End critical section for producer Escargot

			usleep(producer->miliseg*1000);
	  	}


	fflush(stdout);

	}
	sem_post(producer->sTCandy);


}
