#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define CANT_ABEJAS 100
#define PORCIONES_MIEL 10

sem_t oso;
sem_t tarro;
sem_t abeja_produciendo;

pthread_t t_oso;
pthread_t t_abejas[CANT_ABEJAS];

int cont = 1;

void comer(){

    printf("Oso durmiendo\n");
    sem_wait(&oso);

    printf("Oso comiendo\n");

    for(int i=0; i<PORCIONES_MIEL; i++){
        sem_post(&abeja_produciendo);
        cont--;
    }

    sem_post(&tarro);
}

void producir_miel(){

    sem_wait(&tarro);

    if(sem_trywait(&abeja_produciendo))
        sem_post(&oso);
    else{
        printf("Producir miel %d\n", cont++);
        sem_post(&tarro);
    }
}

void* th_oso(void *args){
    while(1)
        comer();
}

void* th_abeja(void *args){
    while(1)
        producir_miel();
}

int main(){

    sem_init(&tarro, 1, 1);
    sem_init(&oso, 1, 0);
    sem_init(&abeja_produciendo, 0, PORCIONES_MIEL);

    for(int i=0; i<CANT_ABEJAS; i++)
        pthread_create(&t_abejas[i], NULL, th_abeja, NULL);
    pthread_create(&t_oso, NULL, th_oso, NULL);

    getchar();
    return 0;
}
