
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

int n=5;

typedef struct printers{
	sem_t disponible;
	int i1;	
	int i2;
} *impresoras;

void liberar(impresoras p,int imp);
void *requerir(void* arg);

void main(){

	pthread_t hilo;
	pthread_t hilos[n];
	
	impresoras p;
	p=malloc(sizeof(struct printers));
	p->i1=1;
	p->i2=1;
		
	sem_init(&(p->disponible),0,2);
	
	printf("\n.........Comienzo.........\n");
	
	for(int i=;i<n;i++)
		prioridades[]

	//CREACON DE HILOS PARA LOS USUARIOS
	for(int i=1;i<n+1;i++){

		//Prevención de warnings		
		int *cliente=malloc(sizeof(int));
		*cliente=i;
		
		if(pthread_create(&hilo,NULL,*requerir, p)!=0){
			printf("\nERROR al crear un hilo para el usuario n°%i \n",i);
			exit(1);		
		}

		hilos[i]=hilo;
	}

	//JOIN DE LOS HILOS 
	for(int j=1;j<6;j++){
		
		if(pthread_join((hilos[j]),0)!=0){
			printf("\nERROR en join para el usuario n°%i \n",j);
			exit(1);
		}
	}		
		
	printf("\n");	
	sem_destroy(&(p->disponible));	
	free(p);
}


void liberar(impresoras p,int imp){
	
	if(imp==1)
		p->i1=1;	
	
	else
		p->i2=1;
	
	printf("\nSe ha liberando la impresora n°%i\n", imp);
    sem_post(&(p->disponible)); 
}

void *requerir(void* arg){
	
	impresoras p=(impresoras)arg;
	int impresora;

	sem_wait(&(p->disponible));   

    //critical section 	
	if(p->i1==1){
		impresora=1;
		p->i1=0;
	}
	else{
		impresora=2;
		p->i2=0;
	}

	printf("\nSe está utilizando la impresora n°%i\n", impresora);
	sleep(3);
      
    //signal 
	liberar(p,impresora);

	pthread_exit(0); 
}

