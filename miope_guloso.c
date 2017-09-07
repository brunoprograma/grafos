#include <stdlib.h>
#include <stdio.h>

void print_matriz(int *matriz, int lin, int col) {
    int i, j, (*p_matriz)[lin][col] = (int (*)[lin][col]) matriz;

    for (i = 0; i < lin; i++) {
        printf("[");
        for (j = 0; j < col; j++) {
            printf("%d", (*p_matriz)[i][j]);
            if (!(j+1 == col))
                printf(", ");
        }
        printf("]\n");
    }
    printf("\n");
}

struct Ivalor {
    int indice;
    int valor;
};

struct Ivalor menor_positivo(int *vetor, int tam) {
    int i, (*p_vetor)[tam] = (int (*)[tam]) vetor;
    struct Ivalor menor;
    menor.valor = -1;
    menor.indice = -1;

    for (i = 0; i < tam; i++) {
        if (menor.valor == -1 && (*p_vetor)[i] > 0) {
            menor.indice = i;
            menor.valor = (*p_vetor)[i];
        } else if (menor.valor != -1 && (*p_vetor)[i] > 0 && (*p_vetor)[i] < menor.valor) {
            menor.indice = i;
            menor.valor = (*p_vetor)[i];
        } else {
            continue;
        }
    }

    return menor;
}

int visitado(int *vetor, int tam, int num) {
    int i;
    for (i = 0; i < tam; i++) {
        if (vetor[i] == num) {
            return 1;
        }
    }
    return 0;
}

void guloso_adjacencia(int *matriz, int lin, int col) {
	int i, visitados[lin], i_vis = 0, distancia = 0,
	(*p_matriz)[lin][col] = (int (*)[lin][col]) matriz;
    struct Ivalor proximo;

    for (i = 0; i < lin; i++)
        visitados[i] = -1;

	for (i = 0; i < lin; i++) {
        visitados[i_vis++] = i;
        proximo = menor_positivo((*p_matriz)[i], col);

        if (proximo.valor && !visitado(&visitados, lin, proximo.indice)) {
            printf("%d -> ", i+1);
            i = proximo.indice;
            i--;
            distancia += proximo.valor;
        } else {
            printf("%d\n\n", i+1);
            break;
        }
	}

	printf("Distância: %d\n\n\n", distancia);
}

struct Ivalor loc_destino(int *matriz, int lin, int col, int atual, int indice, int valor) {
    int i, j, (*p_matriz)[lin][col] = (int (*)[lin][col]) matriz;
    struct Ivalor destino;
    destino.valor = -1;
    destino.indice = -1;

    if (indice != -1 && valor != -1) {
        for (i = 0; i < lin; i++) {
            if (i != atual) {
                if ((*p_matriz)[i][indice] + valor == 0) {
                    destino.indice = i;
                    destino.valor = (*p_matriz)[i][indice];
                    break;
                } else if ((*p_matriz)[i][indice] == valor) {
                    destino.indice = i;
                    destino.valor = (*p_matriz)[i][indice];
                    break;
                }
            }
        }
    }

    return destino;
}

void guloso_incidencia(int *matriz, int lin, int col) {
	int i, visitados[lin], i_vis = 0, distancia = 0,
	(*p_matriz)[lin][col] = (int (*)[lin][col]) matriz;
    struct Ivalor proximo, aresta;

    for (i = 0; i < lin; i++)
        visitados[i] = -1;

	for (i = 0; i < lin; i++) {
        visitados[i_vis++] = i;
        aresta = menor_positivo((*p_matriz)[i], col);
        proximo = loc_destino(matriz, lin, col, i, aresta.indice, aresta.valor);

        if (aresta.valor && !visitado(&visitados, lin, proximo.indice)) {
            printf("%d -> ", i+1);
            i = proximo.indice;
            i--;
            distancia += aresta.valor;
        } else {
            printf("%d\n\n", i+1);
            break;
        }
	}

	printf("Distância: %d\n\n\n", distancia);
}

int main(void) {
	int ma1[5][5] = {{0, 30, -15, 0, 20},
                     {-30, 0, -10, 50, 0},
                     {15, 10, 0, 5, -10},
                     {0, 50, -5, 0, -30},
                     {-20, 0, 10, 30, 0}},
        mi1[5][8] = {{30, 0, 0, 20, -15, 0, 0, 0},
                     {-30, 50, 0, 0, 0, -10, 0, 0},
                     {0, 0, 0, 0, 15, 10, 5, -10},
                     {0, 50, -30, 0, 0, 0, -5, 0},
                     {0, 0, 30, -20, 0, 0, 0, 10}},
        ma2[7][7] = {{0, 2, 0, 6, 12, 0, 0},
                     {-2, 0, 1, 0, 0, 5, 0},
                     {0, -1, 0, 0, 0, 0, 40},
                     {-6, 0, 0, 0, 0, 4, 0},
                     {-12, 0, 0, 0, 0, 0, 30},
                     {0, -5, 0, -4, 0, 0, 8},
                     {0, 0, -40, 0, -30, -8, 0}},
        mi2[7][9] = {{2, 6, 12, 0, 0, 0, 0, 0, 0},
                     {-2, 0, 0, 1, 5, 0, 0, 0, 0},
                     {0, 0, 0, -1, 0, 0, 0, 40, 0},
                     {0, -6, 0, 0, 0, 4, 0, 0, 0},
                     {0, 0, -12, 0, 0, 0, 30, 0, 0},
                     {0, 0, 0, 0, -5, -4, 0, 0, 8},
                     {0, 0, 0, 0, 0, 0, -30, -40, -8}};

    print_matriz(ma1, 5, 5);
    guloso_adjacencia(ma1, 5, 5);

    print_matriz(ma2, 7, 7);
    guloso_adjacencia(ma2, 7, 7);

    print_matriz(mi1, 5, 8);
    guloso_incidencia(mi1, 5, 8);

    print_matriz(mi2, 7, 9);
    guloso_incidencia(mi2, 7, 9);

	return 0;
}
