#include <stdio.h>
#include <stdlib.h>

int ** createMatrix(int numberOfRows, int numberOfColumns) {
    int ** matrix = (int *)malloc(sizeof(int) * numberOfRows);

    for(int i = 0; i < numberOfRows; i++) {
        matrix[i] = (int *)malloc(sizeof(int) * numberOfColumns);
    }

    return matrix;
}

int main()
{
    int quantityOfNodes;
    int nodeValue;
    int option;
    int isDirected;
    int isWeighted;
    int relation;
    int edgeWeight;

    int * nodes = (int *)malloc(sizeof(int) * quantityOfNodes);
    int ** adjacencyMatrix = NULL;
    int ** weightMatrix = NULL;

    do {
        printf("0 - Encerrar o programa\n1 - Construir o grafo\n2 - Impressao  da  matriz  de  adjacencias\n3 - Impressao  de  percursos\n4 - Ordenacao Topologica\n5 - Caminho  de  distancia  minima\n");

        printf("\nDigite a opcao desejada: ");
        scanf("%d", &option);

        switch(option) {
            case 1:
                printf("\nDigite a quantidade de nos que o grafo vai ter: ");
                scanf("%d", &quantityOfNodes);

                printf("\n");

                for(int i = 0; i < quantityOfNodes; i++) {
                    printf("Digite o valor do no %d: ", i + 1);
                    scanf("%d", &nodeValue);
                    nodes[i] = nodeValue;
                }

                printf("\nO grafo sera direcionado ? (1 - Sim, 0 - Nao) ");
                scanf("%d", &isDirected);

                printf("O grafo sera ponderado ? (1 - Sim, 0 - Nao) ");
                scanf("%d", &isWeighted);

                adjacencyMatrix = createMatrix(quantityOfNodes, quantityOfNodes);

                if(isWeighted) {
                    weightMatrix = createMatrix(quantityOfNodes, quantityOfNodes);
                }

                printf("\n");

                for(int i = 0; i < quantityOfNodes; i++) {
                    printf("Digite os adjacentes do no %d\n\n", nodes[i]);
                    for(int j = 0; j < quantityOfNodes; j++) {
                        printf("O no %d sera adjacente ao no %d ? (1 - Sim, 0 - Nao) ", nodes[i], nodes[j]);
                        scanf("%d", &relation);

                        adjacencyMatrix[i][j] = relation;

                        if(weightMatrix) {
                            printf("Digite o peso da aresta entre o no %d e o no %d: ", nodes[i], nodes[j]);
                            scanf("%d", &edgeWeight);
                            weightMatrix[i][j] = edgeWeight;
                        }
                    }
                    printf("\n");
                }

                printf("\n");
            break;
            case 2:
                printf("\nMatriz de ajacencias\n\n");

                for(int i = 0; i < quantityOfNodes; i++) {
                    printf("%d | ", nodes[i]);
                    for(int j = 0; j < quantityOfNodes; j++) {
                        printf("%d ", adjacencyMatrix[i][j]);
                    }
                    printf("\n");
                }

                if(isWeighted) {
                    printf("\nMatriz de pesos\n\n");

                    for(int i = 0; i < quantityOfNodes; i++) {
                        printf("%d | ", nodes[i]);
                        for(int j = 0; j < quantityOfNodes; j++) {
                            printf("%d ", weightMatrix[i][j]);
                        }
                        printf("\n");
                    }
                }

                printf("\n");
            break;
        }
    } while(option != 0);
}
