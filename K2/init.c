#include "shared.h"
#include <stdio.h>

int main(int argc, char** argv)
{                                    
	sem_t A;
	sem_t B;
        sem_t C;
	sem_t mutex;
	mutex = sem_init(3245);
	A = sem_init(3248);
	B = sem_init(3247);
        C = sem_init(3246);
	int *common;                      // деклариране на общи променливи за
	int *countIter;                  // предаване на данни и брояч на интерации
	countIter = (int*)getmem(3250);
	*countIter = 100;
	sem_set(mutex,1);               
	sem_set(A,1);
	sem_set(B,0);
        sem_set(C,0);
	common = (int*)getmem(3249);
	printf("    Initialised! %d \n",*countIter);
	return 0;
}
	
