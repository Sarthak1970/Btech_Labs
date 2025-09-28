#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_FRAMES 100
#define MAX_DATA 50

typedef struct {
    int seq;
    char data[MAX_DATA];
} Frame;

typedef struct {
    int expectedSeq;
} Receiver;

typedef struct {
    Frame frames[MAX_FRAMES];
    int nextSeq;
    int frameCount;
} Sender;

void initReceiver(Receiver *r) {
    r->expectedSeq = 0;
}

int receiveFrame(Receiver *r, Frame f) {
    int chance = rand() % 5;
    if (chance == 0) {
        printf("Receiver: Frame lost or corrupted\n");
        return 0;
    }

    if (f.seq == r->expectedSeq) {
        printf("Receiver: Frame received, data = %s\n", f.data);
        r->expectedSeq = 1 - r->expectedSeq;
        return 1;
    } else {
        printf("Receiver: Duplicate frame ignored\n");
        return 1;
    }
}

int getExpectedSeq(Receiver *r) {
    return r->expectedSeq;
}

void initSender(Sender *s, char messages[][MAX_DATA], int count) {
    s->nextSeq = 0;
    s->frameCount = count;
    for (int i = 0; i < count; i++) {
        s->frames[i].seq = i % 2;
        strncpy(s->frames[i].data, messages[i], MAX_DATA - 1);
        s->frames[i].data[MAX_DATA - 1] = '\0';
    }
}

void sendFrames(Sender *s, Receiver *r) {
    int i = 0;
    while (i < s->frameCount) {
        printf("Sender: Sending Frame %d (Seq=%d, Data=%s)\n",
               i + 1, s->frames[i].seq, s->frames[i].data);

        int ack = receiveFrame(r, s->frames[i]);
        if (ack) {
            printf("Sender: ACK received\n");
            i++;
        } else {
            printf("Sender: Timeout, retransmitting Frame %d\n", i + 1);
        }
    }
    printf("All frames sent successfully\n");
}

int main() {
    srand(time(0));

    char data[][MAX_DATA] = {"Stop", "And", "Wait", "Algorithm"};
    int dataCount = sizeof(data) / sizeof(data[0]);

    Sender sender;
    Receiver receiver;

    initSender(&sender, data, dataCount);
    initReceiver(&receiver);

    sendFrames(&sender, &receiver);

    return 0;
}