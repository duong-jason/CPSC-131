#include <iostream>
#include <vector>
#include <string>
#include "Graph.hpp"

using namespace std;

// Global static variables
static int testCount = 0;
static const int testTotal = 5;

vector<int> v1;
vector<int> v2;
vector<int> v3;
vector<int> v4;

template <typename T, typename U>
bool assertVectorEquals(const string& nameOfTest, const vector<T>& expected, const vector<U>& actual);

// Main
int main(int argc, char const *argv[]) {
    {
        Graph G(9);//9 vertices
        G.addEdge(0, 1);
        G.addEdge(0, 3);
        G.addEdge(0, 8);
        G.addEdge(1, 7);
        G.addEdge(2, 3);
        G.addEdge(2, 5);
        G.addEdge(2, 7);
        G.addEdge(3, 4);
        G.addEdge(4, 8);
        G.addEdge(5, 6);

        G.print_graph();

        v1 = { 0, 1, 3, 8, 7, 2, 4, 5, 6 };
        v2 = G.BFS();

        assertVectorEquals("Breadth First Test", v1, v2);

        Graph D(9);//9 vertices
        D.addEdge(0, 1);
        D.addEdge(0, 3);
        D.addEdge(0, 8);
        D.addEdge(1, 7);
        D.addEdge(2, 3);
        D.addEdge(2, 5);
        D.addEdge(2, 7);
        D.addEdge(3, 4);
        D.addEdge(4, 8);
        D.addEdge(5, 6);

        v3 = { 0, 1, 7, 2, 3, 4, 8, 5, 6 };
        v4 = D.DFS_helper();

        assertVectorEquals("Depth First Test", v3, v4);

        v1.clear();
        v2.clear();
        v3.clear();
        v4.clear();
    }

    {
        Graph G(9);//9 vertices
        G.addEdge(0, 1);
        G.addEdge(0, 8);
        G.addEdge(2, 3);
        G.addEdge(2, 4);
        G.addEdge(2, 5);
        G.addEdge(2, 8);
        G.addEdge(4, 7);
        G.addEdge(5, 6);
        G.addEdge(6, 7);
        G.addEdge(6, 8);

        G.print_graph();

        v1 = { 0, 1, 8, 2, 6, 3, 4, 5, 7 };
        v2 = G.BFS();

        assertVectorEquals("Breadth First Test", v1, v2);

        Graph D(9);//5 vertices
        D.addEdge(0, 1);
        D.addEdge(0, 8);
        D.addEdge(2, 3);
        D.addEdge(2, 4);
        D.addEdge(2, 5);
        D.addEdge(2, 8);
        D.addEdge(4, 7);
        D.addEdge(5, 6);
        D.addEdge(6, 7);
        D.addEdge(6, 8);

        v3 = { 0, 1, 8, 2, 3, 4, 7, 6, 5 };
        v4 = D.DFS_helper();

        assertVectorEquals("Depth First Test", v3, v4);

        v1.clear();
        v2.clear();
        v3.clear();
        v4.clear();
    }

    {
        Graph G(5);//5 vertices
        G.addEdge(0, 1);
        G.addEdge(0, 4);
        G.addEdge(1, 2);
        G.addEdge(1, 3);
        G.addEdge(2, 3);
        G.addEdge(3, 4);

        G.print_graph();

        v1 = { 0, 1, 4, 2, 3 };
        v2 = G.BFS();

        assertVectorEquals("Breadth First Test", v1, v2);

        Graph D(5);//5 vertices
        D.addEdge(0, 1);
        D.addEdge(0, 4);
        D.addEdge(1, 2);
        D.addEdge(1, 3);
        D.addEdge(2, 3);
        D.addEdge(3, 4);

        v3 = { 0, 1, 2, 3, 4 };
        v4 = D.DFS_helper();

        assertVectorEquals("Depth First Test", v3, v4);

        v1.clear();
        v2.clear();
        v3.clear();
        v4.clear();
    }

    return 0;
}

// Helper Functions
template <typename T, typename U>
bool assertVectorEquals(const string& nameOfTest, const vector<T>& expected, const vector<U>& actual) {
    if (expected.size() == actual.size()) {
        for (size_t i = 0; i < expected.size(); i++) {
            if (expected[i] != actual[i]) {
                cout << "FAILED " << nameOfTest << ": expected '" << expected[i] << "' but actually '" << actual[i] << "'" << endl;
                return false;
            }
        }

        cout << "PASSED " << nameOfTest << ": expected and actual lists match: {";

        for (int i = 0; i < expected.size(); i++) cout << " " << expected[i];
        cout << " }" << endl;

        testCount++;
        return true;
    }

    cout <<  "FAILED " << nameOfTest << ": expected size '" << expected.size() << "' but actually size is '" << actual.size() << "'" << endl;
    return false;
}