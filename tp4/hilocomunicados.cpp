#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <iomanip>


using namespace std;

// El caso en el que no hay ? no me interesa porque ahi directamente puedo contar 
// y se si llego o no. 

// +-+++-
// ???+-+

// ++-,-++,+-+

// target = 1
// cant_preg = 3

// bt(2, 3)
// plus = bt(3, 2)

// minus = bt(2, 2)

int bt(int target, int cant_preg) {
    if (target == 0 && cant_preg == 0) {
      return 1;
    }

    if (cant_preg == 0) {
      return 0;
    }

    if (cant_preg > 0) {
      int plus = bt(target+1, cant_preg-1);
      int minus = bt(target-1, cant_preg-1);
      return plus + minus;
    } 
}


int main () {
  long double res = 0.0;
  int target = 0;
  int cant_preg = 0;
  string s1 = ""; string s2 = "";
  cin >> s1; cin >> s2;

  for (char& c : s1) {
    if (c == '+') {
      target++;
    } else if (c == '-') {
      target--;
    }
  }
  
  for (char& c : s2) {
    if (c == '+') {
      target--;
    } else if (c == '-') {
      target++;
    } else if (c == '?') {
      cant_preg++;
    }
  }
  int sols;
  if (target == 0 && cant_preg == 0) {
    res = 1;
  } else if (target != 0 && cant_preg == 0) {
    res = 0;
  } else {
    sols = bt(target, cant_preg);
    res = sols / (pow(2, cant_preg));
  }

  cout << fixed << setprecision(12) << res << endl;
  return 0;
}

