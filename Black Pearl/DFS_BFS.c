#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10

struct Graph {
    int vertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    struct Node* adjList[MAX_VERTICES];
};

struct Node {
    int vertex;
    struct Node* next;
};

void initGraph(struct Graph* G, int V) {
    G->vertices = V;
    for (int i = 0; i < V; i++) {
        G->adjList[i] = NULL;
        for (int j = 0; j < V; j++) {
            G->adjMatrix[i][j] = 0;
        }
    }
}

void addEdge(struct Graph* G, int start, int end) {
    G->adjMatrix[start][end] = 1;
    G->adjMatrix[end][start] = 1;

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = end;
    newNode->next = G->adjList[start];
    G->adjList[start] = newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = start;
    newNode->next = G->adjList[end];
    G->adjList[end] = newNode;
}

void dfsMatrix(struct Graph* G, int start, int visited[MAX_VERTICES]) {
    printf("%d ", start);
    visited[start] = 1;

    for (int i = 0; i < G->vertices; i++) {
        if (G->adjMatrix[start][i] && !visited[i]) {
            dfsMatrix(G, i, visited);
        }
    }
}

void dfsList(struct Graph* G, int start, int visited[MAX_VERTICES]) {
    printf("%d ", start);
    visited[start] = 1;

    struct Node* node = G->adjList[start];
    while (node != NULL) {
        if (!visited[node->vertex]) {
            dfsList(G, node->vertex, visited);
        }
        node = node->next;
    }
}

void bfsMatrix(struct Graph* G, int start, int visited[MAX_VERTICES]) {
    int queue[MAX_VERTICES];
    int front = -1, rear = -1;

    printf("%d ", start);
    visited[start] = 1;
    queue[++rear] = start;

    while (front != rear) {
        start = queue[++front];
        for (int i = 0; i < G->vertices; i++) {
            if (G->adjMatrix[start][i] && !visited[i]) {
                printf("%d ", i);
                visited[i] = 1;
                queue[++rear] = i;
            }
        }
    }
}

void bfsList(struct Graph* G, int start, int visited[MAX_VERTICES]) {
    int queue[MAX_VERTICES];
    int front = -1, rear = -1;

    printf("%d ", start);
    visited[start] = 1;
    queue[++rear] = start;

    while (front != rear) {
        start = queue[++front];
        struct Node* node = G->adjList[start];
        while (node != NULL) {
            if (!visited[node->vertex]) {
                printf("%d ", node->vertex);
                visited[node->vertex] = 1;
                queue[++rear] = node->vertex;
            }
            node = node->next;
        }
    }
}

int main() {
    struct Graph graph;
    int choice, start, end;

    initGraph(&graph, MAX_VERTICES);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add an edge\n");
        printf("2. Perform DFS using Adjacency Matrix\n");
        printf("3. Perform DFS using Adjacency List\n");
        printf("4. Perform BFS using Adjacency Matrix\n");
        printf("5. Perform BFS using Adjacency List\n");
        printf("6. Quit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the start vertex: ");
                scanf("%d", &start);
                printf("Enter the end vertex: ");
                scanf("%d", &end);
                addEdge(&graph, start, end);
                break;
            case 2:
                printf("Enter the starting vertex for DFS: ");
                scanf("%d", &start);
                int visitedMatrix[MAX_VERTICES] = {0};
                printf("DFS using Adjacency Matrix: ");
                dfsMatrix(&graph, start, visitedMatrix);
                break;
            case 3:
                printf("Enter the starting vertex for DFS: ");
                scanf("%d", &start);
                int visitedList[MAX_VERTICES] = {0};
                printf("DFS using Adjacency List: ");
                dfsList(&graph, start, visitedList);
                break;
            case 4:
                printf("Enter the starting vertex for BFS: ");
                scanf("%d", &start);
                int visitedBFSMatrix[MAX_VERTICES] = {0};
                printf("BFS using Adjacency Matrix: ");
                bfsMatrix(&graph, start, visitedBFSMatrix);
                break;
            case 5:
                printf("Enter the starting vertex for BFS: ");
                scanf("%d", &start);
                int visitedBFSList[MAX_VERTICES] = {0};
                printf("BFS using Adjacency List: ");
                bfsList(&graph, start, visitedBFSList);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
