#include <stdio.h>
int dist[50][50], temp[50][50], n, i, j, k, l, x;
void dvr();
int main()
{
    printf("\nEnter the number of nodes : ");
    scanf("%d", &n);
    printf("\nEnter the distance matrix :\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &dist[i][j]);
            dist[i][i] = 0;
            temp[i][j] = j;
        }
        printf("\n");
    }
    dvr();
    return 0;
}
void dvr()
{
    for (l = 0; l < n; l++)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                for (k = 0; k < n; k++)
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        temp[i][j] = k;
                    }
    for (i = 0; i < n; i++)
    {
        printf("Node %d: \n",i+1);
        for (j = 0; j < n; j++)
        {
            printf("%d\n", dist[i][j]);
        }
        printf("\n");
    }
    return 0;
}