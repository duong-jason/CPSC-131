#pragma once

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
private:
    vector<vector<int>> mat;
    vector<bool> visited;
    vector<int> result;

public:
    Graph() = default;
    Graph(const int& size) {
        for (int i = 0; i < size; ++i) {
            mat.push_back({});
            visited.push_back(false);
        }
    }
    ~Graph() {
        for (vector<int> edge : mat) edge.clear();
        visited.clear();
    }

    void addEdge(const int& v1, const int& v2) {
        mat[v1].push_back(v2);
        mat[v2].push_back(v1);
    }

    vector<int> BFS() {
        queue<int> q;
        q.push(0);
        visited[0] = true;

        while (!q.empty()) {
            for (int edge : mat[q.front()]) {
                if (!visited[edge]) {
                    visited[edge] = true;
                    q.push(edge);
                }
            }

            result.push_back(q.front());
            q.pop();
        }

        return result;
    }

    vector<int> DFS_helper() {
        result.push_back(0);
        DFS(0);
        return result;
    }

    void DFS(int node) {
        visited[node] = true;
        for (int edge : mat[node]) {
            if (!visited[edge]) {
                result.push_back(edge);
                DFS(edge);
            }
        }
    }

    void print_graph() {
        cout << "-------------------------------------------\n";
        for (auto y : mat) {
            for (auto x : y) {
                cout << x << " ";
            }
            cout << endl;
        }	
        cout << "-------------------------------------------\n";
    }
};
