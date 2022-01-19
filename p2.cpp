#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

vector<vector<int>> buildGraph(int n, int m) {
    vector<vector<int>> graph;
    int parent, child;

    for (int i = 0; i < n; i++) {
        graph.push_back({});
    }

    for (int i = 0; i < m; i++) {
        if (scanf("%d %d", &parent, &child) != 2) {
            cout << 0 << endl;
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

int visitVertex(vector<vector<int>> &graph, int v, unordered_set<int> &common, int V, vector<int> &color, vector<int> &pi) {
    pi[V] = V;
    color[v] = 1;
    for (size_t i = 0; i < graph[v].size(); i++) {
        int u = graph[v][i] - 1;
        if (color[u] == 0) {
            visitVertex(graph, u, common, V, color, pi);
        } else {
            if (pi[u] != V && (common.find(u) == common.end())) {
                for (size_t j = 0; j < graph[u].size(); j++) {
                    int x = graph[u][j] - 1;
                    if (common.find(x) != common.end()) {
                        common.erase(x);
                    }
                }
                common.insert(u);
            }
        }
    }
    color[v] = 2;
    return 0;
}


unordered_set<int> FindCommonAncestrals(vector<vector<int>> &graph, int vertexes[2]) {
    unordered_set<int> common;
    vector<int> color(graph.size(), 0); // 0 - white, 1 - gray, 2 - black
    vector<int> pi(graph.size());

    for(int i = 0; i < 2; i++) {
        if(color[vertexes[i]] == 0) {
            visitVertex(graph, vertexes[i], common, vertexes[i], color, pi);
        }
        else {
            if(pi[vertexes[i]] != vertexes[i]) {
                // nao pertence
                if(common.find(vertexes[i]) == common.end()) {
                    for(size_t j = 0; j < graph[vertexes[i]].size(); j++) {
                        if(common.find(graph[vertexes[i]][j]) != common.end()) {
                            common.erase(graph[vertexes[i]][j]);
                        }
                    }
                    common.insert(vertexes[i]);
                }
            }
        }

    }
    return common;
}

vector<int> commonAncestrals(vector<vector<int>> &graph, int v1, int v2) {
    unordered_set<int> common;
    int vertexes[2] = {v1-1, v2-1};

    common = FindCommonAncestrals(graph, vertexes);
    vector<int> commonAncestral(common.begin(), common.end());
    sort(commonAncestral.begin(), commonAncestral.end());
    return commonAncestral;
}

int main() {
    int v1, v2, n, m;
    vector<vector<int>> graph;
    vector<int> commonAncestral;
    
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
        commonAncestral = commonAncestrals(graph, v1, v2);
        if (commonAncestral.size() == 0) {
            cout << '-' << endl;
        } else {
            for (size_t i = 0; i < commonAncestral.size(); i++) {
                cout << commonAncestral[i] + 1 << ' ';
            }
            cout << endl;
        }
    }
    
    return 0;
}