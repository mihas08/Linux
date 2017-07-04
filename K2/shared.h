//
// shared.h
//

#ifndef __SHARED2__
#define __SHARED2__
#include <sys/sem.h>

struct sem_str {
  int semid;
  short init[1];
  struct sembuf p, v;
};

typedef struct sem_str *sem_t;  

void *getmem (int i);

sem_t sem_init(int i);
void sem_set(sem_t s, int value);
void PS(sem_t s);
void VS(sem_t s);
void sem_remove(sem_t s);
#endif
