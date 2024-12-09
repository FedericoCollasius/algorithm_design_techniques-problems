#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const double INF = std::numeric_limits<double>::infinity();

void bfsSPF(vector<vector<int>>& G, int S, vector<int>& dist, vector<int>& vis) {
   queue<int> q;
   dist[S] = 0;
   q.push(S);
   
   int v;
   while (!q.empty()) {
     v = q.front();
     q.pop();
     
     if (vis[v])
       continue;
    
     vis[v] = 1;
     int curr_child_distance = dist[v] + 1;

     for (const auto& w : G[v]) {
       if (!vis[w] && dist[w] > curr_child_distance) {
         dist[w] = curr_child_distance;
         q.push(w);
       }
     }
   }
}

int main() {
  int n;
  cin >> n;

  vector<vector<int>> G(n, vector<int>(0));
  for (int i = 0; i < n-1; i++) {
    G[i].push_back(i+1);
    G[i+1].push_back(i);
  }
  int v; 
  for (int i = 0; i < n; i++) {
    cin >> v;
    v--;
    if (i != v && (v > G[i].back())) {
      G[i].push_back(v);  
    }
  }
  vector<int> dist(n, INF);
  vector<int> vis(n, 0);
  bfsSPF(G, 0, dist, vis);
  for (int i = 0; i < n; i++) {
    cout << dist[i] << " ";
  }
  cout << endl;

  return 0;
}
