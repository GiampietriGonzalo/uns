#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void main (int argc, char argv){

	int i;

	for(i=1; i<=argc; i++){

		vfork();
		printf("%d,%d\n",i,getpid());
		
	}
	
	exit(0);
}
