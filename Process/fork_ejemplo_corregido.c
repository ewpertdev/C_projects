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
        // Es exit(1) y el valor es 1, por lo que el proceso hijo sale con estado 1
        exit(1);
    }
    
    if (pid == 0) {
        // Proceso hijo
        printf("\tSoy el proceso hijo, mi PID es %d\n", getpid());
        // Es sleep(1) y el valor es 1, por lo que el hijo se duerme 1 segundo
        sleep(1); // Esperar a que el padre pregunte
        printf("\tEstoy bien, gracias por preguntar\n");
    } else {
        // Proceso padre
        printf("Soy el proceso padre, mi PID es %d\n", getpid());
        printf("Hola, ¿qué tal?\n");
        // Es sleep(2) y el valor es 2, por lo que el padre se duerme 2 segundos
        sleep(2); // Esperar la respuesta del hijo
    }
    
    return 0;
}
// Sale el printf del padre y luego el del hijo porque el padre se duerme 2 segundos

/* 
1. Se corrigió el error de formato en la llamada a getpid() en el proceso hijo.

2. Se movió el mensaje "Estoy bien, gracias por preguntar" dentro del bloque condicional del proceso hijo.

3. Se implementó la lógica para que el padre pregunte y el hijo responda:

    -El padre imprime su mensaje de saludo antes de la respuesta del hijo.
    -Se añadieron llamadas a sleep() para sincronizar la salida entre padre e hijo.

4. Se reorganizó el código para mejorar la legibilidad y la lógica del flujo del programa.

Con estos cambios, el programa ahora funciona como se espera: el padre pregunta "¿qué tal?" y el hijo responde "Estoy bien, gracias por preguntar"
*/