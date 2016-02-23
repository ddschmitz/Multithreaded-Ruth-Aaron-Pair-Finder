/*
	Author:  Darrin Schmitz
	Date:    11/28/2015
	
	A multithreaded Ruth-Aaron pair finder written in C.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <pthread.h>

#define PRIMES 10000000    // Size of sieve.
#define THNUMS 15          // Number of threads.
#define PAIRS 1000000      // How many pairs to check. 

// Thread parametes
struct ThreadParams
{ 
	int id;				   // Each thread's id.
	int low;			   // Where each thread begins checking for pairs.
	int high;		   	   // Where each thread stops checking for pairs.
	int *structprimes;     // Each thread's sieve.
};

// Function prototypes
void *Work(void *arg);
int lowerBound(int threadId, int thnums, int pairs);
int higherBound(int threadId, int thnums, int pairs);

int main(void)
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
	pthread_t tid;
    void *status;

    // Create a Sieve of Eratosthenese which we will use to check if a number is prime.
    unsigned long long int a,b;
    int *primes;
    primes = malloc(sizeof(int)*PRIMES);
    for(a = 2; a <PRIMES; a++)
        primes[a] = 1;
    for(a = 2; a < PRIMES; a++)
        if(primes[a])
            for(b = a; a * b < PRIMES; b++)
                primes[a * b] = 0;

	for (a = 0; a < THNUMS; a++)// Copy the sieve to each threads array.
		ptharg[a].structprimes = malloc(sizeof(int)*PRIMES);
	
	int i;
	for (i = 0; i < THNUMS; i++)
	{
		ptharg[i].id = i;
		ptharg[i].low = lowerBound(i, THNUMS, PAIRS);// Where the specified thread (with id i) will start checking.
		ptharg[i].high = higherBound(i, THNUMS, PAIRS);// Where the specified thread (with id i) will stop checking.
		memcpy(ptharg[i].structprimes, primes, sizeof(int)*PRIMES);

		printf("ID=%d   LOW=%d   HIGH=%d\n", ptharg[i].id, ptharg[i].low, ptharg[i].high);
		
		if (pthread_create(&tid, NULL, Work, (void*)&ptharg[i]) != 0)
		{
			perror("error creating child");
			return -1;
		}

		if (i == THNUMS-1)
            pthread_join(tid, &status);
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

int lowerBound(int threadId, int thnums, int pairs)
{
	return threadId * pairs / thnums;
}

int higherBound(int threadId, int thnums, int pairs)
{
	return lowerBound(threadId + 1, thnums, pairs) - 1;
}

void *Work(void *arg)
{
	int pair1;// First number in pair.
	int pair2;// Second number in pair.
	int i;
	int total1;
	int total2;
	int other_factor;
	
	struct ThreadParams *pm = (struct ThreadParams*)arg; // Making local Struct and assigning it to passed in struct. 
	
	for(pair1 = pm->low, pair2 = pair1++; pair1 < pm->high; pair1++, pair2++)
	{	
		total1 = 0;
		total2 = 0;
		for(i = 2; i <= sqrt(pair1) + 1; i++)
		{
			if(pair1 % i == 0)// If it is a factor.
			{
				other_factor = pair1 / i;// Find the other factor using the first one.
				
				if(pm->structprimes[i] == 1)// If its in the sieve its a prime.  Also add it to the total.  Do the same with the other factor.
					total1 = i + total1;
					
				if(pm->structprimes[other_factor] == 1)// Do the same with the other factor.
					total1 = other_factor + total1;
			}
		}

		for(i = 2; i <= sqrt(pair2) + 1; i++)
		{
			if(pair2 % i == 0)// If it is a factor.
			{
				other_factor = pair2 / i;// Find the other factor using the first one.
				
				if(pm->structprimes[i] == 1)// If its in the sieve its a prime.  Also add it to the total.
					total2 = i + total2;
				
				if(pm->structprimes[other_factor] == 1)// Do the same with the other factor.
					total2 = other_factor + total2;
			}
		}
		
		if(total1 == total2)
			printf("From thread ID: %3d | These two are a Ruth-Aaron pair: %d, %d\n", pm->id, pair2, pair1); // Gets switched some how?
	}
}
