#include <bits/stdc++.h>
using namespace std;

class Process {
public:
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int pid;
    bool done;
    int rt;
    int start_time;

    Process(int at, int bt) {
        this->at = at;
        this->bt = bt;
        this->ct = 0;
        this->tat = 0;
        this->wt = 0;
        this->done = false;
    }
};

class SJF {
    vector<Process*> processes;
    vector<pair<int, int>> sequence;
    int total;

public:
    SJF() { total = 0; };

    void init() {
        int n;
        cout << "Enter number of processes:\n";
        cin >> n;

        processes.resize(n);

        for (int i = 0; i < n; i++) {
            int at, bt;
            cout << "Enter arrival time and burst time for PID " << i + 1 << ":\n";
            cin >> at >> bt;
            Process* p = new Process(at, bt);
            p->pid = i + 1;
            processes[i] = p;
        }
    }
    void start() {
        int n = processes.size();
        int completed = 0;
        int currentTime = 0;
        int lastPid = -1;
        int min_rt;
        int idx;
    
        while (completed < n) {
            idx = -1;
            min_rt = INT_MAX;
    
            for (int i = 0; i < n; i++) {
                if (processes[i]->at <= currentTime && processes[i]->rt > 0) {
                    if (processes[i]->rt < min_rt) {
                        min_rt = processes[i]->rt;
                        idx = i;
                    } else if (processes[i]->rt == min_rt) {
                        if (processes[i]->at < processes[idx]->at) {
                            idx = i;
                        }
                    }
                }
            }
    
            if (idx != -1) {
                Process* p = processes[idx];
    
                // First time this process starts
                if (p->start_time == -1) {
                    p->start_time = currentTime;
                }
    
                // If process just changed, log the switch
                if (lastPid != p->pid) {
                    sequence.push_back({p->pid, currentTime});
                    lastPid = p->pid;
                }
    
                p->rt--;
                currentTime++;
    
                if (p->rt == 0) {
                    p->ct = currentTime;
                    p->tat = p->ct - p->at;
                    p->wt = p->tat - p->bt;
                    completed++;
                }
            } else {
                // CPU is idle
                currentTime++;
            }
        }
    }    

    void ganttChart() {
        cout << "\nGantt Chart\n------------\n";

        for (size_t i = 0; i < sequence.size(); i++) {
            cout << "------";
        }
        cout << "\n|";
        for (auto& proc : sequence) {
            cout << " P" << proc.first << " |";
        }
        cout << "\n";
        for (size_t i = 0; i < sequence.size(); i++) {
            cout << "------";
        }
        cout << "\n";

        cout << sequence[0].second;
        for (auto& p : sequence) {
            Process* proc = processes[p.first - 1];
            int end = p.second + proc->bt;
            cout << setw(6) << end;
        }

        cout << "\n\nProcess Details:\n";
        cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
        for (auto* proc : processes) {
            cout << proc->pid << "\t"
                 << proc->at << "\t"
                 << proc->bt << "\t"
                 << proc->ct << "\t"
                 << proc->tat << "\t"
                 << proc->wt << "\n";
        }

        cout << "\nAverage Waiting Time: " << fixed << setprecision(2) << get_awt() << endl;
    }

    double get_awt() {
        int wt = 0;
        for (auto* p : processes) {
            wt += p->wt;
        }
        return (double)wt / processes.size();
    }
};

int main() {
    SJF scheduler;
    scheduler.init();
    scheduler.start();
    scheduler.ganttChart();
    return 0;
}
