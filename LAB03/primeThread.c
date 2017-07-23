#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "functions.c"

void *threadedFunctionParametrized(void* _n)
{
    int num = (intptr_t)_n;
    return (void*)(intptr_t) isPrime(num, NUM_ITER);
}

int main( int argc, char *argv[] )
{
    int numbers[4], i;
	void* ret[4];
    if(parseArguments(argc, argv, numbers) < 0)
	{
    	printf("Not enough arguments\n");
		return -1;
	}

	pthread_t threadsParametrized[NUM_ARG];

	for(i= 0; i < NUM_ARG; i++ )
	{
		int rc = pthread_create(&threadsParametrized[i], NULL, threadedFunctionParametrized, (void *)(intptr_t) numbers[i]);
		if (rc)
		{
			printf("could not create thread %d\n", rc);
			return -1;
		}
	}

	int maxPrime = 0, nofPrime = 0;
	for(i= 0; i < NUM_ARG; i++ )
	{
		pthread_join(threadsParametrized[i], &ret[i]);
		if((intptr_t)ret[i]==1)
		{
			nofPrime++;
			if(maxPrime<numbers[i]) maxPrime = numbers[i];
		}
	}
	printf("%d\n", nofPrime);

	if(nofPrime>0)
	{
	   FILE *fp = fopen("prime", "w+");
	   fprintf(fp, "%d", maxPrime);
	   fclose(fp);
	}
}

