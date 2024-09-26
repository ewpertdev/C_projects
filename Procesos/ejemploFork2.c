#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main(){
	pid_t pid;
	pid = fork();
	if (pid==-1){
		printf("no se ha creado el proceso\n");
		exit(-1);
	}
	if(pid==0){
		printf("soy hijo %d\n", getpid());
		exit(1);
	} else{

		printf("soy padre \n%d\n", getppid());
	}
	
	pid2=fork();
	
	if(pid==0){
		pid3=fork();
		if(pid==0){
			pid4=fork();
			if(pid==0){

		printf("soy padre \n%d\n", getppid());
			
		printf("soy padre \n%d\n", getppid());
		}

		printf("soy hijo %d\n", getpid());
		exit(2);
	} else {
		 
		printf("soy padre \n%d\n", getppid());
	}
	}
}
