#include <iostream>
#include <algorithm>

using namespace std;

struct Process {
    int pid;       
    int arrival;   
    int burst;    
    int waiting;  
    int turnaround;
};

bool compareArrival(Process a, Process b) {
    return a.arrival < b.arrival;
}

bool compareBurst(Process a, Process b) {
    return a.burst < b.burst;
}

void calculateTimes(Process p[], int n) {
    int completionTime[n];
    int totalWaiting = 0, totalTurnaround = 0;

    completionTime[0] = p[0].arrival + p[0].burst;
    p[0].waiting = 0;
    p[0].turnaround = p[0].burst;

    for (int i = 1; i < n; i++) {
        if (completionTime[i - 1] < p[i].arrival)
            completionTime[i] = p[i].arrival + p[i].burst;
        else
            completionTime[i] = completionTime[i - 1] + p[i].burst;

        p[i].turnaround = completionTime[i] - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;

        totalWaiting += p[i].waiting;
        totalTurnaround += p[i].turnaround;
    }

    cout << "\nPID\tArrival\tBurst\tWaiting\tTurnaround\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].arrival << "\t" << p[i].burst << "\t"
             << p[i].waiting << "\t" << p[i].turnaround << "\n";
    }

    cout << "\nAverage Waiting Time: " << (float)totalWaiting / n;
    cout << "\nAverage Turnaround Time: " << (float)totalTurnaround / n << "\n";
}

void FCFS(Process p[], int n) {
    sort(p, p + n, compareArrival);
    cout << "\n--- First Come First Serve (FCFS) Scheduling ---\n";
    calculateTimes(p, n);
}

void SJF(Process p[], int n) {
    sort(p, p + n, compareArrival); 

    int completed = 0, currentTime = 0;
    bool processCompleted[n] = {false};

    cout << "\n--- Shortest Job First (SJF) Scheduling ---\n";

    while (completed < n) {
        int idx = -1, minBurst = 1e9;

        for (int i = 0; i < n; i++) {
            if (!processCompleted[i] && p[i].arrival <= currentTime) {
                if (p[i].burst < minBurst) {
                    minBurst = p[i].burst;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            currentTime++;
        } else {
            currentTime += p[idx].burst;
            p[idx].turnaround = currentTime - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            processCompleted[idx] = true;
            completed++;
        }
    }

    calculateTimes(p, n);
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process p[n];

    cout << "Enter Arrival Time and Burst Time for each process:\n";
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Process " << i + 1 << " Arrival Time: ";
        cin >> p[i].arrival;
        cout << "Process " << i + 1 << " Burst Time: ";
        cin >> p[i].burst;
    }

    FCFS(p, n);

    for (int i = 0; i < n; i++) {
        p[i].waiting = 0;
        p[i].turnaround = 0;
    }

    SJF(p, n);

    return 0;
}