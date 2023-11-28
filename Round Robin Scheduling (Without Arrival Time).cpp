#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Process {
    int id;
    int burstTime;
};

void calculateWaitingTurnaroundTime(vector<Process>& processes, int timeQuantum) {
    int n = processes.size();
    vector<int> waitingTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    vector<int> remainingBurstTime(n);

    for (int i = 0; i < n; i++) {
        remainingBurstTime[i] = processes[i].burstTime;
    }

    queue<Process> roundRobinQueue;
    int currentTime = 0;

    roundRobinQueue.push(processes[0]);
    int currentProcessIndex = 1;

    while (!roundRobinQueue.empty()) {
        Process currentProcess = roundRobinQueue.front();
        roundRobinQueue.pop();

        int executionTime = min(timeQuantum, remainingBurstTime[currentProcess.id - 1]);

        remainingBurstTime[currentProcess.id - 1] -= executionTime;
        currentTime += executionTime;

        while (currentProcessIndex < n) {
            roundRobinQueue.push(processes[currentProcessIndex]);
            currentProcessIndex++;

            if (remainingBurstTime[currentProcess.id - 1] <= 0)
                break;
        }

        if (remainingBurstTime[currentProcess.id - 1] > 0) {
            roundRobinQueue.push(currentProcess);
        } else {
            turnaroundTime[currentProcess.id - 1] = currentTime;
            waitingTime[currentProcess.id - 1] = turnaroundTime[currentProcess.id - 1] - processes[currentProcess.id - 1].burstTime;
        }
    }

    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }

    double averageWaitingTime = static_cast<double>(totalWaitingTime) / n;
    double averageTurnaroundTime = static_cast<double>(totalTurnaroundTime) / n;

    cout << "Process\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i].id << "\t" << waitingTime[i] << "\t" << turnaroundTime[i] << endl;
    }

    cout << "Average Waiting Time: " << averageWaitingTime << endl;
    cout << "Average Turnaround Time: " << averageTurnaroundTime << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter burst time for process P" << processes[i].id << ": ";
        cin >> processes[i].burstTime;
    }

    int timeQuantum;
    cout << "Enter time quantum for Round Robin: ";
    cin >> timeQuantum;

    cout << "Round Robin Scheduling (without arrival time):\n";
    calculateWaitingTurnaroundTime(processes, timeQuantum);

    return 0;
}

