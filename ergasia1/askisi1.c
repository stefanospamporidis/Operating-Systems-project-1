#include "askisi1.h"

int isNumber(char* number){ //tsekarw an dinw ari8mo apo to pliktrologio
	int i;
	for (i=0;i<strlen(number);i++){
		if (number[i]<'0' || number[i]>'9')
			return 0;
	}
	return 1;
}	

/* Semaphore down operation, using semop */
int sem_wait(int sem_id) {
   struct sembuf sem_d;
   
   sem_d.sem_num = 0;
   sem_d.sem_op = -1;
   sem_d.sem_flg = 0;
   if (semop(sem_id,&sem_d,1) == -1) {
       perror("# Semaphore down operation ");
       return -1;
   }
   return 0;
}

/* Semaphore up operation, using semop */
int sem_signal(int sem_id) {
   struct sembuf sem_d;
   
   sem_d.sem_num = 0;
   sem_d.sem_op = 1;
   sem_d.sem_flg = 0;
   if (semop(sem_id,&sem_d,1) == -1) {
       perror("# Semaphore up operation ");
       return -1;
   }
   return 0;
}

/* Semaphore Init - set a semaphore's value to val */
int sem_Init(int sem_id, int val) {

   union semun arg;
   
   arg.val = val;
   if (semctl(sem_id,0,SETVAL,arg) == -1) {
       perror("# Semaphore setting value ");
       return -1;
   }
   return 0;

}

void CreateResources(){
	shmsize =  sizeof(Component);
	//ftiaxnoume shared memory   
	shm_Const_Painter = shmget (SHMKEY1, shmsize, PERMS | IPC_CREAT);
	if ( shm_Const_Painter < 0 ) {
    	FreeResources(0,0,0,0,0,0,0,0,0);
    }
	shm_Painter_Controller = shmget (SHMKEY2, shmsize, PERMS | IPC_CREAT);
	if ( shm_Painter_Controller < 0 ) {
        FreeResources(1,0,0,0,0,0,0,0,0);
    }
	shm_Controller_Composition = shmget (SHMKEY3, shmsize, PERMS | IPC_CREAT);
	if ( shm_Controller_Composition < 0 ) {
        FreeResources(1,1,0,0,0,0,0,0,0);
    }
	//kanoume attach tis mnimes 
	shm_Const_Painter_ptr = (Component*)shmat(shm_Const_Painter, (char *) 0, 0);
	if ( shm_Const_Painter_ptr == NULL ) {
    	FreeResources(1,1,0,0,0,0,0,0,0);        
    }
	shm_Painter_Controller_ptr = (Component*)shmat(shm_Painter_Controller, (char *) 0, 0);
	if ( shm_Const_Painter_ptr == NULL ) {
    	FreeResources(1,1,0,0,0,0,0,0,0);         
    }
	shm_Controller_Composition_ptr = (Component*)shmat(shm_Controller_Composition, (char *) 0, 0);
	if ( shm_Const_Painter_ptr == NULL ) {
    	FreeResources(1,1,0,0,0,0,0,0,0);         
    }
	//Create a new semaphore
	sem_Constructor = semget(SEMKEY1,1,IPC_CREAT | 0660);
   	if (sem_Constructor == -1) {
       	FreeResources(1,1,1,0,0,0,0,0,0);
   	}
	//Create a new semaphore
	sem_Paint = semget(SEMKEY2,1,IPC_CREAT | 0660);
   	if (sem_Paint == -1) {
       	FreeResources(1,1,1,1,0,0,0,0,0);
   	}
	//Create a new semaphore
	sem_Paint_Controller = semget(SEMKEY3,1,IPC_CREAT | 0660);
   	if (sem_Paint_Controller == -1) {
       	FreeResources(1,1,1,1,1,0,0,0,0);
   	}
	//Create a new semaphore
	sem_Controller_Paint = semget(SEMKEY4,1,IPC_CREAT | 0660);
   	if (sem_Controller_Paint == -1) {
       	FreeResources(1,1,1,1,1,1,0,0,0);
   	}
	//Create a new semaphore
	sem_Controller_Composition = semget(SEMKEY5,1,IPC_CREAT | 0660);
   	if (sem_Controller_Composition == -1) {
       	FreeResources(1,1,1,1,1,1,1,0,0);
   	}
	//Create a new semaphore
	sem_Composition_Controller = semget(SEMKEY6,1,IPC_CREAT | 0660);
   	if (sem_Composition_Controller == -1) {
       	FreeResources(1,1,1,1,1,1,1,1,0);
   	}
	
	
}

void FreeResources(int f1,int f2,int f3,int f4,int f5,int f6,int f7,int f8,int f9){

	if (f1 == 1){
		if (shmctl(shm_Const_Painter,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Const_Painter \n");
			exit(1);
		}			
	}
	if (f2 == 1){
		if (shmctl(shm_Painter_Controller,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Const_Painter \n");
			exit(1);
		}		
	}
	if (f3 == 1){
		if (shmctl(shm_Controller_Composition,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Const_Painter \n");
			exit(1);
		}	
	}
	if (f4 == 1){
		if (shmctl(shm_Const_Painter,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Const_Painter \n");
			exit(1);
		}
		if (shmctl(shm_Painter_Controller,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Painter_Controller \n");
			exit(1);
		}	
		if (shmctl(shm_Controller_Composition,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Controller_Composition \n");
			exit(1);
		}	
	}
	if (f5 == 1){
		if (shmctl(shm_Const_Painter,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Const_Painter \n");
			exit(1);
		}
		if (shmctl(shm_Painter_Controller,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Painter_Controller \n");
			exit(1);
		}	
		if (shmctl(shm_Controller_Composition,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Controller_Composition \n");
			exit(1);
		}		
	}
	if (f6 == 1){
		if (shmctl(shm_Const_Painter,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Const_Painter \n");
			exit(1);
		}
		if (shmctl(shm_Painter_Controller,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Painter_Controller \n");
			exit(1);
		}	
		if (shmctl(shm_Controller_Composition,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Controller_Composition \n");
			exit(1);
		}	
	}
	if (f7 == 1){
		if (shmctl(shm_Const_Painter,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Const_Painter \n");
			exit(1);
		}
		if (shmctl(shm_Painter_Controller,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Painter_Controller \n");
			exit(1);
		}	
		if (shmctl(shm_Controller_Composition,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Controller_Composition \n");
			exit(1);
		}	
	}
	if (f8 == 1){
		if (shmctl(shm_Const_Painter,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Const_Painter \n");
			exit(1);
		}
		if (shmctl(shm_Painter_Controller,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Painter_Controller \n");
			exit(1);
		}	
		if (shmctl(shm_Controller_Composition,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Controller_Composition \n");
			exit(1);
		}		
	}
	if (f9 == 1){
		if (shmctl(shm_Const_Painter,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Const_Painter \n");
			exit(1);
		}
		if (shmctl(shm_Painter_Controller,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Painter_Controller \n");
			exit(1);
		}	
		if (shmctl(shm_Controller_Composition,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror("shm_Controller_Composition \n");
			exit(1);
		}	
	}
	exit(1);

}

void InitSemaphores(){

	//Semaphores initialization
   	/* Set the value of the semaphore to 1 */
   	if (sem_Init(sem_Constructor, 1) == -1) { 
       		FreeResources(1,1,1,0,0,0,0,0,0);
   	}
	if (sem_Init(sem_Paint, 0) == -1) { 
       		FreeResources(1,1,1,1,0,0,0,0,0);
   	}
	if (sem_Init(sem_Paint_Controller, 1) == -1) { 
       		FreeResources(1,1,1,1,1,0,0,0,0);
   	}
	if (sem_Init(sem_Controller_Paint, 0) == -1) { 
       		FreeResources(1,1,1,1,1,1,0,0,0);
   	}
	if (sem_Init(sem_Controller_Composition, 1) == -1) { 
       		FreeResources(1,1,1,1,1,1,1,0,0);
   	}
	if (sem_Init(sem_Composition_Controller, 0) == -1) { 
       		FreeResources(1,1,1,1,1,1,1,1,0);
   	}
	
}

void putinSharedMemory(Component c,Component *shm){

	shm->creation_time=c.creation_time;
	shm->paint_in_time=c.paint_in_time;
	strcpy(shm->id,c.id);
	shm->type=c.type;
	

}

void takefromSharedMemory(Component *shm,Component *c){

	c->creation_time=shm->creation_time;
	c->paint_in_time=shm->paint_in_time;
	strcpy(c->id,shm->id);
	c->type=shm->type;

}

void Constructor(int type,int N){

	int i;
	int counter;
	Component c;
	for (i=1;i<=N;i++){
		if (type==1){
			usleep(CONSTR_TIME1);		
		}
		else if (type==2){
			usleep(CONSTR_TIME2);		
		}
		else{
			usleep(CONSTR_TIME3);		
		}
		counter=IdMaker(type,i);	
		ComponentConstructor(type,counter,&c);
		sem_wait(sem_Constructor);
		putinSharedMemory(c,shm_Const_Painter_ptr);
		// printf("Constr:id= %s type= %d\n",c.id,c.type);
		sem_signal(sem_Paint);
	}
	printf("eimai o constructor \n");
	exit(1);
}

void Painter(int N){
	
	int i;
	Component c;
	for (i=0;i<3*N;i++){
		sem_wait(sem_Paint);
		takefromSharedMemory(shm_Const_Painter_ptr,&c);
		//printf("Painter:id= %s type= %d\n",c.id,c.type);
		c.paint_in_time=clock();
		usleep(PAINTER_TIME);
		sem_signal(sem_Constructor);
		// proxwraw gia na to dwsw ston controller
		sem_wait(sem_Paint_Controller);
		putinSharedMemory(c,shm_Painter_Controller_ptr);
		sem_signal(sem_Controller_Paint);
	}
	printf("eimai o painter \n");
	exit(1);
}

void Controller(int type,int N){

	int counter=0;
	Component c;
	Queue q;
	initQueue(&q);
	while (1){
		sem_wait(sem_Controller_Paint);
		takefromSharedMemory(shm_Painter_Controller_ptr,&c);
		if (type != c.type){
			sem_signal(sem_Controller_Paint);
			continue;
		}
		sem_signal(sem_Paint_Controller);
		addNode(&q,c);
		counter++;
		if (counter==N){
			break;
		}
		sem_wait(sem_Controller_Composition);
		if (shm_Controller_Composition_ptr->type==type){
			removeNode(&q,&c);
			putinSharedMemory(c,shm_Controller_Composition_ptr);
			sem_signal(sem_Composition_Controller);
		}
		else {
			sem_signal(sem_Controller_Composition);
			continue;		
		}
	}
	while (1){
		sem_wait(sem_Controller_Composition);
		if (shm_Controller_Composition_ptr->type==type){
			removeNode(&q,&c);
			putinSharedMemory(c,shm_Controller_Composition_ptr);
			sem_signal(sem_Composition_Controller);
		}
		else {
			sem_signal(sem_Controller_Composition);
			continue;		
		}
		if (queueIsEmpty(&q)==1){
			break;		
		}
	}
	printf("eimai o controller \n");
	exit(1);
}


void Composition(int N){

	int i;
	clock_t total_composition_time=0,total_paint_waiting_time=0;
	Component c1,c2,c3,temp_c;
	for (i=0;i<3*N;i++){
		sem_wait(sem_Composition_Controller);
		takefromSharedMemory(shm_Controller_Composition_ptr,&temp_c);
		if (temp_c.type==1){
			copyComponent(&temp_c,&c1);
			total_paint_waiting_time+=c1.paint_in_time;
			shm_Controller_Composition_ptr->type=2;
		}
		else if (temp_c.type==2){
			copyComponent(&temp_c,&c2);
			total_paint_waiting_time+=c2.paint_in_time;
			shm_Controller_Composition_ptr->type=3;
		}
		else {
			copyComponent(&temp_c,&c3);
			total_paint_waiting_time+=c3.paint_in_time;
			shm_Controller_Composition_ptr->type=1;
			if (c1.creation_time <= c2.creation_time && c1.creation_time <= c2.creation_time)
				total_composition_time+=clock()-c1.creation_time;
			if (c2.creation_time <= c1.creation_time && c2.creation_time <= c3.creation_time)
				total_composition_time+=clock()-c2.creation_time;
			if (c3.creation_time <= c1.creation_time && c3.creation_time <= c2.creation_time)
				total_composition_time+=clock()-c3.creation_time;
		}		
		sem_signal(sem_Controller_Composition);
	}
	printf("meso xrono anamonis: %5.2f secs \n",total_paint_waiting_time/3000.0*N); //to total paint waiting time einai ms kai ta kanw seconds kai kanw print 5 4ifia opou ta duo einai dekadika
	printf("meso xrono dimiourgias proiontos: %5.2f secs \n",total_composition_time/1000.0*N);
	printf("eimai o composition \n");
	exit(1);
}

void ComponentConstructor(int type,int counter,Component *c){

	if (counter >= 0 && counter < 10){
		sprintf(c->id,"000%d",counter);
	}
	else if (counter >= 10 && counter < 100){
		sprintf(c->id,"00%d",counter);
	}
	else if (counter >= 100 &&  counter < 1000){
		sprintf(c->id,"0%d",counter);
	}
	else{
		sprintf(c->id,"%d",counter);
	}
	c->type=type;
	c->creation_time=clock();
	
}

int IdMaker(int type,int i){

	if (type == 3){
		return i%10000;
	}
	else if (type == 2){
		return i/10000;
	}
	else {
		return i/10000000;
	}

}

int main ( int argc , char * argv []) {
	
	int i,N,status;
	pid_t childpid,wpid;
	Component c; // einai to dummy item me arxikopoiisi sto type=1 pou vazw sto shared memory tou Controller_Composition
	c.type=1;
	if (argc != 2){
		printf("La8os ari8mos orismatwn\n");
		exit(1);
	}
	if (isNumber(argv[1]) == 0 ){
		printf("La8os ari8mos sta orismata\n");
		exit(1);
	}
	N=atoi(argv[1]);
	CreateResources(); //edw 8a kaleitai i create resources
	InitSemaphores();
	putinSharedMemory(c,shm_Controller_Composition_ptr); // edw dinw to dummy item stin shared memory Controller_Composition gia to prwto item pou 8a valei o controller
	for (i=1;i<4;i++){
		childpid=fork();
		if (childpid==0){
			Constructor(i,N);
			// break;
		}
	}
	
	childpid=fork();
	if (childpid==0)
		Painter(N);
	
	for (i=1;i<4;i++){
		childpid=fork();
		if (childpid==0){
			Controller(i,N);
			// break;
		}
	}

	childpid=fork();
	if (childpid==0)
		Composition(N);

	
	while((wpid=wait(&status)) > 0 ){
		printf("teleiwse i %u\n",wpid);
	}
	FreeResources(1,1,1,1,1,1,1,1,1);
	printf("eimai i main \n");
	return 0;
}

//arxikopoisi semaforwn na ginei sunartisi
//8a dinw kati apo tin grammi entolwn kai 8a kanw print components
