//
// shared.c
// Routines:
//	- getmem (common memory)
//	- TestAndSet
//	- Semaphore operations P and V
//	  semaphores are implemented with pointers

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdlib.h>

#define SEMKEY 88
#define SHMSIZE 64


//
// ========================= Shared memory =====================
//

void * getmem (int i){
int shmid;

  shmid = shmget(70+i, SHMSIZE, IPC_CREAT|0666);
  return shmat(shmid,0,0);
}

//
// ======================== Semaphore operations ==========================
//


int shmid, semid;
int i, *pint, status, id;

short out[1],
      oldval;

struct sem_str {
  int semid;
  short init[1];
  struct sembuf p, v;
};

typedef struct sem_str *sem_t;  

sem_t sem_init(int i)
{ sem_t s;
  
  s = (sem_t) malloc(sizeof(struct sem_str));
  s->semid = semget(SEMKEY+i,1,IPC_CREAT|0777);

  s->p.sem_num = 0;
  s->p.sem_op = -1;
  s->p.sem_flg = 0;

  s->v.sem_num = 0;
  s->v.sem_op = 1;
  s->v.sem_flg = 0;

  return s;
}

void sem_set(sem_t s, int value)
{  
  s->init[0]=value;
  semctl(s->semid,1,SETALL,s->init);
}

void PS(sem_t s)
{
  int oldval;
  
  oldval = semop(s->semid,&(s->p),1);
}

void VS(sem_t s)
{
  int oldval;
  
  oldval = semop(s->semid,&(s->v),1);
}

void sem_remove(sem_t s)
{
  semctl(s->semid,1,IPC_RMID,0);
  free(s);
}

//
// ===================== TestAndSet ============================
//

//static __inline__
int testandset(volatile int *spinlock)
{
  int ret;
  
    __asm__ __volatile__(
           "xchgl %0, %1"
           : "=r"(ret), "=m"(*spinlock)
           : "0"(1), "m"(*spinlock)
           : "memory");
                                
    return ret;
}
