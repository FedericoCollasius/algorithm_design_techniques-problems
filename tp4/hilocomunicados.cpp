#include <iostream>
#include <cmath>
#include <string>

using namespace std;

int main () {
  double res = 0.0;
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
  target*=(-1);

  long int espacio_total = pow(2,cant_preg);



  cout << target << endl;

  return 0;
}
