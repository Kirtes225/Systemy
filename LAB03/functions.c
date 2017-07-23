#define NUM_ARG 4
#define NUM_ITER 1000000

int mod(int a,int b,int c);
int mul(int a,int b,int c);
int isPrime(int p,int it);
int parseArguments(int argc, char* argv[], int num[]);

int mod(int a,int b,int c)
{
    int x=1,y=a; 
    while(b > 0)
	{
        if(b%2 == 1) x=mul(x,y,c);
        y = mul(y,y,c); 
        b /= 2;
    }
    return x%c;
}
 
int mul(int a,int b,int c)
{
    int x = 0,y=a%c;
    while(b > 0)
	{
        if(b%2 == 1) x = (x+y)%c;
        y = (y*2)%c;
        b /= 2;
    }
    return x%c;
}
 
int isPrime(int p,int it)
{
    if(p<2) return 0;
    if(p!=2 && p%2==0) return 0;
    int s=p-1;
    while(s%2==0) s/=2;

    int i;
    for(i=0;i<it;i++)
	{
        int a=rand()%(p-1)+1,tt=s;
        int md=mod(a,tt,p);
        while(tt!=p-1 && md!=1 && md!=p-1)
		{
            md=mul(md,md,p);
            tt *= 2;
        }
        if(md!=p-1 && tt%2==0) return 0;
    }
    return 1;
}

int parseArguments(int argc, char* argv[], int num[])
{
    if(argc != 5) return -1;
    int i;
    for(i = 0; i<NUM_ARG; i++)
        num[i] = atoi(argv[i+1]);
    return 0;
}
