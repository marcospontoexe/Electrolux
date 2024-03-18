#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>

typedef struct {
    int *arrayPares;
    int tamanhoPares;
    float media;
    int maximo;
    int minimo;
} Valores;

Valores calculaValores(int *array, int tamanho) {
    Valores valores;

    int soma = 0;
    valores.maximo = array[0];
    valores.minimo = array[0];
    int pares[tamanho]; // Array temporário 
    int contPares = 0;
    
    for (int i = 0; i < tamanho; i++) {
        soma += array[i];
        if (array[i] > valores.maximo) {
            valores.maximo = array[i];
        }
        if (array[i] < valores.minimo) {
            valores.minimo = array[i];
        }
        if (array[i] % 2 == 0) { // valor par
            pares[contPares++] = array[i]; 
        }
    }

    // média
    valores.media = (float)soma / tamanho;

    // Aloca dinâmica de memória arrayPares
    valores.arrayPares = (int*)malloc(contPares * sizeof(int));
    if (valores.arrayPares == NULL) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }

    // Copia o array temporario para arrayPares
    for (int i = 0; i < contPares; i++) {
        valores.arrayPares[i] = pares[i];
    }
    valores.tamanhoPares = contPares;

    return valores;
}

int main(int argc, char const *argv[]) {
    setlocale(LC_ALL, "Portuguese_Brazil");
    int array[] = {110, 582, 63, 14, 3, 1, 88, 73, 909, 7410, 2, 82};
    int tamanho = sizeof(array) / sizeof(array[0]);

    Valores valores = calculaValores(array, tamanho);

    printf("Valor média: %.2f\n", valores.media);
    printf("Valor máximo: %d\n", valores.maximo);
    printf("Valor mínimo: %d\n", valores.minimo);
    printf("Quantidade de números pares: %d\n", valores.tamanhoPares);
    printf("Números pares:\n");
    for (int i = 0; i < valores.tamanhoPares; i++) {
        printf("%d ", valores.arrayPares[i]);
    }
    printf("\n");

    free(valores.arrayPares);

    return 0;
}