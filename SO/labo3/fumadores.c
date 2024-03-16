#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>


typedef struct recursos{

	sem_t tabaco;
	sem_t papel;
	sem_t fosforo;
	pthread_mutex_t mux;

} *ingredientes;

void *armarFT(void *arg);
void *armarFP(void *arg);
void *armarFF(void *arg);
void *repartir(void *arg);

void main(){
	
	pthread_t ft,fp,ff;
	pthread_t agente;

	ingredientes rec= malloc(sizeof(struct recursos));
	sem_init(&(rec->tabaco),0,1);
	sem_init(&(rec->papel),0,1);
	sem_init(&(rec->fosforo),0,1);
	pthread_mutex_init(&(rec->mux),NULL);	


	//INICIALIZACION DE LOS HILOS
	if(pthread_create(&ft,NULL,armarFT, rec)!=0)
		printf("\nError al inicializar el hilo del fumadorTabaco\n");

	if(pthread_create(&fp,NULL,armarFP, rec)!=0)
		printf("\nError al inicializar el hilo del fumadorPapel\n");
	
	if(pthread_create(&ff,NULL,armarFF, rec)!=0)
		printf("\nError al inicializar el hilo del fumadorFosforo\n");

	
	if(pthread_create(&agente,NULL,repartir, rec)!=0)
		printf("\nError al inicializar el hilo del agente\n");		


	
	//JOINS
	if(pthread_join(ft,NULL)!=0)
		printf("\nError en el JOIN del fumadorTabaco\n");

	if(pthread_join(fp,NULL)!=0)
		printf("\nError en el JOIN del fumadorPepel\n");
	
	if(pthread_join(ff,NULL)!=0)
		printf("\nError en el JOIN del fumadorFosoforo\n");
	
	if(pthread_join(agente,NULL)!=0)
		printf("\nError en el JOIN del fumadorAgente\n");	

}

void *armarFF(void *arg){

	ingredientes rec=(ingredientes) arg;

	while(1){

		sem_wait(&(rec->tabaco));
		sem_wait(&(rec->papel));
		printf("\nEl fumando que tiene FÓSFOROS está fumando\n");
		pthread_mutex_unlock(&(rec->mux));
		
	}

}

void *armarFP(void *arg){
	
	ingredientes rec=(ingredientes) arg;
	
	while(1){
		sem_wait(&(rec->fosforo));
		sem_wait(&(rec->tabaco));

		printf("\nEl fumando que tiene PAPEL está fumando\n");
		pthread_mutex_unlock(&(rec->mux));
	}

}

void *armarFT(void *arg){

	ingredientes rec=(ingredientes) arg;

	while(1){

		sem_wait(&(rec->fosforo));
		sem_wait(&(rec->papel));
		printf("\nEl fumando que tiene TABACO está fumando\n");
		pthread_mutex_unlock(&(rec->mux));
		
	}

}

void *repartir(void *arg){
	
	ingredientes rec=(ingredientes) arg;
	
	while(1){

		sleep(1);
		int i=rand()%3;
		

		if(i==0){
			sem_post(&(rec->tabaco));
			sem_post(&(rec->papel));
			printf("\nSe libero tabaco y papel\n");
		}
		else
			if(i==1){
				sem_post(&(rec->tabaco));
				sem_post(&(rec->fosforo));
				printf("\nSe libero tabaco y fosforo\n");
			}
			else{
				sem_post(&(rec->fosforo));
				sem_post(&(rec->papel));
				printf("\nSe libero fosforo y papel\n");
			}
		
		pthread_mutex_lock(&(rec->mux));	
	}	
}
