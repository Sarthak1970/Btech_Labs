#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

// FIFO Page Replacement
int fifo(const vector<int>& pages, int capacity) {
    unordered_set<int> s;
    queue<int> q;
    int faults = 0;

    for (int page : pages) {
        if (s.find(page) == s.end()) {
            if (s.size() == capacity) {
                s.erase(q.front());
                q.pop();
            }
            s.insert(page);
            q.push(page);
            faults++;
        }
    }
    return faults;
}

// LRU Page Replacement
int lru(const vector<int>& pages, int capacity) {
    unordered_map<int, int> lastUsed;
    vector<int> memory;
    int faults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        auto it = find(memory.begin(), memory.end(), page);

        if (it == memory.end()) {
            if (memory.size() == capacity) {
                // Find least recently used
                int lruIndex = 0;
                for (int j = 1; j < memory.size(); j++) {
                    if (lastUsed[memory[j]] < lastUsed[memory[lruIndex]])
                        lruIndex = j;
                }
                memory[lruIndex] = page;
            } else {
                memory.push_back(page);
            }
            faults++;
        }
        lastUsed[page] = i;
    }
    return faults;
}

// Optimal Page Replacement
int optimal(const vector<int>& pages, int capacity) {
    vector<int> memory;
    int faults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];

        if (find(memory.begin(), memory.end(), page) == memory.end()) {
            if (memory.size() < capacity) {
                memory.push_back(page);
            } else {
                int farthest = i + 1;
                int idx = -1;
                for (int j = 0; j < memory.size(); j++) {
                    int k;
                    for (k = i + 1; k < pages.size(); k++) {
                        if (memory[j] == pages[k])
                            break;
                    }
                    if (k > farthest) {
                        farthest = k;
                        idx = j;
                    }
                }
                if (idx == -1) idx = 0;
                memory[idx] = page;
            }
            faults++;
        }
    }
    return faults;
}

int main() {
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int capacity = 4;

    cout << "Page Reference String: ";
    for (int p : pages) cout << p << " ";
    cout << "\nNumber of Frames: " << capacity << "\n\n";

    cout << "FIFO Page Faults    : " << fifo(pages, capacity) << "\n";
    cout << "LRU Page Faults     : " << lru(pages, capacity) << "\n";
    cout << "Optimal Page Faults : " << optimal(pages, capacity) << "\n";

    return 0;
}