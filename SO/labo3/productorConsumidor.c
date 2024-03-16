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
	sem_t lleno;
	sem_t vacio;
	int sigLleno;
	int sigVacio;

} *producto;

void *consumir(void *arg);
void *producir(void *arg);

void main(){

	pthread_t consumidor;
	pthread_t productor;
	

	producto recurso=malloc(sizeof(struct product));
	sem_init(&(recurso->lleno),0,1);
	sem_init(&(recurso->vacio),0,1);
	//recurso->sigLleno=rand()%21;
	//recurso->sigVacio=rand()%21;	
	
	recurso->sigLleno=0;
	recurso->sigVacio=0;	


	//CREACION DE HILOS
	if(pthread_create(&productor,NULL,producir,recurso) != 0)
		printf("\nError al crear el hilo para el productor\n");

	
	if(pthread_create(&consumidor,NULL,consumir,recurso) != 0)
		printf("\nError al crear el hilo para el consumidor\n");

	sleep(0.5);
		

	//JOIN DE HILOS
	if(pthread_join(productor,NULL)!=0)
		printf("\nError en el JOIN del hilo productor\n");	
	
	if(pthread_join(consumidor,NULL)!=0)
		printf("\nError en el JOIN del hilo consumidor\n");

	
	
}


void *producir(void *arg){

	producto recurso=(producto)arg;
	int item;
	
	while(1){

		sem_wait(&(recurso->vacio));
		item=rand()%21;		
		
		recurso->buffer[recurso->sigVacio]=item;
		printf("\nSe produció el item n°%i en la posición %i \n", item,recurso->sigVacio);		
		sleep(1);		

		recurso->sigVacio=((recurso->sigVacio)+1)%N;
		sem_post(&(recurso->lleno));
	}	

}


void *consumir(void *arg){

	producto recurso=(producto)arg;
	int item;

	while(1){
	
		sem_wait(&(recurso->lleno));
	
		item=recurso->buffer[recurso->sigLleno];
		printf("\nSe consumió el item n°%d en la posición %i \n", item,recurso->sigLleno);		
		recurso->sigLleno=(recurso->sigLleno+1)%N;
		sleep(1);
	
		sem_post(&(recurso->vacio));
	}
}
