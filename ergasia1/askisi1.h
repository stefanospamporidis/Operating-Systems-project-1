#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <time.h>
#include <string.h>
#include "Componentsqueue.h"
#include <sys/wait.h>


#define SHMKEY1 (key_t)4321 //shared memory keys
#define SHMKEY2 (key_t)1234
#define SHMKEY3 (key_t)2345
#define SEMKEY1 (key_t) 4567 //semaphore keys
#define SEMKEY2 (key_t) 5678
#define SEMKEY3 (key_t) 6789
#define SEMKEY4 (key_t) 7890
#define SEMKEY5 (key_t) 3456
#define SEMKEY6 (key_t) 3333
#define PERMS 0600
#define CONSTR_TIME1 200
#define CONSTR_TIME2 300
#define CONSTR_TIME3 400
#define PAINTER_TIME 200



int shm_Const_Painter,shm_Painter_Controller,shm_Controller_Composition;
Component *shm_Const_Painter_ptr,*shm_Painter_Controller_ptr,*shm_Controller_Composition_ptr;

int sem_Constructor,sem_Paint,sem_Paint_Controller,sem_Controller_Paint,sem_Controller_Composition,sem_Composition_Controller;
int shmsize;


union semun {
   int val;                  	/* value for SETVAL */
   struct semid_ds *buf;     /* buffer for IPC_STAT, IPC_SET */
   unsigned short *array;    /* array for GETALL, SETALL */

};

void takefromSharedMemory(Component *shm,Component *c); //pairnei to component apo tin sharememory
void putinSharedMemory(Component c,Component *shm); //gemizei to sharedmemory me to component pou kataskeuasame
void InitSemaphores(); //arxikopoiei ta semaphores
int IdMaker(int type,int i); //ftiaxnei ta ids 
void ComponentConstructor(int type,int counter,Component *c); // ftiaxnei ta components
void CreateResources();
void FreeResources(int f1,int f2,int f3,int f4,int f5,int f6,int f7,int f8,int f9);
void Controller(int type,int N); //pairnei ta vammena e3artimata apo ton painter kai ta dinei gia sunarmologisi
void Constructor(int type,int N); //ftiaxnei ta e3artimata
void Painter(int N); //vafei ta e3artimata
void Composition(int N); //sunarmologei ta vamena e3artimata
int sem_wait(int sem_id);
int sem_signal(int sem_id);
int sem_Init(int sem_id, int val);
int isNumber(char* number);
