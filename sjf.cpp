#include <bits/stdc++.h>
using namespace std;

struct Process {
    int pid, at, bt, ct, tat, wt;
    bool done = false;
};

struct Compare {
    bool operator()(Process* a, Process* b) {
        return a->bt > b->bt || (a->bt == b->bt && a->at > b->at);
    }
};

class SJF {
    vector<Process> p;
    vector<pair<int, int>> seq;

public:
    void init() {
        int n;
        cin >> n;
        p.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i].at >> p[i].bt;
            p[i].pid = i + 1;
        }
    }

    void start() {
        int n = p.size(), done = 0, time = 0;
        while (done < n) {
            priority_queue<Process*, vector<Process*>, Compare> pq;
            for (auto& proc : p)
                if (!proc.done && proc.at <= time)
                    pq.push(&proc);
            if (!pq.empty()) {
                Process* cur = pq.top();
                cur->wt = time - cur->at;
                time += cur->bt;
                cur->ct = time;
                cur->tat = cur->ct - cur->at;
                cur->done = true;
                seq.push_back({cur->pid, time - cur->bt});
                done++;
            } else time++;
        }
    }

    void chart() {
        for (auto _ : seq) cout << "------"; cout << "\n|";
        for (auto& i : seq) cout << " P" << i.first << " |"; cout << "\n";
        for (auto _ : seq) cout << "------"; cout << "\n";
        cout << seq[0].second;
        for (auto& i : seq) {
            auto& proc = p[i.first - 1];
            cout << setw(6) << i.second + proc.bt;
        }
        cout << "\n\nPID\tAT\tBT\tCT\tTAT\tWT\n";
        for (auto& i : p)
            cout << i.pid << "\t" << i.at << "\t" << i.bt << "\t" << i.ct << "\t" << i.tat << "\t" << i.wt << "\n";
        cout << fixed << setprecision(2) << "\nAvg WT: " << avgwt() << "\n";
    }

    double avgwt() {
        double s = 0;
        for (auto& i : p) s += i.wt;
        return s / p.size();
    }
};

int main() {
    SJF sjf;
    sjf.init();
    sjf.start();
    sjf.chart();
    return 0;
}
