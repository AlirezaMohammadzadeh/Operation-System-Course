#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Process {
    string name;
    int executionTime;
    int arrivalTime;
};

bool compareArrivalTime(Process p1, Process p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

int main() {
    int n;
    int quantum = 3;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for(int i = 0; i < n; i++) 
        cin >> processes[i].name >> processes[i].executionTime >> processes[i].arrivalTime;

    sort(processes.begin(), processes.end(), compareArrivalTime);

    queue<Process> processQueue;
    vector<int> waitingTime(n), turnaroundTime(n);
    int currentTime = processes[0].arrivalTime, remainingTime = 0, currentIndex = 0;
    while(!processQueue.empty() || currentIndex < n) {
        while(currentIndex < n && processes[currentIndex].arrivalTime <= currentTime) {
            processQueue.push(processes[currentIndex]);
            currentIndex++;
        }

        if(processQueue.empty()) {
            currentTime = processes[currentIndex].arrivalTime;
            continue;
        }

        Process currentProcess = processQueue.front();
        processQueue.pop();

        if(remainingTime > 0) {
            processQueue.push(currentProcess);
            if(remainingTime >= quantum) {
                remainingTime -= quantum;
            } else {
                currentTime += remainingTime;
                remainingTime = 0;
            }
            continue;
        }

        waitingTime[currentProcess.name[1] - '0'] += currentTime - currentProcess.arrivalTime;
        if(currentProcess.executionTime >= quantum) {
            currentProcess.executionTime -= quantum;
            remainingTime = quantum;
            processQueue.push(currentProcess);
        } else {
            remainingTime = currentProcess.executionTime;
            currentTime += currentProcess.executionTime;
            turnaroundTime[currentProcess.name[1] - '0'] = currentTime - currentProcess.arrivalTime;
        }
    }

    double avgWaitingTime = 0, avgTurnaroundTime = 0;
    for(int i = 0; i < n; i++) {
        avgWaitingTime += waitingTime[i];
        avgTurnaroundTime += turnaroundTime[i];
        }
    avgWaitingTime /= n;
    avgTurnaroundTime /= n;

    cout << "Average Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;

    return 0;
}   
