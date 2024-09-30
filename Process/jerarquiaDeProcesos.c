#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Creamos un programa que muestre la jerarquia de procesos

int main() {
    // Declaramos las variables para los PIDs de los procesos
    pid_t pid1, pid2, pid3, pid4;
    // El int status se utiliza para almacenar el estado de salida de los procesos
    int status;

    // Proceso padre (level 0)
    printf("Proceso padre - PID: %d, PPID: %d, Nivel: 0\n", getpid(), getppid());

    // Crear primer hijo (H1)
    pid1 = fork();
    if (pid1 == -1) {
        perror("Fork ha fallado");
        // exit(1) es el estado de salida del proceso padre
        exit(1);
    } else if (pid1 == 0) {
        // Proceso H1 (level 1)
        printf("Proceso H1 - PID: %d, PPID: %d, Nivel: 1\n", getpid(), getppid());
        // exit(1) es el estado de salida del proceso H1
        exit(1);
    } else {
        printf("Padre creó H1 con PID: %d\n", pid1);
    }

    // Crear segundo hijo (H2)
    pid2 = fork();
    if (pid2 == -1) {
        perror("Fork ha fallado");
        exit(1);
    } else if (pid2 == 0) {
        // Proceso H2
        printf("Proceso H2 - PID: %d, PPID: %d, Nivel: 1\n", getpid(), getppid());
    }

        // H2 crea su primer hijo 
        pid3 = fork();
        if (pid3 == -1) {
            perror("Fork ha fallado");
            exit(1);
        } else if (pid3 == 0) {
            // Primer hijo de H2 (nivel 2)
            printf("El primer hijo de H2 - PID: %d, PPID: %d, Nivel: 2\n", getpid(), getppid());
            // exit(2) es el estado de salida del primer hijo de H2
            exit(2);
        } else {
            printf("H2 creó su primer hijo con PID: %d\n", pid3);
        }

        // H2 crea su segundo hijo
        pid4 = fork();
        if (pid4 == -1) {
            perror("Fork ha fallado");
            exit(1);
        } else if (pid4 == 0) {
            // Segundo hijo de H2 (nivel 2)
            printf("El segundo hijo de H2 - PID: %d, PPID: %d, Nivel: 2\n", getpid(), getppid());
            // exit(2) es el estado de salida del segundo hijo de H2
            exit(2);
        } else {
            printf("H2 creó su segundo hijo con PID: %d\n", pid4);
        }

        // H2 espera a sus hijos
        waitpid(pid3, &status, 0);
        printf("El primer hijo de H2 ha salido con estado: %d\n", WEXITSTATUS(status));
        waitpid(pid4, &status, 0);
        printf("El segundo hijo de H2 ha salido con estado: %d\n", WEXITSTATUS(status));

        // exit(1) es el estado de salida del proceso H2
        exit(1);
    } else {
        printf("Padre creó H2 con PID: %d\n", pid2);
    }

    // Padre espera a sus hijos
    waitpid(pid1, &status, 0);
    printf("H1 salió con estado: %d\n", WEXITSTATUS(status));
    waitpid(pid2, &status, 0);
    printf("H2 salió con estado: %d\n", WEXITSTATUS(status));

    return 0;
}


