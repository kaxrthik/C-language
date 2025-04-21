#include <stdio.h>
#define MAX 10
#define INF 9999

int cost[MAX][MAX], dist[MAX], visited[MAX], pred[MAX], n;
int distanceMatrix[MAX][MAX];
int pathMatrix[MAX][MAX]; // For tracking paths

void dijkstra(int start);

void printPath(int src, int dest);

int main() {
    int i, j;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter the cost matrix (9999 for no direct path):\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if(i == j)
                cost[i][j] = 0;
        }
    }

    for(i = 0; i < n; i++) {
        dijkstra(i);
        for(j = 0; j < n; j++) {
            distanceMatrix[i][j] = dist[j];
            pathMatrix[i][j] = pred[j];
        }
    }

    // Final Distance Matrix
    printf("\n🔷 Final Distance Matrix (All-Pairs Shortest Paths):\n\n ");
    for (j = 0; j < n; j++)
        printf("%5d", j);
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("%5d", i);
        for (j = 0; j < n; j++) {
            if (distanceMatrix[i][j] == INF)
                printf("%5s", "INF");
            else
                printf("%5d", distanceMatrix[i][j]);
        }
        printf("\n");
    }

    // Print all paths
    printf("\n\n📌 All Shortest Paths:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if(i != j) {
                printf("Path from %d to %d (Cost: %d): ", i, j, distanceMatrix[i][j]);
                printPath(i, j);
                printf("\n");
            }
        }
    }

    return 0;
}

void dijkstra(int start) {
    int count, mindist, nextnode, i, j;

    for(i = 0; i < n; i++) {
        dist[i] = cost[start][i];
        visited[i] = 0;
        pred[i] = (cost[start][i] != INF && i != start) ? start : -1;
    }

    dist[start] = 0;
    visited[start] = 1;

    for(count = 1; count < n - 1; count++) {
        mindist = INF;
        for(i = 0; i < n; i++) {
            if(dist[i] < mindist && !visited[i]) {
                mindist = dist[i];
                nextnode = i;
            }
        }

        visited[nextnode] = 1;

        for(i = 0; i < n; i++) {
            if(!visited[i] && dist[nextnode] + cost[nextnode][i] < dist[i]) {
                dist[i] = dist[nextnode] + cost[nextnode][i];
                pred[i] = nextnode;
            }
        }
    }
}

void printPath(int src, int dest) {
    int path[MAX], count = 0, temp = dest;

    while(temp != -1 && temp != src) {
        path[count++] = temp;
        temp = pathMatrix[src][temp];
    }

    if(temp == -1) {
        printf("No path");
        return;
    }

    printf("%d", src);
    for(int i = count - 1; i >= 0; i--) {
        printf(" -> %d", path[i]);
    }
}