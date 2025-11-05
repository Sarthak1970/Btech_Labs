#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NODES 6
#define FRAMES 10

typedef struct {
    int id;
    int hasToken;
} Node;

void passToken(Node nodes[], int *tokenPos) {
    nodes[*tokenPos].hasToken = 0;
    *tokenPos = (*tokenPos + 1) % NODES;
    nodes[*tokenPos].hasToken = 1;
}

void tokenRing(Node nodes[]) {
    int tokenPos = 0;
    nodes[tokenPos].hasToken = 1;

    for (int i = 0; i < FRAMES; i++) {
        printf("\nRound %d:\n", i + 1);
        for (int j = 0; j < NODES; j++) {
            if (nodes[j].hasToken) {
                printf("Node %d has the token. ", nodes[j].id);
                if (rand() % 2 == 0) {
                    int dest = rand() % NODES;
                    while (dest == nodes[j].id) dest = rand() % NODES;
                    printf("Sending frame to Node %d... Delivered!\n", dest);
                } else {
                    printf("No data to send.\n");
                }
                passToken(nodes, &tokenPos);
                break;
            }
        }
    }

    printf("\nSimulation complete. Token circulated among %d nodes.\n", NODES);
}

int main() {
    srand(time(NULL));
    Node nodes[NODES];
    for (int i = 0; i < NODES; i++) {
        nodes[i].id = i;
        nodes[i].hasToken = 0;
    }
    tokenRing(nodes);
    return 0;
}
