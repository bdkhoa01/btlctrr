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
#include <chrono>

using namespace std;
using namespace chrono;

const int INF = 1e9;
const int MAX_N = 20;
int graph[MAX_N][MAX_N];
int n;

int calculateCost(const vector<int>& path) {
    int cost = 0;
    for (int i = 0; i < path.size() - 1; ++i) {
        cost += graph[path[i]][path[i + 1]];
    }
    cost += graph[path.back()][path.front()];
    return cost;
}

pair<vector<int>, int> bruteForceTSP() {
    vector<int> cities(n);
    iota(cities.begin(), cities.end(), 0);

    vector<int> bestPath;
    int bestCost = INF;

    do {
        int currentCost = 0;
        for (int i = 0; i < n - 1; ++i) {
            currentCost += graph[cities[i]][cities[i + 1]];
        }
        currentCost += graph[cities[n - 1]][cities[0]];

        if (currentCost < bestCost) {
            bestCost = currentCost;
            bestPath = cities;
        }
    } while (next_permutation(cities.begin(), cities.end()));

    bestPath.push_back(bestPath[0]);  // Close the path to form a cycle
    return make_pair(bestPath, bestCost);
}

string drawPath(const vector<int>& path) {
    stringstream ss;
    char start = 'A';
    for (int i = 0; i < path.size(); ++i) {
        ss << start + path[i];
        if (i < path.size() - 1) {
            ss << " -> ";
        }
    }
    return ss.str();
}

string Traveling(int graphInput[][20], int nInput, char start) {
    n = nInput;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = graphInput[i][j];
        }
    }

    auto start_time = steady_clock::now();

    auto resultBF = bruteForceTSP();
    vector<int> bestPathBF = resultBF.first;
    int bestCostBF = resultBF.second;

    auto end_time = steady_clock::now();
    auto duration = duration_cast<nanoseconds>(end_time - start_time);

    cout << "Time taken: " << duration.count() << " nanoseconds" << endl;
    cout << "Brute Force Cost: " << bestCostBF << " Path: " << drawPath(bestPathBF) << endl;

    return drawPath(bestPathBF) + " (Cost: " + to_string(bestCostBF) + ")";
}


