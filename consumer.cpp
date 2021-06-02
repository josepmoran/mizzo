#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include "consumer.h"
#include "semaphore.h"
#include <string.h>
#include "io.h"
#include <unistd.h>
#include <string>

typedef enum UnumName {
	enumval1,enunval2
} EnumType;

void * consumer(void *VoidPtr){

	ConsumerType cons;
	ProductType prod;

	int x=0;

	//Type cast

	CONSUMER_STRUCT *consumer = (CONSUMER_STRUCT *) VoidPtr;

	fflush(stdout);

	while (*(consumer->consumerSlot )<100){

		sem_wait(consumer->sfull);
	  //sem_wait(consumer->sTCandy);
	  //critical section begin

	  sem_wait(consumer-> MutexPtr);

	  sem_post(consumer->sempty);

	   //check the candy is frog or escargot
	   if (consumer->beltPtr[*(consumer->consumerSlot )]==0)
	   {
		   prod = FrogBite;
	   *(consumer->frogConsume)= *(consumer->frogConsume)+1;
	   sem_post(consumer->Frog);

	   }else{
		   prod = Escargot;
	   *(consumer->escargotConsume)= *(consumer->escargotConsume)+1;
	   }

	   //consume the candy from belt = 2
	   consumer->beltPtr[*(consumer->consumerSlot )]=2;

	   //consume the candy
	   *(consumer->consumerSlot ) =  *(consumer->consumerSlot )+1;

		 //consumer->beltPtr[*(producer->Tcandy)]=1;
	  //printf("Total candies %d  this is from %s \n", *(consumer->Tcandy), consumer->name);


	  //sem_post(consumer->Frog);

		std::string consname = (consumer->name);

		if (consname.compare("Lucy") == 0){
			cons = Lucy;
		}else{
			cons = Ethel;
		}

	  sem_post(consumer-> MutexPtr);

	  //critical section End

	  usleep(consumer->miliseg*1000);

		int consumed [] = {*(consumer->frogConsume),*(consumer->escargotConsume)};
		io_remove_type(cons,prod,consumer->beltPtr,consumed);
	  }


	  fflush(stdout);

	  //printf("Belt: %d\n",*(consumer->belt));

	  //exit of consumer increment semaphore sexitmain
	  sem_post(consumer-> sexitmain);

	  //printf(" TOTAL frog %d, total escarlet %d from %s\n",*(consumer->frogConsume),*(consumer->escargotConsume),consumer->name);
	  //printf("Exit consumer\n");

}
