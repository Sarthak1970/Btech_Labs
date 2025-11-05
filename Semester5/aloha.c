#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_FRAMES 20
#define USERS 5

typedef struct {
    int id;
    int sent;
    int success;
} Frame;

int randomUser() {
    return rand() % USERS;
}

int collisionChance() {
    return rand() % 100 < 30;
}

void printStats(Frame frames[]) {
    int success = 0;
    for (int i = 0; i < TOTAL_FRAMES; i++)
        if (frames[i].success) success++;
    printf("Success: %d | Collisions: %d | Efficiency: %.2f%%\n",
           success, TOTAL_FRAMES - success, (success * 100.0) / TOTAL_FRAMES);
}

void pureAloha(Frame frames[]) {
    for (int i = 0; i < TOTAL_FRAMES; i++) {
        int sender = randomUser();
        printf("User %d sending Frame %d... ", sender, frames[i].id);
        if (collisionChance()) {
            printf("Collision! Frame %d lost.\n", frames[i].id);
            frames[i].success = 0;
        } else {
            printf("Sent successfully.\n");
            frames[i].success = 1;
        }
    }
    printf("\nResults (Pure ALOHA):\n");
    printStats(frames);
}

void slottedAloha(Frame frames[]) {
    for (int i = 0; i < TOTAL_FRAMES; i++) {
        int sender = randomUser();
        printf("Slot %d: User %d transmitting... ", i, sender);
        if (collisionChance()) {
            printf("Collision! Frame %d lost.\n", frames[i].id);
            frames[i].success = 0;
        } else {
            printf("Sent successfully.\n");
            frames[i].success = 1;
        }
    }
    printf("\nResults (Slotted ALOHA):\n");
    printStats(frames);
}

int main() {
    srand(time(NULL));
    Frame frames[TOTAL_FRAMES];
    for (int i = 0; i < TOTAL_FRAMES; i++) {
        frames[i].id = i;
        frames[i].sent = 0;
        frames[i].success = 0;
    }

    int choice;
    printf("1. Pure ALOHA\n2. Slotted ALOHA\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1) pureAloha(frames);
    else if (choice == 2) slottedAloha(frames);
    else printf("Invalid choice.\n");

    return 0;
}
