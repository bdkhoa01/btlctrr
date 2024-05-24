#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

const int MY_INT_MAX = 1000000;

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    Edge* edge;
};

void BF(const int G[20][20], int n, char startVertex, int BFValue[20], int BFPrev[20]) {
    // Build graph
    Graph graph;
    graph.V = n;
    graph.E = 0;
    graph.edge = new Edge[n * n];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (G[i][j] != 0 && G[i][j] != INT_MAX) {
                graph.edge[graph.E].src = i;
                graph.edge[graph.E].dest = j;
                graph.edge[graph.E].weight = G[i][j];
                graph.E++;
            }
        }
    }

    // Initialize arrays
    int src = startVertex - 'A';
    for (int i = 0; i < n; ++i) {
        BFValue[i] = INT_MAX;
        BFPrev[i] = -1;
    }
    BFValue[src] = 0;

    // Relax edges
    for (int i = 1; i < n; ++i) {
        int relaxCount = 0;
        for (int j = 0; j < graph.E; ++j) {
            int u = graph.edge[j].src;
            int v = graph.edge[j].dest;
            int weight = graph.edge[j].weight;
            if (BFValue[u] != INT_MAX && BFValue[u] + weight < BFValue[v]) {
                BFValue[v] = BFValue[u] + weight;
                BFPrev[v] = u;
                relaxCount++;
            }
        }

        // Print step
        cout << "Step " << i << ":" << endl;
        cout << "\033[1;34mBFValue:\033[0m ";
        for (int k = 0; k < n; ++k) {
            if (BFValue[k] != INT_MAX)
                cout << BFValue[k] << " ";
            else
                cout << "INF ";
        }
        cout << endl;
        cout << "\033[1;32mBFPrev:\033[0m  ";
        for (int k = 0; k < n; ++k) {
            cout << BFPrev[k] << " ";
        }
        cout << endl;
        cout << "\033[1;35mRelaxations:\033[0m " << relaxCount << endl << endl;
    }

    delete[] graph.edge;
}

string BF_Path(const int G[20][20], int n, char startVertex, char goalVertex) {
    int BFValue[20];
    int BFPrev[20];

    int src = startVertex - 'A';
    int dest = goalVertex - 'A';

    BF(G, n, startVertex, BFValue, BFPrev);

    if (BFValue[dest] == INT_MAX) {
        return "No Path";
    }

    vector<int> path;
    int at = dest;
    while (at != -1) {
        path.push_back(at);
        at = BFPrev[at];
    }
    reverse(path.begin(), path.end());

    stringstream ss;
    for (int i = 0; i < path.size(); ++i) {
        if (i > 0) ss << " ";
        ss << (char)(path[i] + 'A');
    }
    cout << "\033[1;36mPath from " << startVertex << " to " << goalVertex << ": " << ss.str() << "\033[0m" << endl;
    cout << "\033[1;33mTotal weight: " << BFValue[dest] << "\033[0m" << endl;

    return ss.str();
}
