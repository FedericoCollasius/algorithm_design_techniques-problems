#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<vector<int>> aristas(N);

  int u, v;
  for(int i = 0; i < N-1; i++) {
    cin >> u >> v;
    aristas[u-1].push_back(v-1);
    aristas[v-1].push_back(u-1);
  }

  // cout << "Aristas:" << endl;
  // for (int u = 0; u < N; u++) {
  //   std::cout << u << ": ";
  //   for (int v : aristas[u]) std::cout << v << " ";
  //   std::cout << "\n";
  // }

  queue<int> sec;
  vector<int> tmp;
  for(int i = 0; i < N; i++){
    int x;
    cin >> x;
    sec.push(x - 1);
    tmp.push_back(x - 1);
  }

  // cout << "Secuencia:" << endl;
  // for(auto n : tmp) {
  //   cout << n << ", ";
  // }
  // cout << endl;

  vector<int> visitado(N, 0);
  queue<int> q;
  q.push(0);
  visitado[0] = 1;
  unordered_set<int> s;
  s.insert(0);
  while(!q.empty()) {
    while(!s.empty()){
      int w = sec.front(); sec.pop();
      auto it = s.find(w);
      if (it == s.end()) {
        // cout << "El elemento " << w << " no se encuentra en s" << endl;
        cout << "No";
        return 0;
      }
      s.erase(w);
    }
    for(int i = 0; i < q.size(); i++) {
      u = q.front(); q.pop();
      for(int v : aristas[u]){
        if(visitado[v] == 0){
          q.push(v);
          s.insert(v);
          visitado[v] = 1;
        }
      }
    }
  }

  cout << "Yes";
  return 0;
}
