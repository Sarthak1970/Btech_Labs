#include <stdio.h>

#define INF 999
#define N 4   

int cost[N][N] = {
    {0,   1,   3, INF},
    {1,   0,   1,   4},
    {3,   1,   0,   2},
    {INF, 4,   2,   0}
};

int dist[N][N];
int nextHop[N][N];

void initialize() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dist[i][j] = cost[i][j];
            if (cost[i][j] != INF && i != j)
                nextHop[i][j] = j;
            else
                nextHop[i][j] = -1;
        }
    }
}

int runDVR() {
    int updated = 0;

    for (int router = 0; router < N; router++) {
        for (int dest = 0; dest < N; dest++) {
            for (int via = 0; via < N; via++) {
                if (dist[router][dest] > cost[router][via] + dist[via][dest]) {
                    dist[router][dest] = cost[router][via] + dist[via][dest];
                    nextHop[router][dest] = via;
                    updated = 1;
                }
            }
        }
    }
    return updated;
}

void printTables() {
    for (int r = 0; r < N; r++) {
        printf("\nRouting table for Router %d:\n", r);
        printf("Dest\tCost\tNextHop\n");
        for (int d = 0; d < N; d++) {
            printf("%d\t%d\t%d\n", d, dist[r][d], nextHop[r][d]);
        }
    }
}

int main() {
    initialize();
    printf("Initial Routing Tables:\n");
    printTables();

    while (runDVR());

    printf("\nFinal Routing Tables After Convergence:\n");
    printTables();

    return 0;
}
