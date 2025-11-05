#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_FRAMES 15
#define USERS 5

typedef struct {
    int id;
    int success;
    int collisions;
} Frame;

int randomUser() {
    return rand() % USERS;
}

int channelBusy() {
    return rand() % 100 < 40; // 40% chance channel is busy
}

int collisionOccurs() {
    return rand() % 100 < 25; // 25% chance of collision
}

void printStats(Frame frames[]) {
    int success = 0, collisions = 0;
    for (int i = 0; i < TOTAL_FRAMES; i++) {
        if (frames[i].success) success++;
        collisions += frames[i].collisions;
    }
    printf("Success: %d | Collisions: %d | Efficiency: %.2f%%\n",
           success, collisions, (success * 100.0) / TOTAL_FRAMES);
}

void csma_cd(Frame frames[]) {
    for (int i = 0; i < TOTAL_FRAMES; i++) {
        int sender = randomUser();
        printf("User %d sensing channel... ", sender);
        if (channelBusy()) {
            printf("Busy. Waiting...\n");
            continue;
        }
        printf("Transmitting frame %d... ", frames[i].id);
        if (collisionOccurs()) {
            printf("Collision detected! Backing off.\n");
            frames[i].collisions++;
            i--; // resend same frame
        } else {
            printf("Sent successfully.\n");
            frames[i].success = 1;
        }
    }
    printf("\nResults (CSMA/CD):\n");
    printStats(frames);
}

void csma_ca(Frame frames[]) {
    for (int i = 0; i < TOTAL_FRAMES; i++) {
        int sender = randomUser();
        printf("User %d checking channel... ", sender);
        if (channelBusy()) {
            printf("Busy. Waiting before retry.\n");
            continue;
        }
        printf("Sending RTS... ");
        if (collisionOccurs()) {
            printf("Collision on RTS! Waiting.\n");
            frames[i].collisions++;
            i--;
            continue;
        }
        printf("CTS received. Transmitting frame %d... ", frames[i].id);
        if (collisionOccurs()) {
            printf("Collision during data! Resending.\n");
            frames[i].collisions++;
            i--;
        } else {
            printf("Frame sent successfully.\n");
            frames[i].success = 1;
        }
    }
    printf("\nResults (CSMA/CA):\n");
    printStats(frames);
}

int main() {
    srand(time(NULL));
    Frame frames[TOTAL_FRAMES];
    for (int i = 0; i < TOTAL_FRAMES; i++) {
        frames[i].id = i;
        frames[i].success = 0;
        frames[i].collisions = 0;
    }

    int choice;
    printf("1. CSMA/CD\n2. CSMA/CA\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1) csma_cd(frames);
    else if (choice == 2) csma_ca(frames);
    else printf("Invalid choice.\n");

    return 0;
}
