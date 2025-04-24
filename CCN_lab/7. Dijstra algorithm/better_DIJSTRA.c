#include <stdio.h>
#define INT_MAX 99
#define MAX_VERTICES 100
int minDistance(int dist[], int sptSet[], int vertices) // Function to find the vertex with the minimum distance value
{
    int min = INT_MAX, minIndex;
    for (int v = 0; v < vertices; v++)
    {
        if (!sptSet[v] && dist[v] < min)
        {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}
void printSolution(int dist[], int vertices) // Function to print the constructed distance array
{
    printf("Vertex \tDistance from Source\n");
    for (int i = 0; i < vertices; i++)
        printf(" %d \t %d\n", i, dist[i]);
}
void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int src, int vertices) // Function to implement Dijkstra's algorithm for a given graph and source vertex
{
    int dist[MAX_VERTICES];   // The output array dist[i] holds the shortest distance from src to i
    int sptSet[MAX_VERTICES]; // sptSet[i] will be true if vertex i is included in the shortest path tree or the shortest distance from src to i is finalized
    for (int i = 0; i < vertices; i++)  // Initialize all distances as INFINITE and sptSet[] as false
    {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }
    dist[src] = 0; // Distance from source vertex to itself is always 0
    for (int count = 0; count < vertices - 1; count++) // Find the shortest path for all vertices
    {
        // Pick the minimum distance vertex from the set of vertices not yet processed.
        int u = minDistance(dist, sptSet, vertices); // u is always equal to src in the first iteration.
        sptSet[u] = 1; // Mark the picked vertex as processed
        for (int v = 0; v < vertices; v++) // Update dist value of the adjacent vertices of the picked vertex.
        {
            // Update dist[v] only if it is not in the sptSet, there is an edge from u to v,
            // and the total weight of path from src to v through u is smaller than the current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
        }
    }
    printSolution(dist, vertices); // Print the constructed distance array
}
int main()
{
    int vertices, check;
    printf("Input the number of vertices: "); // Input the number of vertices
    scanf("%d", &vertices);
    if (vertices <= 0 || vertices > MAX_VERTICES)
    {
        printf("Invalid number of vertices. Exiting...\n");
        return 1;
    }
    int graph[MAX_VERTICES][MAX_VERTICES];
    printf("Input the adjacency matrix for the graph (use INT_MAX for infinity):\n"); // Input the adjacency matrix representing the weighted graph
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
            scanf("%d", &graph[i][j]);
    }
    while (check)
    {
        int source;
        printf("Input the source vertex: "); // Input the source vertex
        scanf("%d", &source);
        if (source < 0 || source >= vertices)
        {
            printf("Invalid source vertex. Exiting...\n");
            return 1;
        }
        dijkstra(graph, source, vertices); // Perform Dijkstra's algorithm
        printf("check for other source: 1 for YES | 0 for NO : ");
        scanf("%d", &check);
        if (check == 0)
            break;
    }
    return 0;
}