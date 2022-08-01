#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define INFINITY INT_MAX

int ** createMatrix(int numberOfRows, int numberOfColumns) {
    int i = 0;
    int ** matrix = (int **)malloc(sizeof(int*[numberOfRows]));

	for(i; i < numberOfRows; i++) {
		matrix[i] = (int *) malloc(sizeof(int[numberOfColumns]));
    }

    return matrix;
}

int isValidToApplyDijkstra(int ** graph, int numbersOfNode) {
    for(int i = 0; i < numbersOfNode; i++) {
        for(int j = 0; i < numbersOfNode; j++) {
            if((i == j && graph[i][j] != INFINITY) || graph[i][j] < 0) return 0;
        }
    }

    return 1;
}

int findIndex(int item, int items[], int numberOfItems) {
    for(int i = 0; i < numberOfItems; i++)
        if(items[i] == item) return i;

    return -1;
}

int minDistance(int distance[], int visited[], int numbersOfNodes) {
    int min = INFINITY;
    int min_index = INFINITY;

    for(int i = 0; i < numbersOfNodes; i++) {
        if(!visited[i] && distance[i] <= min) {
            min = distance[i];
            min_index = i;
        }
    }

    return min_index;
}

void dijkstra(int ** graph, int src, int end, int nodes[], int numbersOfNode) {
    int distance[numbersOfNode];
    int visited[numbersOfNode];
    int path[numbersOfNode];

    int indexStartNode = findIndex(src, nodes, numbersOfNode);
    int indexEndNode = findIndex(end, nodes, numbersOfNode);

    for(int i = 0; i < numbersOfNode; i++) {
        distance[i] = INFINITY;
        path[i] = INFINITY;
        visited[i] = 0;
    }

    path[indexStartNode] = src;
    path[indexEndNode] = end;
    distance[indexStartNode] = 0;

    for(int i = 0; i < numbersOfNode - 1; i++) {
        int md = minDistance(distance, visited, numbersOfNode);
        visited[md] = 1;

        for(int j = 0; j < numbersOfNode; j++) {
            if(!visited[j] && graph[md][j] != INFINITY && distance[md] != INFINITY && distance[md] + graph[md][j] < distance[j]) {
                distance[j] = distance[md] + graph[md][j];
                path[md] = nodes[md];
            }
        }
    }

    printf("caminho: ");

    for(int i = 0; i < numbersOfNode; i++) {
        if(path[i] != INFINITY)
            (i == (numbersOfNode - 1)) ? printf("%d", path[i]) : printf("%d,", path[i]);
    }

    printf("\n");
}

void freeMatrix(int ** matrix, int numberOfRows) {
    for(int i = 0; i < numberOfRows; i++)
		free(matrix[i]);
	free(matrix);
}

void createUnDirectedGraph(int ** matrix, int * nodes, int isWeighted, int quantityOfNodes) {
    int relation, weight;

    for(int i = 0; i < quantityOfNodes; i++) {
        printf("\nDigite os nos adjacentes ao no %d (nem todos os valores serao perguntados) \n\n", nodes[i]);
        for(int j = 0; j < quantityOfNodes; j++) {

            if(j >= i) {
                printf("\nO no %d esta conectado com o no %d? (0 - Nao, 1 - Sim): ", nodes[i], nodes[j]);
                scanf("%d", &relation);

                if(isWeighted) {
                    if(relation) {
                        printf("\nDigite o peso da aresta entre o no %d e o no %d: ",  nodes[i], nodes[j]);
                        scanf("%d", &weight);
                        matrix[i][j] = weight;
                        matrix[j][i] = weight;
                    } else {
                        matrix[i][j] = INFINITY;
                        matrix[j][i] = INFINITY;
                    }
                } else {
                    if(relation) {
                        matrix[i][j] = 1;
                        matrix[j][i] = 1;
                    } else {
                        matrix[i][j] = 0;
                        matrix[j][i] = 0;
                    }
                }
            }
        }
    }

    printf("\n");
}

void createDirectedGraph(int ** matrix, int * nodes ,int isWeighted, int quantityOfNodes) {
    int relation, weight;

    for(int i = 0; i < quantityOfNodes; i++) {
        printf("\nDigite os nos adjacentes ao no %d\n\n", nodes[i]);
        for(int j = 0; j < quantityOfNodes; j++) {
            printf("\nO no %d esta conectado com o no %d? (0 - Nao, 1 - Sim): ", nodes[i], nodes[j]);
            scanf("%d", &relation);

            if(isWeighted) {
                if(relation) {
                    printf("\nDigite o peso da aresta entre o no %d e o no %d: ",  nodes[i], nodes[j]);
                    scanf("%d", &weight);
                    matrix[i][j] = weight;
                } else {
                    matrix[i][j] = INFINITY;
                }
            } else {
                if(relation) {
                    matrix[i][j] = 1;
                } else {
                    matrix[i][j] = 0;
                }
            }
        }
    }

    printf("\n");
}

void initArray(int * array, int size) {
    for(int i = 0; i < size; i++) {
        array[i] = 0;
    }
}

void showMatrix(int ** matrix, int * nodes, int quantityOfNodes) {
    printf("\n\n\n");
    for(int i = 0; i < quantityOfNodes; i++) {
        printf("\t%d", nodes[i]);
    }
    printf("\n\n\n");
    for(int i = 0; i < quantityOfNodes; i++) {
        printf("%d", nodes[i]);

        for(int j = 0; j < quantityOfNodes; j++) {
            printf("\t%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
}

void depthFirstSearch(int ** graph, int * nodes, int * visited, int v, int size, int isWeighted) {
    int i = 0;
    printf("%d ", nodes[v]);
    visited[v] = 1;
    for(i; i < size; i++) { 
        if(isWeighted) {
            if( graph[v][i] != INFINITY && visited[i] == 0 ) {
                depthFirstSearch(graph, nodes, visited, i, size, isWeighted);
            }
        } else {
            if( graph[v][i] == 1 && visited[i] == 0 ) {
                depthFirstSearch(graph, nodes, visited, i, size, isWeighted);
            }
        }
    }
}

void topologicalSorting(int ** graph, int * nodes, int * visited, int v, int size, int isWeighted) {}

void breadthFirstSearch(int ** graph, int * nodes, int * visited, int isWeighted, int size, int v) {
    int queue[size];
    int start = 0;
    int end = 0;
    int node;
    int aux;

    queue[0] = v;
    end++;
    visited[v] = 1;

    while(start != end) {
        node = nodes[queue[start]];
        aux = queue[start];

        start++; 
        printf("%d ", node);

        for(int i = 0; i < size; i++) {
            if(isWeighted) {
                if(graph[aux][i] != INFINITY && visited[i] == 0) {
                    queue[end] = i;
                    end++;
                    visited[i] = 1;
                }
            } else {
                if(graph[aux][i] == 1 && visited[i] == 0) {
                    queue[end] = i;
                    end++;
                    visited[i] = 1;
                }
            }
        }
    }

}

int main()
{
    int startNode,
        endNode,
        quantityOfNodes,
        nodeValue,
        option,
        isDirected,
        isWeighted,
        searchType;
        
    int * nodes = NULL;
    int * visited = NULL;
    int ** adjacencyMatrix = NULL;

    do {
        printf("0 - Encerrar o programa\n1 - Construir o grafo\n2 - Impressao  da  matriz  de  adjacencias\n3 - Impressao  de  percursos\n4 - Ordenacao Topologica\n5 - Caminho  de  distancia  minima\n");

        printf("\nDigite a opcao desejada: ");
        scanf("%d", &option);

        switch(option) {
            case 1:
                printf("\nDigite a quantidade de nos do grafo: ");
                scanf("%d", &quantityOfNodes);

                if(nodes != NULL) {
                    free(nodes);
                    nodes = NULL;
                }
                nodes = (int *) malloc(sizeof(int[quantityOfNodes]));

                if(adjacencyMatrix != NULL) {
                    freeMatrix(adjacencyMatrix, quantityOfNodes);
                    adjacencyMatrix = NULL;
                }

                adjacencyMatrix = createMatrix(quantityOfNodes, quantityOfNodes);

                for(int i = 0; i < quantityOfNodes; i++) {
                    printf("\nDigite o valor do no %d: ", i);
                    scanf("%d", &nodes[i]);
                }

                printf("\nO grafo vai ser direcionado? (0 - Nao, 1 - Sim): ");
                scanf("%d", &isDirected);

                printf("\nO grafo vai ser ponderado? (0 - Nao, 1 - Sim): ");
                scanf("%d", &isWeighted);

                if(isDirected) {
                    createDirectedGraph(adjacencyMatrix, nodes, isWeighted, quantityOfNodes);
                } else {
                    createUnDirectedGraph(adjacencyMatrix, nodes, isWeighted, quantityOfNodes);
                }

                printf("\n");
            break;
            case 2:

                if(adjacencyMatrix != NULL) {
                    showMatrix(adjacencyMatrix, nodes, quantityOfNodes);
                } else {
                    printf("\nVoce nao criou seu grafo ainda\n");
                }

                printf("\n");
            break;
            case 5:
                if(!isValidToApplyDijkstra(adjacencyMatrix, quantityOfNodes)) {
                    printf("\nGrafo invalido para aplicar dijkstra!\n\n");
                    break;
                }

                printf("\nDigite o no inicial da busca: ");
                scanf("%d", &startNode);

                printf("Digite o no final da busca: ");
                scanf("%d", &endNode);


                printf("\n");

                dijkstra(adjacencyMatrix, startNode, endNode, nodes, quantityOfNodes);

                printf("\n");
            break;
            case 3:

                if(adjacencyMatrix != NULL) {
                    printf("\nDigite o tipo de busca que voce deseja executar (6 - para busca em profundidade, 7 - para busca em largura): ");
                    scanf("%d", &searchType);

                    if(visited != NULL) {
                        free(visited);
                        visited = NULL;
                    }
                    visited = (int *) malloc(sizeof(int[quantityOfNodes]));
                    initArray(visited, quantityOfNodes);

                    if(searchType == 6) {
                        printf("\n");
                        depthFirstSearch(adjacencyMatrix, nodes, visited, 0, quantityOfNodes, isWeighted);
                        
                        for(int i = 0; i < quantityOfNodes; i++) {
                            if(visited[i] == 0) {
                                printf("%d ", nodes[i]);
                            }
                        }

                        printf("\n");
                    } 

                    if(searchType == 7) {
                        printf("\n");
                        
                        breadthFirstSearch(adjacencyMatrix, nodes, visited, isWeighted, quantityOfNodes, 0);
                        
                        for(int i = 0; i < quantityOfNodes; i++) {
                            if(visited[i] == 0) {
                                printf("%d ", nodes[i]);
                            }
                        }
                        
                        printf("\n");
                    }

                } else {
                    printf("\nVoce nao criou seu grafo ainda\n");
                }

                printf("\n");
            break;
            case 4:

            break;
        }
    } while(option != 0);
}
