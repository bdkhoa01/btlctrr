#include "bellman.h"
#include "tsm.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <numeric>
#include <cmath>

using namespace std;

const int MY_INT_MAX = 1e9;

int main() {
    // BF algo
    int G[20][20] = {
        {0, 6, 0, 0, 7},
        {0, 0, 5, -4, 8},
        {0, -2, 0, 0, 0},
        {2, 0, 7, 0, 0},
        {0, 0, -3, 9, 0}
    };
    int n = 5;
    char startVertex = 'A';
    int BFValue[20];
    int BFPrev[20];

    // Logic of hasNegativeWeightCycle
    bool hasNegativeCycle = false;
    int distance[20];
    for (int i = 0; i < n; ++i) {
        distance[i] = INT_MAX;
    }
    distance[0] = 0; // Assume the source vertex is 0

    // Relax edges |V|-1 times
    for (int i = 0; i < n - 1; ++i) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (G[u][v] != 0 && distance[u] != INT_MAX && distance[u] + G[u][v] < distance[v]) {
                    distance[v] = distance[u] + G[u][v];
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (G[u][v] != 0 && distance[u] != INT_MAX && distance[u] + G[u][v] < distance[v]) {
                hasNegativeCycle = true;
                break;
            }
        }
    }

    if (hasNegativeCycle) {
        cout << "Invalid input: Graph contains a negative weight cycle" << endl;

        // Logic of printPositiveWeightsMessage
        cout << "Graph edges and their weights:" << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (G[i][j] != 0) {
                    cout << (char)('A' + i) << " -> " 
                         << (char)('A' + j) << " weight: " 
                         << G[i][j] << endl;
                }
            }
        }
        cout << "All weights are positive" << endl;

        return 1;
    }

    // Call func
    BF(G, n, startVertex, BFValue, BFPrev);

    // Result
    cout << "Khoang cach ngan nhat tu dinh " << startVertex << " toi cac dinh khac:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Dinh " << (char)('A' + i) << ": " << BFValue[i] << endl;
    }

    // Tìm đường đi từ A tới E
    char goalVertex = 'E';
    string path = BF_Path(G, n, startVertex, goalVertex);
    cout << "Duong di tu " << startVertex << " toi " << goalVertex << ": " << path << endl;

    // TSP
    int tspGraph[20][20] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    int tspN = 4;
    char tspStartVertex = 'A';

    // Logic of hasNegativeWeightCycle for TSP
    hasNegativeCycle = false;
    for (int i = 0; i < tspN; ++i) {
        distance[i] = INT_MAX;
    }
    distance[0] = 0; // Assume the source vertex is 0

    // Relax edges |V|-1 times
    for (int i = 0; i < tspN - 1; ++i) {
        for (int u = 0; u < tspN; ++u) {
            for (int v = 0; v < tspN; ++v) {
                if (tspGraph[u][v] != 0 && distance[u] != INT_MAX && distance[u] + tspGraph[u][v] < distance[v]) {
                    distance[v] = distance[u] + tspGraph[u][v];
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (int u = 0; u < tspN; ++u) {
        for (int v = 0; v < tspN; ++v) {
            if (tspGraph[u][v] != 0 && distance[u] != INT_MAX && distance[u] + tspGraph[u][v] < distance[v]) {
                hasNegativeCycle = true;
                break;
            }
        }
    }

    if (hasNegativeCycle) {
        cout << "Invalid input: TSP graph contains a negative weight cycle" << endl;

        // Logic of printPositiveWeightsMessage for TSP
        cout << "Graph edges and their weights:" << endl;
        for (int i = 0; i < tspN; ++i) {
            for (int j = 0; j < tspN; ++j) {
                if (tspGraph[i][j] != 0) {
                    cout << (char)('A' + i) << " -> " 
                         << (char)('A' + j) << " weight: " 
                         << tspGraph[i][j] << endl;
                }
            }
        }
        cout << "All weights are positive" << endl;

        return 1;
    } else {
        // Logic of printPositiveWeightsMessage for TSP
        cout << "Graph edges and their weights:" << endl;
        for (int i = 0; i < tspN; ++i) {
            for (int j = 0; j < tspN; ++j) {
                if (tspGraph[i][j] != 0) {
                    cout << (char)('A' + i) << " -> " 
                         << (char)('A' + j) << " weight: " 
                         << tspGraph[i][j] << endl;
                }
            }
        }
        cout << "All weights are positive" << endl;
    }

    // Call func
    string tspPath = Traveling(tspGraph, tspN, tspStartVertex);
    cout << "Lo trinh TSP: " << tspPath << endl;

    return 0;
}
