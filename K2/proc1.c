#include "shared.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
	int *common,r;
	int t;
	int *countIter;
	srand(time(NULL));
	sem_t A;
	sem_t B;
        sem_t C;
	sem_t mutex;
	countIter = (int*)getmem(3250);
	common = (int*)getmem(3249);
	mutex = sem_init(3245);
	A = sem_init(3248);
	B = sem_init(3247);
        C = sem_init(3246);
	while(1)
	{
		r = rand() %100 +1;
		PS(A);
		PS(mutex);
		*common = r;
		t = *countIter;
		VS(mutex);
		VS(B);
		if(t==0)break;
	}
	printf("\n Process 1 completed!");
return 0;
}
