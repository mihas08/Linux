#include "shared.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv)
{    
    FILE* fp;               
	int *common,i,r;
	int *countIter;
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
	fp = fopen("output.dat","w");      
	                                
	while(1)                             
	{	
		PS(C);                       
		PS(mutex);
		r = *countIter;                     
		i = *common;                           
        	printf("\n Read %d -> %d\n",r,i);
		r = r -1;
		*countIter = r;
		fprintf(fp, " %d \n" ,i);
		VS(mutex);
		VS(A);               
		if(r==0)break;          
	}
	fclose(fp);                          	
	printf("\n Process 3 completed!");
	return 0;
}
