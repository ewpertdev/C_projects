#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

// Definimos los límites para los cálculos
#define PRIME_LIMIT 1000000
#define ODD_LIMIT 5000000

// Función para verificar si un número es primo
bool is_prime(unsigned long long int n) {
    // Si el número es menor o igual a 1, no es primo
    if (n <= 1) return false;
    // Utilizamos un bucle for para verificar si el número es primo
    for (unsigned long long int i = 2; i * i <= n; i++) {
        // Si el número es divisible por algún número, no es primo
        if (n % i == 0) return false;
    }
    // Si el número es primo, devolvemos true
    return true;
}

// Función para calcular la suma de los números primos hasta PRIME_LIMIT
unsigned long long int sum_primes() {
    // Declaramos la variable sum para almacenar la suma de los números primos
    unsigned long long int sum = 0;
    // Utilizamos un bucle for para sumar los números primos desde 2 hasta PRIME_LIMIT
    for (unsigned long long int i = 2; i <= PRIME_LIMIT; i++) {
        // Si el número es primo, lo sumamos
        if (is_prime(i)) {
            // Sumamos el número primo a la variable sum
            sum += i;
        }
    }
    // Devolvemos la suma de los números primos
    return sum;
}

// Función para calcular la suma de los números impares hasta ODD_LIMIT
unsigned long long int sum_odds() {
    // Declaramos la variable sum para almacenar la suma de los números impares
    unsigned long long int sum = 0;
    // Utilizamos un bucle for para sumar los números impares desde 1 hasta ODD_LIMIT
    for (unsigned long long int i = 1; i <= ODD_LIMIT; i += 2) {
        // Sumamos el número impar a la variable sum
        sum += i;
    }
    // Devolvemos la suma de los números impares
    return sum;
}

int main() {
    // Declaramos las variables para los PIDs de los procesos
    pid_t pid1, pid2;
    // La variable status se utiliza para almacenar el estado de salida de los procesos
    int status;

    // PARTE 1: Cálculo secuencial
    // Aquí realizamos los cálculos de forma secuencial
    printf("PART 1: Sequential Computation\n");
    // Calculamos la suma de los números primos y la suma de los números impares
    unsigned long long int prime_sum = sum_primes();
    unsigned long long int odd_sum = sum_odds();
    // Mostramos los resultados
    printf("Suma de primos hasta %d: %llu\n", PRIME_LIMIT, prime_sum);
    printf("Suma de impares hasta %d: %llu\n\n", ODD_LIMIT, odd_sum);

    // PARTE 2: Cálculo en paralelo
    // Ahora ejecutamos dos tareas simultáneamente utilizando procesos hijos
    printf("PART 2: Parallel Computation\n");

    // Creamos el primer proceso hijo para calcular la suma de primos
    pid1 = fork();
    if (pid1 == -1) {
        // Si la creación del proceso falla, mostramos un error y terminamos el programa
        perror("Fork ha fallado");
        // exit(1) es el estado de salida del proceso padre
        exit(1);
    } else if (pid1 == 0) {
        // Código ejecutado por el primer proceso hijo
        // Calcula la suma de números primos y muestra el resultado
        unsigned long long int result = sum_primes();
        // Mostramos el resultado
        printf("Hijo 1 - Suma de primos hasta %d: %llu\n", PRIME_LIMIT, result);
        // Terminamos el proceso hijo
        exit(0);
    }

    // Creamos el segundo proceso hijo para calcular el producto de números impares
    pid2 = fork();
    if (pid2 == -1) {
        // Si la creación del proceso falla, mostramos un error y terminamos el programa
        perror("Fork ha fallado");
        exit(1);
    } else if (pid2 == 0) {
        // Código ejecutado por el segundo proceso hijo
        // Calcula el producto de números impares y muestra el resultado
        unsigned long long int product = 1;
        // Calculamos el producto de los números impares hasta 500,000
        for (unsigned long long int i = 1; i <= 500000; i += 2) {
            // Multiplicamos el número impar por el producto
            product *= i;
            // Si el producto es 0, detenemos el bucle
            if (product == 0) break;
        }
        // Mostramos el resultado
        printf("Hijo 2 - Producto de impares hasta 500,000: %llu\n", product);
        // Terminamos el proceso hijo
        exit(0);
    }

    // El proceso padre espera a que ambos procesos hijos terminen sus tareas

    // Espera a que el primer proceso hijo termine
    waitpid(pid1, &status, 0);

    // Espera a que el segundo proceso hijo termine
    waitpid(pid2, &status, 0);

    // Mostramos un mensaje indicando que ambos procesos hijos han terminado
    printf("Padre: Ambos procesos hijos han terminado.\n");

    // El return 0 es el estado de salida del proceso padre
    return 0;
}
