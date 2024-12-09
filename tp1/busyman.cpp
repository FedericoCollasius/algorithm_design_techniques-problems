#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int busyman(vector<pair<int, int>>& act) {
  vector<pair<int, int>> sch; // Schedule 
  sort(act.begin(), act.end(), [](const auto &left, const auto &right){ // Ordenamos de forma ascendente por segunda componente (timepo en el que termina)
    return left.second < right.second;
  }); 
  for(auto a : act){
    if (sch.empty() || sch.back().second <= a.first){ // Estrategia greedy: una nueva actividad puede empezar <-> termino la ultima
      sch.push_back(a);
    }   
  }
    
  return sch.size();
}

int main() {
  int T;
  cin >> T; // Cantidad de casos de test
    
  for (int t = 0; t < T; t++) {
    int N;
    cin >> N; // Cantidad de actividades
    vector<pair<int, int>> act; // Vector de tuplas. Primera componente es el tiempo de comienzo de una actividad y la segunda el tiempo en el que termina Vector of pairs. 
        
    for (int i = 0; i < N; i++) {
      int begin, end;
      cin >> begin >> end;    
      act.push_back({begin, end});
    }   
        
    int result = busyman(act);
    cout << result << endl;
  }
  return 0;
}

