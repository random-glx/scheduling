#include <bits/stdc++.h>
using namespace std;

bool cmpTrr(vector<int> arr1, vector<int> arr2) {
    if(arr1[0]==arr2[0])
        return arr1[2] < arr2[2];
    return arr1[0] < arr2[0];
}
bool cmpQS(vector<int> arr1, vector<int> arr2) {
    return arr1[2] < arr2[2];
}

vector<vector<int>> Timearr;
queue<vector<int>> qu;
int j = 0;
int absTime = 0;
void pulse() {
    while(j < Timearr.size() && absTime >= Timearr[j][0]){
        qu.push(Timearr[j++]);
    }
}

int main() {
    cout << "enter the Number of process : ";
    int n;
    cin >> n;
    Timearr.resize(n, vector<int>(3));
    vector<int> BT(n);
    for (int i = 0; i < n; i++){
        Timearr[i][2] = i + 1;
        cout << "Enter the arrival Time p" << i+1 << " : ";
        cin >> Timearr[i][0];
        cout << "Enter the burst time p" << i+1 << " : ";
        cin >> Timearr[i][1];
        BT[i] = Timearr[i][1];
    }
    int tq;
    cout << "enter Time Quantum : ";
    cin >> tq;

    vector<vector<int>> QuantStore;
    vector<vector<int>> ganttChart;

    sort(Timearr.begin(), Timearr.end(), cmpTrr);
    qu.push(Timearr[0]);
    j++;

    while (!qu.empty() || j < Timearr.size()){
        vector<int> curr = qu.front();
        qu.pop();
        int startTime = (curr[0] > absTime) ? curr[0] : absTime;
        if (curr[0] > absTime) {
            absTime = curr[0];
        }
        int execTime = (curr[1] > tq) ? tq : curr[1];
        int finishTime = startTime + execTime;
        absTime = finishTime;

        if (curr[1] > tq) {
            curr[1] -= tq;
            pulse();
            qu.push(curr);
        } else {
            curr[1] = 0;
            pulse();
        }
        vector<int> record = curr;
        record.push_back(finishTime);
        QuantStore.push_back(record);
        ganttChart.push_back({ record[2], startTime, finishTime });
    }

    cout << "\nGantt Table (Slice Execution):\n";
    cout << "ID  AT  Remaining_BT  FT\n";
    for (int i = 0; i < QuantStore.size(); i++){
        cout << "p" << QuantStore[i][2] << "  " << QuantStore[i][0] << "  " 
             << QuantStore[i][1] << "  " << QuantStore[i][3] << endl;
    }

    cout << "\nGantt Chart:\n";
    for (auto &slice : ganttChart) {
        cout << "| p" << slice[0] << " ";
    }
    cout << "|\n";
    cout << ganttChart.front()[1];
    for (auto &slice : ganttChart) {
        cout << "     " << slice[2];
    }
    cout << "\n";

    vector<vector<int>> store;
    for (int i = 0; i < QuantStore.size(); i++){
        if(!QuantStore[i][1]) {
            store.push_back(QuantStore[i]);
        }
    }
    sort(store.begin(), store.end(), cmpQS);
    cout << "\nID  AT  BT  CT\n";
    for (int i = 0; i < store.size(); i++){
        store[i][1] = BT[i];
        cout << "p" << store[i][2] << "  " << store[i][0] << "  " 
             << store[i][1] << "  " << store[i][3] << endl;
    }

    float avgTAT = 0, avgWT = 0;
    for (int i = 0; i < n; i++){
        store[i].push_back(store[i][3] - store[i][0]);
        avgTAT += store[i].back();
        store[i].push_back(store[i].back() - store[i][1]);
        avgWT += store[i].back();
    }
    cout << "\nID  AT  BT  CT  TAT  WT\n";
    for (int i = 0; i < store.size(); i++){
        store[i][1] = BT[i];
        cout << "p" << store[i][2] << "  " 
             << store[i][0] << "  " 
             << store[i][1] << "  " 
             << store[i][3] << "  " 
             << store[i][4] << "  " 
             << store[i][5] << endl;
    }
    cout << "avgTAT: " << avgTAT/n << endl;
    cout << "avgWT : " << avgWT/n << endl;
    return 0;
}