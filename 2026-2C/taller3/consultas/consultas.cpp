#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

int consulta(vector<long long>& T, int n) {
  sort(T.begin(), T.end(), [](long long a, long long b){ return a < b;});
  int res = n;
  int cnt = T[0];
  for (int i = 1; i < n; i++){
    if(T[i] < cnt) {
      int j;
      for(j = i+1; j < n && T[j] < cnt; j++);
      if (j < n){
        swap(T[i], T[j]);
      } else {
        res--;
      }
    }
    cnt += T[i];
  }
  /*
  for (long long num : T) {
    cout << num << " ";
  }
  */
  return res;
}

int main() {
  int n;
  cin >> n; 
  vector<long long> T;
  T.resize(n);
  for(long long& e : T){
    cin >> e;
  }
  int res = consulta(T, n);
  cout << res << endl;
  return 0;
}
