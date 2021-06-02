

#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include "semaphore.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "io.h"
#include "producer.h"
#include "consumer.h"
#include <queue>

using namespace std;

int main(int argc, char **argv)	{

	// Initializing structs for consumers and producers
	CONSUMER_STRUCT Lucy ;
	CONSUMER_STRUCT Ethel;
	PRODUCER_STRUCT frog;
	PRODUCER_STRUCT escargot;

	// Initialization for structure contents
	sem_t mutex, sfrog, stcandy, sexit;
	sem_t sempty, sfull;
	pthread_attr_t	pthread_attributes; // Initializing pthread attributes
	char Option;	// For parsing input
	int milisec;
	int indexargv=0;
	int tcandy;
	int belt[100];	// Belt array containing 100 entries
	tcandy =0;
	int i;
	int frogconsume=0;
	int escargotconsume=0;
	int frogproduce=0;
	int escargotproduce=0;
	int consumerslot=0;

	// Initializing the belt entries to -1 until it gets filled with 0 (CFB) or 1 (EES)
	for (i =0 ; i <100; i++) {
		belt[i]= -1;
	}

	// Initialize elements of Lucy consumer struct
	Lucy.MutexPtr= &mutex;
	Lucy.miliseg = 0;
	Lucy.N = 43;
	Lucy.name ="Lucy";
	Lucy.Frog = &sfrog;
	Lucy.Tcandy = &tcandy;
	Lucy.sTCandy = &stcandy;
	Lucy.sexitmain = &sexit;
	Lucy.beltPtr =belt;
	Lucy.consumerSlot = &consumerslot;
	Lucy.escargotConsume=&escargotconsume;
	Lucy.frogConsume=&frogconsume;
	Lucy.sfull = &sfull;
	Lucy.sempty =&sempty;

	// Initializing elements of Ethel consumer struct
	Ethel.MutexPtr= &mutex;
	Ethel.miliseg = 0;
	Ethel.N = 43;
	Ethel.name ="Ethel";
	Ethel.Frog = &sfrog;
	Ethel.Tcandy = &tcandy;
	Ethel.sTCandy = &stcandy;
	Ethel.sexitmain = &sexit;
	Ethel.beltPtr =belt;
	Ethel.consumerSlot = &consumerslot;
	Ethel.escargotConsume=&escargotconsume;
	Ethel.frogConsume=&frogconsume;
	Ethel.sfull = &sfull;
	Ethel.sempty =&sempty;

	// Initializing elements of  Frog producer struct
	frog.MutexPtr= &mutex;
	frog.miliseg = 0;
	frog.N = 43;
	frog.name ="frog";
	frog.Frog = &sfrog;
	frog.isFrog = true;
	frog.Tcandy = &tcandy;
	frog.sTCandy = &stcandy;
	frog.beltPtr =belt;
	frog.escargotProduce=&escargotproduce;
	frog.frogProduce=&frogproduce;
	frog.sfull = &sfull;
	frog.sempty =&sempty;

	// Initialize elements of Escargot producer struct
	escargot.MutexPtr= &mutex;
	escargot.miliseg = 0;
	escargot.N = 43;
	escargot.name ="escargot";
	escargot.Frog = &sfrog;
	escargot.isFrog = false;
	escargot.Tcandy = &tcandy;
	escargot.sTCandy = &stcandy;
	escargot.beltPtr =belt;
	escargot.escargotProduce=&escargotproduce;
	escargot.frogProduce=&frogproduce;
	escargot.sfull = &sfull;
	escargot.sempty =&sempty;

	//Init each semaphore
	//sem_init(&unconsumed,0,0);
	//sem_init(&availableSlots,0,10);
	sem_init(&sfull,0,0); //sfull = 0 beltslot full size
	sem_init(&sempty,0,10); //sempty = 10 beltslot empty size

	sem_init(&mutex,0,1); //mutex = 1
	sem_init(&sfrog,0,3); //sfrog = 3
	sem_init(&stcandy,0,0); //semaphore total candy = 10

	sem_init(&sexit,0,0);//semaphore exit of the program = 0

    //To run the getopt accept parameters for the different tags -E -L -f -e
    while ((Option = getopt(argc, argv, "E:L:f:e:")) != -1){
        switch (Option){
             case 'E':

			    Ethel.miliseg = atoi(optarg);
				break;

             case 'L':

				Lucy.miliseg = atoi(optarg);
				break;

			case 'f':

				frog.miliseg =  atoi(optarg);
		  		break;

		    case 'e':

			    escargot.miliseg = atoi(optarg);
		  		break;


            default:
	          	cout<<"Exit the arguments";
                exit(1);


        }
	}


	pthread_t Lucy_t, Ethel_t, frog_t,escargot_t;



	pthread_attr_init(&pthread_attributes);


	// Invoking the consumer threads
	//Invoke Lucy before Ethel
	pthread_create( &Lucy_t, &pthread_attributes,
				&consumer, (void *) &Lucy);

	pthread_create( &Ethel_t, &pthread_attributes,
			  	&consumer, (void *) &Ethel);

	// Invoking the producer threads
	//Invocke Frog bite candy first
	pthread_create(&frog_t, &pthread_attributes,
				&producer,  (void *) &frog);

	pthread_create(&escargot_t, &pthread_attributes,
				&producer,  (void *) &escargot);



	sem_wait(&sexit); //exit when consumers finish
	sem_wait(&sexit);//exit when second consumers finish

	int produced[] = {*(frog.frogProduce),*(escargot.escargotProduce)};

	int lucyArray[] = {*(Lucy.frogConsume),*(Lucy.escargotConsume)};
	int ethelArray[] = {*(Ethel.frogConsume),*(Ethel.escargotConsume)};

	int *consumed[] = {lucyArray,ethelArray};

	io_production_report(produced,consumed);

	exit(0);
}
