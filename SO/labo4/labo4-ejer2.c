#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

//GRANDE DYLEN
int main(){

    int pid;
    int tuberia[2];
    pipe(tuberia);
	char w,r;
	int i=0;

    while(i<50){

        for(int i=0; i<5; i++){

            if((pid = vfork()) == 0){

                close(tuberia[0]);                   
                w = 65+i;                       
                write(tuberia[1], &w, sizeof(char)); 
                close(tuberia[1]);              
                _exit(0);                             

            }
			else{
                           
                read(tuberia[0], &r, sizeof(char));  
                printf("%c", r);                     
            }
        }

		i++;
	}

    printf("\n");
    return 0;
}
