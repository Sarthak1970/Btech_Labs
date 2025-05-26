#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Process {
    int id;          
    int burstTime;     
    int priority;      
    int waitingTime;   
    int turnaroundTime; 
};

void priorityScheduling(vector<Process>& processes, int n) {
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.priority < b.priority;
    });

    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    processes[0].waitingTime = 0;
    processes[0].turnaroundTime = processes[0].burstTime;
    totalWaitingTime += processes[0].waitingTime;
    totalTurnaroundTime += processes[0].turnaroundTime;

    for (int i = 1; i < n; i++) {
        processes[i].waitingTime = processes[i - 1].turnaroundTime;
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;

        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    cout << "\nPriority Scheduling:\n";
    cout << "Process ID | Burst Time | Waiting Time | Turnaround Time\n";
    for (const auto& p : processes) {
        cout << p.id << "          | " << p.burstTime << "        | " 
             << p.waitingTime << "          | " << p.turnaroundTime << endl;
    }

    cout << "Average Waiting Time: " << (float)totalWaitingTime / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTurnaroundTime / n << endl;
}

void roundRobinScheduling(vector<Process>& processes, int n, int timeQuantum) {
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    int remainingBurstTimes[n];

    for (int i = 0; i < n; i++) {
        remainingBurstTimes[i] = processes[i].burstTime;
    }

    int currentTime = 0;
    queue<int> q;
    q.push(0);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (remainingBurstTimes[current] > timeQuantum) {
            currentTime += timeQuantum;
            remainingBurstTimes[current] -= timeQuantum;
            q.push(current);
        } else {
            currentTime += remainingBurstTimes[current];
            processes[current].waitingTime = currentTime - processes[current].burstTime;
            processes[current].turnaroundTime = currentTime;

            totalWaitingTime += processes[current].waitingTime;
            totalTurnaroundTime += processes[current].turnaroundTime;
        }
    }

    cout << "\nRound Robin Scheduling (Time Quantum = " << timeQuantum << "):\n";
    cout << "Process ID | Burst Time | Waiting Time | Turnaround Time\n";
    for (const auto& p : processes) {
        cout << p.id << "          | " << p.burstTime << "        | " 
             << p.waitingTime << "          | " << p.turnaroundTime << endl;
    }

    cout << "Average Waiting Time: " << (float)totalWaitingTime / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTurnaroundTime / n << endl;
}

int main() {
    int n, timeQuantum;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    cout << "Enter burst times for each process:\n";
    for (int i = 0; i < n; i++) {
        processes[i].id = i;
        cin >> processes[i].burstTime;
    }

    for (int i = 0; i < n; i++) {
        cout << "Enter priority for Process " << i << " (lower value means higher priority): ";
        cin >> processes[i].priority;
    }
    cout << "Enter time quantum for Round Robin: ";
    cin >> timeQuantum;

    priorityScheduling(processes, n);

    roundRobinScheduling(processes, n, timeQuantum);

    return 0;
}
