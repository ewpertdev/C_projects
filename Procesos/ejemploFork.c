#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>

int main(){
/*tipo int que representa el ID de un proceso*/
pid_t pid;
int status;

/*Creamos un proceso*/
pid=fork();
if (pid==-1){
	printf("no se ha creado un proceso");
	exit(-1);
}

if (pid==0) {
	printf("soy hijo\n%d\n", getpid()); /*proceso hijo*/
	exit(0);
} else{
	wait(NULL);
	printf("soy padre \n%d\n", getppid()); /*proceso padre*/
}
}


