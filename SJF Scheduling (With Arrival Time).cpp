#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
};

bool compareArrivalTime(const Process& a, const Process& b) {
    return a.arrivalTime < b.arrivalTime;
}

bool compareBurstTime(const Process& a, const Process& b) {
    return a.burstTime < b.burstTime;
}

void calculateWaitingTurnaroundTime(vector<Process>& processes) {
    int n = processes.size();
    vector<int> waitingTime(n, 0);
    vector<int> turnaroundTime(n, 0);

    waitingTime[0] = 0;
    turnaroundTime[0] = processes[0].burstTime;

    for (int i = 1; i < n; i++) {
        waitingTime[i] = max(0, turnaroundTime[i - 1] - processes[i].arrivalTime);
        turnaroundTime[i] = waitingTime[i] + processes[i].burstTime;
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
        cout << "Enter arrival time for process P" << processes[i].id << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for process P" << processes[i].id << ": ";
        cin >> processes[i].burstTime;
    }

    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), compareArrivalTime);
    cout << "SJF Scheduling (with arrival time):\n";
    calculateWaitingTurnaroundTime(processes);

    return 0;
}

