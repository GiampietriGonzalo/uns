//Problema del Productor-Consumidor
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>

int N=20;

typedef struct product{
	int buffer[20];
	pthread_mutex_t mux;
	int sigLleno;
	int sigVacio;

} *producto;

void *consumir(void *arg);
void *producir(void *arg);

void main(){

	pthread_t consumidor;
	pthread_t productor;
	

	producto recurso=malloc(sizeof(struct product));
	pthread_mutex_init(&(recurso->muxLleno), NULL);
	pthread_mutex_init(&(recurso->muxVacio), NULL);
	//recurso->sigLleno=rand()%21;
	//recurso->sigVacio=rand()%21;	
	
	recurso->sigLleno=0;
	recurso->sigVacio=0;	


	//CREACION DE HILOS
	for(int j=0; j<2;j++)
		if(pthread_create(&productor,NULL,producir,recurso) != 0)
			printf("\nError al crear el hilo para el productor n°%i\n",j+1);


	for(int j=0; j<3;j++)
		if(pthread_create(&consumidor,NULL,consumir,recurso) != 0)
			printf("\nError al crear el hilo para el consumidor n°%i\n",j+1);
	

	//JOIN DE HILOS
	for(int j=0; j<2;j++)
		if(pthread_join(productor,NULL)!=0)
			printf("\nError en el JOIN del hilo productor n°%i\n",j+1);	
	
	for(int j=0; j<3;j++)
		if(pthread_join(consumidor,NULL)!=0)
			printf("\nError en el JOIN del hilo consumidor n°%i\n",j+1);

	
	
}


void *producir(void *arg){

	producto recurso=(producto)arg;
	int item;
	
	while(1){

		pthread_mutex_lock(&(recurso->muxVacio));
		item=rand()%21;		
		
		recurso->buffer[recurso->sigVacio]=item;
		printf("\nSe produció el item n°%i en la posición %i \n", item,recurso->sigVacio);		
		sleep(1);		

		
		recurso->sigLleno=((recurso->sigLleno)+1)%N;		
		pthread_mutex_unlock(&(recurso->muxLleno));
		
	}	

}


void *consumir(void *arg){

	producto recurso=(producto)arg;
	int item;

	while(1){
	
		sem_wait(&(recurso->lleno));
		pthread_mutex_lock(&(recurso->muxLleno));
	
		item=recurso->buffer[recurso->sigLleno];
		printf("\nSe consumió el item n°%d en la posición %i \n", item,recurso->sigLleno);		
		recurso->sigLleno=(recurso->sigLleno+1)%N;
		sleep(1);
	
		sem_post(&(recurso->vacio));
		pthread_mutex_unlock(&(recurso->muxVacio));
		
	}
}
