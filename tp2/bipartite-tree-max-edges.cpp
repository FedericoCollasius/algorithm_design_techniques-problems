#include <iostream>
#include <vector>
#include <queue>
using namespace std;
 
void giveBipartition(const vector<vector<int>>& G, vector<int>& coloring) {
  queue<int> q;
 
  coloring[0] = 0;
  q.push(0);
  int v;
 
  while (!q.empty()) {
    v = q.front();
    q.pop();
    for (const auto& w : G[v]) {
      if (coloring[w] == -1) {
        coloring[w] = 1 - coloring[v];
        q.push(w);
      }
    }
  }
}
 
long long maxEdgesForBipartiteGraph(const vector<vector<int>>& G, int n) {
  vector<int> coloring(n, -1);
  giveBipartition(G, coloring);
  long long V1 = 0;
  long long V2 = 0;
  for (int i = 0; i < n; i++){
    if (coloring[i] == 0) {
      V1++;
    } else {
      V2++;
    }
  }
  return (V1 * V2) - (n - 1);
}
 
 
int main() {
  int n;
  cin >> n;
 
  vector<vector<int>> G(n, vector<int>(0));
  int v, w;
  for (int i = 0; i < n-1; i++) {
    cin >> v >> w;
    v--;w--;
    G[v].push_back(w);
    G[w].push_back(v);
  }
  long long res = maxEdgesForBipartiteGraph(G, n);
  cout << res << endl;
  return 0;
}
