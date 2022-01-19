#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> buildGraph(int n, int m) {
    vector<vector<int>> graph;
    int parent, child;

    for (int i = 0; i < n; i++) {
        graph.push_back({});
    }

    for (int i = 0; i < m; i++) {
        if (scanf("%d %d", &parent, &child) != 2) {
            break;
        }

        graph[child - 1].push_back(parent);
    }

    return graph;
}

bool lookForLoop(vector<vector<int>> &graph, vector<int> &color, int v) {
    color[v] = 1;
    for (size_t i = 0; i < graph[v].size(); i++) {
        if (color[graph[v][i] - 1] == 0) {
            if(lookForLoop(graph, color, graph[v][i] - 1)) {
                return true;
            }
        } else if (color[graph[v][i] - 1] == 1) {
            return true;
        }
    }

    color[v] = 2;
    return false;
}

bool validityCheck(vector<vector<int>> &graph) {
    // Check if a child has more than two parents
    for (size_t i = 0; i < graph.size(); i++) {
        if (graph[i].size() >= 3) {
            return false;
        }
    }

    // Check if it has loops using DFS
    vector<int> color(graph.size(), 0); // 0 - white, 1 - gray, 2 - black
    
    for (int i = 0; i < (int)graph.size(); i++) {
        if (color[i] == 0) {
            if (lookForLoop(graph, color, i)) {
                return false;
            }
        }
    }
    
    return true;
}

int commonAncestral(vector<vector<int>> graph) {
    return 0;
}

int main() {
    int v1, v2, n, m;
    vector<vector<int>> graph;
    
    if (scanf("%d %d", &v1, &v2) != 2) {
        return -1;
    }
    if (scanf("%d %d", &n, &m) != 2) {
        return -1;
    }

    graph = buildGraph(n, m);

    if (validityCheck(graph) == false) {
        cout << '0' << endl;
    } else {
        commonAncestral(graph);
    }
    
    return 0;
}