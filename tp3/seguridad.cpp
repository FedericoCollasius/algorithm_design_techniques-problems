#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void dijkstra(const vector<vector<pair<pair<int,int>,int>>>& G, int n, int source, vector<long long>& distancia) {
  long long INF = 1e18;
  distancia.assign(n, INF);

  // Completamente sacado de Internet.
  // De hecho pense que directamente habia una estructura para Min Priority Queue y no habia que hacer esta macumba.
  priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> min_pq;
  distancia[source] = 0;
  min_pq.push({0, source});

  while (!min_pq.empty()) {
    pair<long long, int> curr = min_pq.top();
    min_pq.pop();
    // El nodo y la distancia de ese nodo hasta source hasta el momento.
    int u = curr.second;
    long long d = curr.first;
    
    // Ya encontramos un camino mejor.
    if (d > distancia[u])
      continue;

    for (const auto& arista : G[u]) {
      int v = arista.first.first;
      int longitud = arista.first.second;
      // Hay un mejor camino usando u, relajamos.
      if (distancia[v] > d + longitud) {
        distancia[v] = d + longitud;
        min_pq.push({distancia[v], v});
      }
    }
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<pair<pair<int,int>,int>>> G(n);
  int a, b, l;
  vector<int> longitudes(m);
  // Gracias por darnos los nodos empezando en 0, me ahorra restarlos lol.
  for(int i = 0; i < m; i++) {
    cin >> a >> b >> l;
    G[a].push_back({{b,l}, i});
    G[b].push_back({{a,l}, i});
    longitudes[i] = l;
  }

  int s = 0;
  int t = n-1;

  // Calculamos distancias minimas con s y t como source.
  vector<long long> dist_min_s, dist_min_t;
  dijkstra(G, n, s, dist_min_s);
  dijkstra(G, n, t, dist_min_t);

  // Una arista u-v forma parte de un camino mínimo <=> dist_min_s[u] + longitud + dist_min_t[v] == dist_minima.
  long long dist_minima = dist_min_s[t];
  long long res = 0;
  vector<bool> arista_contada(m, false);
  for(int u = 0; u < n; u++) {
    for(const auto& arista : G[u]) {
      int v = arista.first.first;
      int longitud = arista.first.second;
      int id = arista.second;
      if(!arista_contada[id] && dist_min_s[u] + longitud + dist_min_t[v] == dist_minima) {
        res += longitud * 2;
        arista_contada[id] = true;
      }
    }
  }
  
  cout << res << endl;
  
  return 0;
}
