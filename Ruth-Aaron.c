/*
	Author:  Darrin Schmitz
	Date:    11/28/2015
	
	This is a multithreaded program that finds Ruth-Aaron Pairs.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <pthread.h>

#define PRIMES 10000000    // Size of seive 
#define THNUMS 15          // Number of threads
#define PAIRS 1000000      // How many pairs to check. 

#define BLOCK_LOW(id, p, n)	((id)*(n)/(p))
#define BLOCK_HIGH(id, p, n)	(BLOCK_LOW((id)+1,p,n)-1)

// Thread parametes
struct ThreadParams
{ 
	int id;				   // id
	int low;			   // start
	int high;		   	   // end
	int *structprimes;     // each thread's seive
};

// Function prototypes
void *Work(void *arg);

int main()
{
//-----Timing the Program-----
	clock_t begin;
	clock_t end;
	double time_spent;
	begin = clock();
	
	struct timespec start, finish;
	double elapsed;
	clock_gettime(CLOCK_MONOTONIC, &start);
//-----------------------------


	struct ThreadParams ptharg[THNUMS];
	int i = 0; //First number in pair
	int i2 = 1; //Second number in pair
	pthread_t tid;
	void *status;

	unsigned long long int a,b;
    int *primes;
	primes = malloc(sizeof(int)*PRIMES);
	for(a = 2; a <PRIMES; a++)//Set every element in the array to 1
        primes[a] = 1;
	
	for(a = 2; a < PRIMES; a++)//Place a 0 in the elements that are not primes
        if(primes[a])
            for(b = a; a * b < PRIMES; b++)
                primes[a * b] = 0;

	for (a = 0; a < THNUMS; a++)// Copy the sieve to each threads array.
		ptharg[a].structprimes = malloc(sizeof(int)*PRIMES);
	
			
	for (i = 0; i < THNUMS; i++)
	{
		ptharg[i].id = i;
		ptharg[i].low = BLOCK_LOW(i, THNUMS, PAIRS);
		ptharg[i].high = BLOCK_HIGH(i, THNUMS, PAIRS);
		memcpy(ptharg[i].structprimes, primes, sizeof(int)*PRIMES);

		printf("ID=%d   LOW=%d   HIGH=%d\n", ptharg[i].id, ptharg[i].low, ptharg[i].high);
		
		
		if (pthread_create(&tid, NULL, Work, (void*)&ptharg[i]) != 0)
		{
			perror("error creating child");
			return -1;
		}

		//pthread_join(tid, &status);
		if (i == THNUMS-1) pthread_join(tid, &status);
	}

	
//-----Timing the Program-----
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Using clock() %lf\n", time_spent);
	
	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	printf("Using clock_gettime() %f\n", elapsed);
//----------------------------
	
	return 0;
}

void *Work(void *arg)
{
	int x;
	int y;
	int total1;
	int total2;
	int other_factor;
	
	struct ThreadParams *pm = (struct ThreadParams*)arg; //Making local Struct and assigning it to passed in struct. 
	
	int i;
	int i2;
	for(i = pm->low, i2 = i++; i < pm->high; i++, i2++)
	{	
		total1 = 0;
		total2 = 0;
		for(x = 2; x <= sqrt(i) + 1; x++)
		{
			if(i % x == 0) //if it is a factor
			{
				other_factor = i / x; 
				
				if(pm->structprimes[x] == 1)//if its in the seive its a prime
					total1 = x + total1;
					
				if(pm->structprimes[other_factor] == 1)
					total1 = other_factor + total1;
			}
		}

		for(x = 2; x <= sqrt(i2) + 1; x++)
		{
			if(i2 % x == 0) //if it is a factor
			{
				other_factor = i2 / x;
				
				if(pm->structprimes[x] == 1)//if its in the seive its a prime
					total2 = x + total2;
				
				if(pm->structprimes[other_factor] == 1)
					total2 = other_factor + total2;
			}
		}
		
		if(total1 == total2)
			printf("From thread ID: %d  | These two are a Ruth-Aaron pair: %d, %d\n", pm->id, i2, i); // Gets switched some how?
	}
}
