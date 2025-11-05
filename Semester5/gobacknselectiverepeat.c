#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_FRAMES 10
#define WINDOW_SIZE 4

typedef struct {
    int id;
    int acked;
    int lost;
} Packet;

int isLost() {
    return rand() % 5 == 0;
}

void printPackets(Packet packets[]) {
    for (int i = 0; i < TOTAL_FRAMES; i++)
        printf("F%d[%s] ", packets[i].id, packets[i].acked ? "ACK" : "----");
    printf("\n");
}

void goBackN(Packet packets[]) {
    int base = 0;
    while (base < TOTAL_FRAMES) {
        printf("\nSending window: ");
        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++)
            printf("%d ", packets[i].id);
        printf("\n");

        int errorAt = -1;
        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            if (isLost()) {
                printf("Frame %d lost!\n", packets[i].id);
                errorAt = i;
                break;
            } else {
                printf("Frame %d acknowledged.\n", packets[i].id);
                packets[i].acked = 1;
            }
        }

        if (errorAt != -1) {
            printf("Retransmitting from frame %d.\n", errorAt);
            for (int i = errorAt; i < TOTAL_FRAMES; i++)
                packets[i].acked = 0;
            base = errorAt;
        } else base += WINDOW_SIZE;

        printPackets(packets);
    }
    printf("\nAll frames sent successfully (Go-Back-N)\n");
}

void selectiveRepeat(Packet packets[]) {
    int base = 0;
    while (1) {
        int allAcked = 1;
        printf("\nSending window: ");
        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++)
            printf("%d ", packets[i].id);
        printf("\n");

        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            if (!packets[i].acked) {
                if (isLost()) printf("Frame %d lost.\n", packets[i].id);
                else {
                    printf("Frame %d acknowledged.\n", packets[i].id);
                    packets[i].acked = 1;
                }
            }
        }

        while (base < TOTAL_FRAMES && packets[base].acked) base++;

        for (int i = 0; i < TOTAL_FRAMES; i++)
            if (!packets[i].acked) allAcked = 0;

        printPackets(packets);
        if (allAcked) break;
    }
    printf("\nAll frames sent successfully (Selective Repeat)\n");
}

int main() {
    srand(time(NULL));
    Packet packets[TOTAL_FRAMES];
    for (int i = 0; i < TOTAL_FRAMES; i++) {
        packets[i].id = i;
        packets[i].acked = 0;
        packets[i].lost = 0;
    }

    int choice;
    printf("1. Go-Back-N\n2. Selective Repeat\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1) goBackN(packets);
    else if (choice == 2) {
        for (int i = 0; i < TOTAL_FRAMES; i++) packets[i].acked = 0;
        selectiveRepeat(packets);
    } else printf("Invalid choice.\n");

    return 0;
}
