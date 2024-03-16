#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

#define CANT_ABEJAS 15
#define PORCIONES_MIEL 20

typedef struct semaphores{

	sem_t tarro;
	sem_t lleno;
	sem_t oso;
	sem_t lugar;	

} *semaforos;

void *vivir(void* arg);
void *producir(void* arg);
int abeja=1;

void main(){

	semaforos sem= malloc (sizeof(struct semaphores));
	pthread_t abejas[CANT_ABEJAS];	
	pthread_t oso;

	/* INICIALIZACIÓN DE SEMÁFOROS */
	sem_init(&(sem->tarro),0,1);
	sem_init(&(sem->oso),0,1);	
	sem_init(&(sem->lleno),0,PORCIONES_MIEL);
	sem_init(&(sem->lugar),0,PORCIONES_MIEL);

	/* INICIALIZACION DE LOS HILOS (ABEJAS) */
	for(int i=0; i<CANT_ABEJAS; i++)
		if(pthread_create(&(abejas[i]),NULL,producir,sem)!=0)
			printf("ERROR al crear al inicializar el hilo para la abeja n°%d\n",i);

	/* INICIALIZACION DEL OSO */
	if(pthread_create(&oso,NULL,vivir,sem)!=0)
		printf("ERROR al crear al inicializar el hilo para el oso \n");

	/* JOIN DE LOS HILOS ABEJAS */
	for(int i=0; i<CANT_ABEJAS; i++)
		if(pthread_join(abejas[i],0)!=0)
			printf("ERROR al realizar el join para el hilo de la abeja n°%d\n",i);
	
	if(pthread_join(oso,0)!=0)
		printf("ERROR al realizar el join para el hilo del oso\n");	


	/* DESTRUCCIÓN DE SEMÁFOROS */
	sem_destroy(&(sem->tarro));
	sem_destroy(&(sem->oso));
	sem_destroy(&(sem->lugar));
	sem_destroy(&(sem->lleno));
	
	exit(0);
}


void *producir(void* arg){
	
	semaforos sem= (semaforos) arg;

while(1){

	sem_wait(&(sem->tarro));
	sem_wait(&(sem->lugar));
	if(sem_trywait(&(sem->lleno))==0){
		printf("La abeja n°%i produce una porción de miel\n",abeja);		
	}
	else{
		printf("\nLA ABEJA N°%i DESPERTARÁ EL OSO\n",abeja);		
		sem_post(&(sem->oso));	
	}
	
	sem_post(&(sem->tarro));
	abeja++;
		
}
}

void *vivir(void* arg){

	semaforos sem= (semaforos) arg;

while(1){

	sem_wait(&(sem->oso));
	sem_wait(&(sem->tarro));
	
	printf("\nEl oso come miel\n");

	for(int i=0;i<PORCIONES_MIEL;i++){
		sem_post(&(sem->lugar));
		sem_post(&(sem->lleno));
	}
	
	printf("\nEl oso se va a dormir\n");
	sem_post(&(sem->tarro));	
	printf("\n");
}
}
