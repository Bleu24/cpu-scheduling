#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// Structure to represent a process
typedef struct {
    int arrivalTime;
    int burstTime;
    int remainingBurstTime;
    int turnaroundTime;
    int waitingTime;
} Process;

// Function to read process information from user
void readProcessInfo(Process processes[], int numProcesses) {
    for (int i = 0; i < numProcesses; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].remainingBurstTime = processes[i].burstTime;
    }
}

// Function to implement Round Robin scheduling
void roundRobinScheduling(Process processes[], int numProcesses, int timeQuantum) {
    int currentTime = 0;
    int finishedProcesses = 0;

    while (finishedProcesses < numProcesses) {
        int flag = 0;
        for (int i = 0; i < numProcesses; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingBurstTime > 0) {
                flag = 1;
                int burst = (processes[i].remainingBurstTime > timeQuantum) ? timeQuantum : processes[i].remainingBurstTime;
                currentTime += burst;
                processes[i].remainingBurstTime -= burst;
                if (processes[i].remainingBurstTime == 0) {
                    finishedProcesses++;
                    processes[i].turnaroundTime = currentTime - processes[i].arrivalTime;
                    processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
                }
            }
        }

        if (flag == 0) {
            currentTime++;
        }
    }
}

// Function to calculate average waiting time and turnaround time
void calculateAverages(Process processes[], int numProcesses) {
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    for (int i = 0; i < numProcesses; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    double averageWaitingTime = (double)totalWaitingTime / numProcesses;
    double averageTurnaroundTime = (double)totalTurnaroundTime / numProcesses;

    printf("Average Turn Around time: %.2f\n", averageTurnaroundTime);
    printf("Average Waiting Time: %.2f\n", averageWaitingTime);
}

int main() {
    int numProcesses;
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    Process processes[numProcesses];
    readProcessInfo(processes, numProcesses);

    int timeQuantum;
    printf("Enter the time quantum: ");
    scanf("%d", &timeQuantum);

    roundRobinScheduling(processes, numProcesses, timeQuantum);
    calculateAverages(processes, numProcesses);

    return 0;
}