#include <iostream>
#include <vector>
#include <unordered_set>

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


unordered_set<int> FindCommonAncestrals(vector<vector<int>> &graph, int vertexes[]) {
    unordered_set<int> common;
    vector<int> color(graph.size(), 0); // 0 - white, 1 - gray, 2 - black
    vector<int> pi(graph.size(), NULL);

    for(int i = 0; i < sizeof(vertexes); i++) {
        if(color[vertexes[i]] == 0) {
            visitVertex(graph, vertexes[i], common, vertexes[i]);
        }
        else {
            if(pi[vertexes[i]] != vertexes[i]) {
                if(common.find(vertexes[i]) != common.end()) {
                    for(int j = 0; j < graph[vertexes[i]].size(); j++) {
                        if(common.find(graph[vertexes[i]][j]) != common.end()) {
                            common.erase(graph[vertexes[i]][j]);
                        }
                    }
                    common.insert(vertexes[i]);
                }
            }
        }

    }
}

int commonAncestrals(vector<vector<int>> graph, int v1, int v2) {
    vector<int> commonAncestral;
    int vertexes[] = {v1-1, v2-1};

    FindCommonAncestrals(graph, vertexes);

    // convert unordered_set to ordered vector
    // return said vector
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
        commonAncestrals(graph, v1, v2);
    }
    
    return 0;
}