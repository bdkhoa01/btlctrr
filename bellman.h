#ifndef BELLMAN_H
#define BELLMAN_H

#include <string>
using namespace std;
// Khai báo hàm Bellman-Ford
void BF(const int G[20][20], int n, char startVertex, int BFValue[20], int BFPrev[20]);

// Khai báo hàm tìm đường đi của Bellman-Ford
string BF_Path(const int G[20][20], int n, char startVertex, char goalVertex);

#endif // BELLMAN_H
