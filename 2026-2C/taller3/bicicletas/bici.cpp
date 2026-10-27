#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// (tiempo, (nodo, indice de min bici vista hasta ahora)) 
using State = pair<long long,pair<int,int>>;

void dijkstra(const vector<vector<pair<int,int>>>& G, int n, int source, vector<int>& S, vector<vector<long long>>& tiempo) {
  long long INF = 1e18;
  tiempo.assign(n, vector<long long>(n, INF));

  priority_queue<State, vector<State>, greater<State>> min_pq;
  tiempo[source][source] = 0;
  min_pq.push({0, {source, source}});

  int i = 0;
  while (!min_pq.empty()) {
    //cout << "Iteracion: " << i << endl;
    State curr = min_pq.top();
    min_pq.pop();
    long long t = curr.first;
    int u = curr.second.first;
    int s = curr.second.second;
    //cout << "Minimo actual: [" << t << "," << "[" << u + 1<< "," << S[s] << "]]" << endl;
    
    long long tiempo_actual = tiempo[u][s];
    //cout << "Tiempo actual: " << tiempo_actual << endl;
      
    if (t > tiempo_actual)
      continue;

    //cout << "Estamos viendo vecinos de: " << u + 1<< endl;
    for (const auto& arista : G[u]) {
      int v = arista.first;
      int w = arista.second;
      //cout << v + 1<< " es vecino con peso " << w << endl;
      int min_bike = (S[s] > S[v]) ? v : s;
      //cout << "La minima bicicleta para el vecino " << v + 1 << " es " << S[min_bike] << endl;
      if (tiempo[v][min_bike] > t + w*S[s]) {
        //cout << "El timpo actual " << tiempo[v][min_bike] << " es mayor que " << t + w*S[s] << endl; 
        //cout << "Actualizamos la distancia de [" << v + 1 << "," << S[min_bike] << "] a " << t + w*S[s] << endl;
        tiempo[v][min_bike] = t + w*S[s];
        min_pq.push({tiempo[v][min_bike], {v, min_bike}});
      }
    }
    i++;
    cout << endl;
  }
}

int main (){
  int T;
  cin >> T;
  while(T > 0){
    int n, m, u, v, w;
    cin >> n >> m;
    vector<vector<pair<int,int>>> G(n);
    for(int i = 0; i < m; i++) {
      cin >> u >> v >> w;
      G[u - 1].push_back({v - 1,w});
      G[v - 1].push_back({u - 1,w});
    }
    vector<int> S(n);
    for(int& e : S){
      cin >> e;
    }
    vector<vector<long long>> t;
    dijkstra(G, n, 0, S, t);
    /*
    for (int i = 0; i < n; i++){
      for(int j = 0; j <n; j++){
        cout << "(" << i + 1 << "," << S[j] << ") -> " << t[i][j] << endl;
      }
    }
    */
    cout << *min_element(t[n-1].begin(), t[n-1].end()) << endl;
    T--;
  }
  return 0;
}
