#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int T, n;
long long a, b, STAY_LOW, MOVE_UP, STAY_HIGH, MOVE_DOWN, PILLAR;
string S;
vector<vector<long long>>M; 
constexpr long long inf = 1e18;

// 0 -> first level , 1 -> second level 
long long gas(int i, int e) { 
  if(M[i][e] != -1){
    //cout << "(" << i << "," << e << ") --> calculado previamente" << endl;
    return M[i][e];
  }

  if(i == n  && e == 1){
    //cout << "(" << i << "," << e << ") --> inf" << endl;
    M[i][e] = inf;
    return inf;
  }

  if(i == n && e == 0){
    //cout << "(" << i << "," << e << ") --> "<< b << endl;
    M[i][e] = b;
    return b;
  }

  long long res;
  if(e == 0) {
    if (S[i] == '1') {res = inf;}
    else {
      long long up = MOVE_UP + gas(i+1, 1);
      long long stay = STAY_LOW + gas(i+1, 0);
      res = min(stay, up);
    }
  }
  else {
    long long stay = STAY_HIGH + gas(i+1, 1);
    if(S[i] == '1') {res = stay;}
    else {
      long long down = MOVE_DOWN + gas(i+1, 0);
      res = min(stay, down);
    }
  }

  M[i][e] = res;
  string s;
  /*
  if (S[i] == '1') {
   // s = "Viene cruce, tengo que estar arriba";
  } else {
    s = "No hay cruce";
  }
  */

  //cout << "(" << i << "," << e << ") " << s << " --> " << res << endl;
  return res;
}

int main() {
  cin >> T;
  while(T > 0){
    cin >> n;
    //cout << "n: " << n << endl;
    cin >> a;
    //cout << "a: " << a << endl;
    cin >> b;
    //cout << "b: " << b << endl;
    //cout << endl;
    STAY_LOW = b + a;
    //cout << "STAY_LOW: " << STAY_LOW << endl;
    MOVE_UP = b + 2*a;
    //cout << "MOVE_UP: " << MOVE_UP << endl;
    STAY_HIGH = 2*b + a;
    //cout << "STAY_HIGH : " << STAY_HIGH<< endl;
    MOVE_DOWN = 2*b + 2*a;
    //cout << "MOVE_DOWN: " << MOVE_DOWN<< endl;
    //cout << endl;
    cin >> S; 
    //cout << "S: " << S << endl;
    //cout << endl;
    M.assign(n + 1, vector<long long>(2, -1));
    long long res = gas(0, 0); 
    cout << res << endl;
    M.clear();
    T--;
  }
  return 0;
}

