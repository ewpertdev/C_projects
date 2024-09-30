#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main() {
int pid;
// Crear un proceso hijo
pid = fork();
if (pid == -1) {
// Error al crear el proceso hijo
perror("fork failed");
exit(1);
}
printf("Hola, ¿qué tal? Todo bien, gracias.\\n");

if (pid == 0) {
printf("\\tSoy el proceso hijo, mi PID es %d\\n", g
etpid());
printf("Estoy bien, gracias por preguntar");
}
printf("Soy el proceso padre, mi PID es %d\\n", getpid
());
return 0;
}

/* 
Hay un error de formato en la llamada a getpid() en el proceso hijo.

La función está dividida entre dos líneas.

El mensaje "Estoy bien, gracias por preguntar" está fuera del bloque condicional del proceso hijo.

La lógica para que el padre pregunte y el hijo responda no está correctamente implementada.*/