#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

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
    ifstream inputFile("processes.txt");
    vector<Process> processes;

    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            Process process;
            sscanf(line.c_str(), "%s %d %d", &process.name, &process.executionTime, &process.arrivalTime);
            processes.push_back(process);
        }
        inputFile.close();
    } else {
        cout << "Unable to open file." << endl;
        return 1;
    }

    int n = processes.size();
    sort(processes.begin(), processes.end(), compareArrivalTime);

    vector<int> waitingTime(n), turnaroundTime(n);
    waitingTime[0] = 0;
    turnaroundTime[0] = processes[0].executionTime;
    int currentTime = processes[0].arrivalTime + processes[0].executionTime;
    for(int i = 1; i < n; i++) {
        if(currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }
        waitingTime[i] = currentTime - processes[i].arrivalTime;
        currentTime += processes[i].executionTime;
        turnaroundTime[i] = waitingTime[i] + processes[i].executionTime;
    }

    double avgWaitingTime = 0, avgTurnaroundTime = 0;
    
    for(int i = 0; i < n; i++) {
        avgWaitingTime += waitingTime[i];
        avgTurnaroundTime += turnaroundTime[i];
        // cout << "Process " << i << ": " << waitingTime[i] << " " << turnaroundTime[i] << endl;
    }
    
    avgWaitingTime /= n;
    avgTurnaroundTime /= n;

    cout << "Average Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;

    return 0;
}
