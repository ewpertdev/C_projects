
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

  // Este programa demuestra como un programa puede crear un nuevo proceso
  // usando fork()

 int main(){
	 // fork() es una función que crea un nuevo poroceso
	 // Cuando llmas a fork(), divide el proceso actual en dos:
	 // - El proceso padre: El programa original que llamó a fork()
	 // - El proceso hijo: Una copia del padre que se ejecuta en paralelo (de forma separada)
	 
	 pid_t pid = fork(); /* Si el fork() tiene éxito, devuelve un proceso ID(PID)
				El proceso padre obtiene el PID del proceso hijo
				El proceso hijo obtiene 0 */

	 // Si el fork() falla, devuelve -1. Este bloque se ejecuta si hubo un error
	 // mientras se está intentando crear el proceso hijo
	 if (pid == 1) {
		 printf("Error al crear el proceso hijo\n");
		 exit(1);

	// Si pid es igual a 0, quiere decir que estamos dentro del proceso hijo
	 } else if (pid == 0) {
		 // Proceso hijo
		 // El programa imprime su propio PID y el PID de su proceso padre (llamado PPID)
		 // El proceso hijo tiene acceso a esos dos valores
		 printf("Hola, soy el proceso hijo con PID: %d y PPID: %d\n", getpid(), getppid());

		 // Este bloque se ejecuta en el proceseo padre después de que el hijo haya sido creado
	 } else {
		 // Proceso padre
		 // El padre imprime su propio PID, el PPID y el PID del proceso hijo que ha sido creado
		 printf("Hola, soy el proceso padre con PID: %d y PPID: %d.\nHice un proceso con PID %d\n", getpid(), getppid(), pid);

		 int status;
		 // El padre espera a que el hijo se complete antes de terminar
		 wait(&status);
	 }
	 return 0;
 }

/*
 * Se ha observado que algunos de los PID y PPIDs son los mismos, es porque el hijo es una copia del padre.
 *
 * 1. El PID del hijo (el printf en el hijo) cuadra con el PID devuelto por el fork() en el padre porque fork() da al padre el PID del hijo
 *
 * 2. El PPID del hijo es el mismo que el PID del padre porque el padre es el que ha creado al hijo
 *
 * 3. El PPID del padre es diferente porque es el PID del proceso que ha creado al padre
 *
 * En resumen:
 *
 * El PID del hijo (que sale printeado en el proceso hijo) es el mismo PID devuelto por fork() en el proceso padre.
 * Esto se debe a que fork() devuelve el PID del hijo recién creado al padre.
 *
 * El PPID del hijo es el mismo que el PID del padre porque el hijo ha sido creado por el padre.
 * Haciendo que el padre sea su ancestro directo
 *
 * El PPID del padre sera diferente porque se refiere al proceso que ha creado al padre (el shell, terminal) */
