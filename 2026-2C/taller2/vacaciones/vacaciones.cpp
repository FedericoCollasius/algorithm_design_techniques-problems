#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <vector>
using namespace std;

unordered_set<int> G;
unordered_set<int> C;

// 0 -> descanso, 1 -> gym, 2 -> competencia
int vacas(int i, int prv, int n, vector<vector<int>>& M) {
  if (i == n) {
    return 0;
  }

  if (M[i][prv] != -1) {
    return M[i][prv];
  }

  int desc = 1 + vacas(i+1, 0, n, M); 
  int gym = 100000;
  int comp = 100000;
  if (prv != 1 && G.find(i) != G.end())
    gym = vacas(i+1, 1, n, M);
  if (prv != 2 && C.find(i) != C.end())
    comp = vacas(i+1, 2, n, M);
  int res = min({desc, gym, comp});
  M[i][prv] = res;
  return M[i][prv];
}

int main() {
  int n;
  cin >> n;
  for(int i=0; i < n; i++){
    int a;
    cin >> a;
    if (a == 1) C.insert(i);
    if (a == 2) G.insert(i);
    if (a == 3){
      C.insert(i);
      G.insert(i);
    }
  }
  vector<vector<int>> M(n, vector<int>(3, -1));
  int res = vacas(0, 0, n, M);
  cout << res << endl;
  return 0;
}
