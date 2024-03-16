#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

int main(){
    int pid;
    int tuberia[2];
    pipe(tuberia);
    printf("Comienzo: \n");

    for(int j=0; j<100; j++)
        for(int i=0; i<3; i++){
            if((pid = fork()) == 0){
                close(tuberia[0]);                   
                char w = 65+i;                       
                write(tuberia[1], &w, sizeof(char)); 
                close(tuberia[1]);                   
                exit(0);                             
            }else{
                waitpid(pid, NULL, 0);               
                char r;                                               
                read(tuberia[0], &r, sizeof(char));  
                printf("%c", r);                     
                fflush(stdout);                      
            }
        }

    printf("\n");
    return 0;
}
