#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

// FIFO Page Replacement
int fifo(int frames, vector<int> pages) {
    unordered_set<int> s;
    queue<int> q;
    int pageFaults = 0;

    for (int page : pages) {
        if (s.find(page) == s.end()) {
            // Page fault
            pageFaults++;
            if (s.size() == frames) {
                int old = q.front();
                q.pop();
                s.erase(old);
            }
            s.insert(page);
            q.push(page);
        }
    }

    return pageFaults;
}

// LRU Page Replacement
int lru(int frames, vector<int> pages) {
    unordered_set<int> s;
    unordered_map<int, int> lastUsed;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); ++i) {
        int page = pages[i];
        if (s.find(page) == s.end()) {
            // Page fault
            pageFaults++;
            if (s.size() == frames) {
                // Find least recently used
                int lruPage = -1, lruTime = i;
                for (int p : s) {
                    if (lastUsed[p] < lruTime) {
                        lruTime = lastUsed[p];
                        lruPage = p;
                    }
                }
                s.erase(lruPage);
            }
            s.insert(page);
        }
        lastUsed[page] = i;
    }

    return pageFaults;
}

// Optimal Page Replacement
int optimal(int frames, vector<int> pages) {
    unordered_set<int> s;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); ++i) {
        int page = pages[i];
        if (s.find(page) == s.end()) {
            // Page fault
            pageFaults++;
            if (s.size() < frames) {
                s.insert(page);
            } else {
                // Replace the page that is not used for longest time
                int farthest = i + 1, victim = -1;
                for (int p : s) {
                    int j;
                    for (j = i + 1; j < pages.size(); ++j) {
                        if (pages[j] == p)
                            break;
                    }
                    if (j > farthest) {
                        farthest = j;
                        victim = p;
                    }
                }
                if (victim == -1) victim = *s.begin();
                s.erase(victim);
                s.insert(page);
            }
        }
    }

    return pageFaults;
}

int main() {
    int frames, n;
    cout << "Enter number of frames: ";
    cin >> frames;

    cout << "Enter number of page references: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter the page reference string:\n";
    for (int i = 0; i < n; ++i)
        cin >> pages[i];

    cout << "\n--- Page Replacement Results ---\n";
    cout << "FIFO Page Faults:     " << fifo(frames, pages) << endl;
    cout << "LRU Page Faults:      " << lru(frames, pages) << endl;
    cout << "Optimal Page Faults:  " << optimal(frames, pages) << endl;

    return 0;
}
