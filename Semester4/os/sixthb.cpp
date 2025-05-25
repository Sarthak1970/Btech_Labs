#include <iostream>
#include <vector>

using namespace std;

class BankersAlgorithm {
    int n, m;
    vector<vector<int>> Max, Alloc, Need;
    vector<int> Available;

    bool isSafe(vector<int> &safeSequence) {
        vector<int> Work = Available;
        vector<bool> Finish(n, false);
        
        for (int count = 0; count < n; count++) {
            bool found = false;

            for (int i = 0; i < n; i++) {
                if (!Finish[i]) {
                    bool canAllocate = true;
                    for (int j = 0; j < m; j++) {
                        if (Need[i][j] > Work[j]) {
                            canAllocate = false;
                            break;
                        }
                    }

                    if (canAllocate) {
                        for (int j = 0; j < m; j++)
                            Work[j] += Alloc[i][j];
                        
                        safeSequence.push_back(i);
                        Finish[i] = true;
                        found = true;
                        break;
                    }
                }
            }

            if (!found)
                return false; 
        }

        return true;
    }

public:
    void input() {
        cout << "Enter number of processes: ";
        cin >> n;
        cout << "Enter number of resource types: ";
        cin >> m;

        Max.resize(n, vector<int>(m));
        Alloc.resize(n, vector<int>(m));
        Need.resize(n, vector<int>(m));
        Available.resize(m);

        cout << "Enter Maximum demand matrix:\n";
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin >> Max[i][j];

        cout << "Enter Allocation matrix:\n";
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin >> Alloc[i][j];

        cout << "Enter Available resources:\n";
        for (int j = 0; j < m; j++)
            cin >> Available[j];

        // Calculate Need matrix
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                Need[i][j] = Max[i][j] - Alloc[i][j];
    }

    void checkSafety() {
        vector<int> safeSequence;
        if (isSafe(safeSequence)) {
            cout << "System is in a SAFE state. Safe sequence: ";
            for (int i : safeSequence)
                cout << "P" << i << " ";
            cout << endl;
        } else {
            cout << "System is in an UNSAFE state! No safe sequence exists.\n";
        }
    }
};

int main() {
    BankersAlgorithm ba;
    ba.input();
    ba.checkSafety();
    return 0;
}
