#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class ResourceAllocationGraph {
    unordered_map<int, vector<int>> adjList;
    vector<int> visited, recursionStack;

    bool detectCycle(int node) {
        visited[node] = 1;
        recursionStack[node] = 1;

        for (int neighbor : adjList[node]) {
            if (!visited[neighbor] && detectCycle(neighbor)) {
                return true;
            } else if (recursionStack[neighbor]) {
                return true; // Cycle detected
            }
        }

        recursionStack[node] = 0;
        return false;
    }

public:
    void addEdge(int from, int to) {
        adjList[from].push_back(to);
    }

    bool isDeadlock() {
        visited.assign(adjList.size(), 0);
        recursionStack.assign(adjList.size(), 0);

        for (auto &pair : adjList) {
            if (!visited[pair.first] && detectCycle(pair.first)) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    ResourceAllocationGraph rag;

    rag.addEdge(1, 2);  
    rag.addEdge(2, 3);  
    rag.addEdge(3, 1);  

    if (rag.isDeadlock()) {
        cout << "Deadlock detected!\n";
    } else {
        cout << "No deadlock detected.\n";
    }

    return 0;
}
