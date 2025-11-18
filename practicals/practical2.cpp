//WAP to simulate selective repeat simulation . Enter no. of frames,loss prob,window size,specific frame to drop , Retransmit only the frame and maintain receiver buffer and out of order frames.

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

struct Packet {
    int id;
    bool sent = false;
    bool ack = false;
    bool buffered = false;
    int attempts = 0;
};

float randomValue() {
    return (float)rand() / RAND_MAX;
}

bool transmit(Packet &pkt, int dropFrame, bool &dropUsed, float lossProb) {
    pkt.attempts++;
    pkt.sent = true;

    if (pkt.id == dropFrame && !dropUsed) {
        dropUsed = true;
        return false;
    }
    if (randomValue() < lossProb) return false;

    return true;
}

void receiver(int frameId, vector<Packet> &buffer, int &expected, vector<bool> &delivered) {
    if (frameId < 0 || frameId >= (int)buffer.size()) return;
    if (delivered[frameId]) return;

    buffer[frameId].buffered = true;
    cout << "Receiver: buffered frame " << frameId << "\n";

    while (expected < (int)buffer.size() &&
           buffer[expected].buffered &&
           !delivered[expected]) 
    {
        delivered[expected] = true;
        cout << "Receiver: delivered frame " << expected << " to application\n";
        expected++;
    }
}

int main() {
    srand((unsigned)time(0));

    int totalFrames, windowSize, dropFrame;
    float lossProb;

    cout << "Enter number of frames: ";
    cin >> totalFrames;

    cout << "Enter loss probability (0.0 - 1.0): ";
    cin >> lossProb;

    cout << "Enter window size: ";
    cin >> windowSize;

    cout << "Enter specific frame number to drop: ";
    cin >> dropFrame;

    vector<Packet> sender(totalFrames);
    vector<Packet> receiverBuf(totalFrames);
    vector<bool> delivered(totalFrames, false);

    for (int i = 0; i < totalFrames; ++i) {
        sender[i].id = i;
        receiverBuf[i].id = i;
    }

    int base = 0;
    int expectedFrame = 0;
    bool dropUsed = false;
    int round = 1;

    cout << "\nSelective Repeat Simulation Starting\n\n";

    while (base < totalFrames) {
        cout << "Round " << round
             << " sender window [" 
             << base << " .. " 
             << min(base + windowSize - 1, totalFrames - 1)
             << "]\n";

        for (int i = base; i < min(base + windowSize, totalFrames); ++i) {
            if (sender[i].ack) continue;

            cout << "Sender: sending frame " << i
                 << " (attempt " << sender[i].attempts + 1 << ") ... ";

            bool ok = transmit(sender[i], dropFrame, dropUsed, lossProb);

            if (!ok) {
                cout << "FAILED\n";
                continue;
            }

            cout << "SUCCESS\n";
            cout << "Channel: frame " << i << " reached receiver\n";

            receiver(i, receiverBuf, expectedFrame, delivered);

            if (receiverBuf[i].buffered) {
                cout << "Receiver: ACK " << i << "\n";
                cout << "Channel: sender got ACK " << i << "\n";
                sender[i].ack = true;
            }
        }

        int oldBase = base;
        while (base < totalFrames && sender[base].ack) base++;

        if (base != oldBase) {
            cout << "Sender: window moved to [" 
                 << base << " .. " 
                 << min(base + windowSize - 1, totalFrames - 1)
                 << "]\n";
        }

        for (int i = base; i < min(base + windowSize, totalFrames); ++i) {
            if (!sender[i].ack && sender[i].attempts > 0) {
                cout << "Sender: will retransmit frame " << i << " next round\n";
            }
        }

        bool stuck = true;
        for (auto &p : sender) {
            if (p.attempts < 20) stuck = false;
        }

        if (stuck) {
            cout << "\nSimulation stopped: too many attempts.\n";
            break;
        }

        cout << "\n";
        round++;
    }

    cout << "--- Simulation Finished ---\n";
    cout << "Frames:\n";

    for (int i = 0; i < totalFrames; ++i) {
        cout << "Frame " << i
             << " | attempts=" << sender[i].attempts
             << " | ack=" << (sender[i].ack ? "YES" : "NO")
             << " | buffered=" << (receiverBuf[i].buffered ? "YES" : "NO")
             << " | delivered=" << (delivered[i] ? "YES" : "NO")
             << "\n";
    }

    return 0;
}
