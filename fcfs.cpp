#include<bits/stdc++.h>
using namespace std;

class Process {
    public:
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int pid;

    Process(int at,int bt) {
        this->at = at;
        this->bt = bt;
        this->ct = 0;
        this->tat = 0;
        this->wt = 0;
    }
};

class FCFS {
    vector<Process*> processes;
    vector<int> AT;
    vector<pair<int,int>> sequence;
    int total = 0;

    public:
    FCFS() {
        this->total = 0;
    };

    void init() {
        int n ;
        cout<<"Enter number of processes : \n";
        cin>>n;

        processes.resize(n);
        AT.resize(n);

        for(int i = 0; i < n; i++) {
            int at,bt;
            cout<<"Enter arrival time and burst time for pid " << i + 1<<endl;
            cin>>at>>bt;

            AT[i] = at;
            Process* p = new Process(at,bt);
            p->pid = i + 1;
            processes[i] = p;

        }
    }

    void start() {
        
        vector<pair<int,Process*>> sorted;

        int n = processes.size();
        for(int i = 0; i < n; i++) {
            sorted.push_back({processes[i]->at, processes[i]});
        }

        sort(sorted.begin(),sorted.end());

        for (int i = 0; i < sorted.size(); i++) {
            Process* p = sorted[i].second;
        
            if (total < p->at)
                total = p->at;
        
            sequence.push_back({p->pid, total});
            
            p->ct = total + p->bt;
            p->tat = p->ct - p->at;
            p->wt = p->tat - p->bt;
        
            total = p->ct;
        }
    }

    void ganttChart() {
        cout<<"Gantt Chart!"<<endl;
        cout<<"------------"<<endl;

        for(int i = 0; i < processes.size(); i++) {
            cout<<"------";
        }
        cout<<endl<<"|";

        for(auto& proc : sequence) {
            cout<<" P"<<proc.first<<"  |";
        }

        cout<<endl;

        for(auto& p : sequence) {
            cout << "--------";
        }
        cout << "\n";
        
        cout << sequence[0].second;
        for(auto& p : sequence) {
            Process* proc = processes[p.first - 1];
            cout << "    " << p.second + proc->bt;
        }

        cout << "\n\n";
        
        cout << "Process Details:\n";
        cout << "---------------\n";
        cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
        
        for(auto* proc : processes) {
            cout << proc->pid << "\t" 
                 << proc->at << "\t" 
                 << proc->bt << "\t" 
                 << proc->ct << "\t" 
                 << proc->tat << "\t" 
                 << proc->wt << "\n";
        }
        
        cout << "\nAverage Waiting Time: " << get_awt() << endl;
    }
    

    double get_awt() {
        int wt = 0;

        for(int i = 0; i < processes.size(); i++) {
            wt += processes[i]->wt;
        }

        return (double)wt/processes.size();
    }
};

int main() {
    FCFS f;
    f.init();
    f.start();
    f.ganttChart();

    return 0;
}