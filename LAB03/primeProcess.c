#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "functions.c"

int main( int argc, char *argv[] )
{
    int numbers[4], i;
	int ret[4];
    if(parseArguments(argc, argv, numbers) < 0)
	{
    	printf("Podaj 4 argumenty\n");
		return -1;
	}

	pid_t pid;
	int maxPrime = 0, nofPrime = 0;
	for (i=0; i<NUM_ARG; i++)
	{
		pid = fork();
		if (pid == -1) return -1;
		else if (pid > 0)
		{
			int val;
			wait(&val); 
			if(WEXITSTATUS(val)==1)
			{
				nofPrime++;
				if(maxPrime<numbers[i]) maxPrime = numbers[i];
			}
		}
		else 
		{
			int val = isPrime(numbers[i], NUM_ITER);
			exit(val);
		}
	}

	printf("%d\n", nofPrime);

	if(nofPrime>0)
	{
	   FILE *fp = fopen("primeProc", "w+");
	   fprintf(fp, "%d", maxPrime);
	   fclose(fp);
	}
}

