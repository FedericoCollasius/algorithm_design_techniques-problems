/*
Recorrido misterioso

Ana y Beto están estudiando para el parcial de TDA y para procrastinar se
plantearon un juego. Dado un árbol no dirigido, el juego consiste en determinar
si un recorrido que arranque en el nodo 1 podría ser generado por BFS.

Input
  - La primera línea contiene un número natural n (1 <= n <= 2*10^5), la
    cantidad de nodos en el árbol.
  - Las siguientes n-1 líneas describen los ejes del árbol. Cada línea contiene
    dos números x e y (1 <= x, y <= n) — los extremos de un eje. Se garantiza
    que el grafo ingresado es un árbol.
  - La última línea contiene n naturales distintos a_1, a_2, ..., a_n
    (1 <= a_i <= n) — la secuencia a verificar.

Output
  Imprimir "Yes" si la secuencia representa un recorrido BFS válido en el árbol,
  o "No" en caso contrario. Las letras pueden ser mayúsculas o minúsculas.
*/
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
  sec.pop();

  // cout << "Secuencia:" << endl;
  // for(auto n : tmp) {
  //   cout << n << ", ";
  // }
  // cout << endl;
  // tmp.clear();

  vector<int> visitado(N, 0);
  queue<int> q;
  q.push(0);
  tmp.push_back(0);
  visitado[0] = 1;
  unordered_set<int> children;
  while(!q.empty()) {
    // cout << "Cola al principio: ";
    // for(auto x : tmp) cout << x << " ";
    // cout << endl;
    int sz = q.size();
    for(int i = 0; i < sz; i++) {
      u = q.front(); q.pop();
      // cout << "Aristas de " << u << ": ";
      for(auto v : aristas[u]){
        if(visitado[v] == 0){
          visitado[v] = 1;
          children.insert(v);
          // cout << v << ", ";
        }
      }
        // cout << endl;
        int amount_children = children.size();
        // cout << "Hijos al principio de " << u << ": ";
        // for (int x : children) std::cout << x << " ";
        // std::cout << "\n";
        while(amount_children > 0) {
          int w = sec.front(); sec.pop();
          // cout << "Vertice w es " << w << endl;
          if (children.find(w) == children.end()) {
            cout << "No" << endl; 
            return 0;
          }
          q.push(w);
          tmp.push_back(w);
          children.erase(w);
          amount_children--;
        }
        // cout << "Cola al final: ";
        // for(auto x : tmp) cout << x << " ";
        // cout << endl;
        // cout << "Hijos de al final" << u << " : ";
        // for (int x : children) std::cout << x << " ";
        // std::cout << "\n";
      }
    }

  cout << "Yes" << endl;
  return 0;
}

/*
Solución alternativa (BFS canónico)

Idea: una secuencia es un BFS válido sii EXISTE algún orden de vecinos que la
genere. La única libertad de BFS es el orden entre hermanos (hijos de un mismo
padre). Entonces ordenamos los vecinos de cada nodo por su posición en la
secuencia dada, corremos el BFS canónico, y comparamos con la secuencia. Si
algún BFS válido produce la secuencia, este también lo hace. O(n log n).

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);          // 1-indexado
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    vector<int> a(n), pos(n + 1);
    for (int i = 0; i < n; i++) { cin >> a[i]; pos[a[i]] = i; }

    // Un recorrido BFS del enunciado arranca en el nodo 1
    if (a[0] != 1) { cout << "No\n"; return 0; }

    // Ordenar los vecinos de cada nodo por su posición en la secuencia
    for (int v = 1; v <= n; v++)
        sort(adj[v].begin(), adj[v].end(),
             [&](int p, int q) { return pos[p] < pos[q]; });

    // BFS canónico: encolar los vecinos en el orden de la secuencia
    vector<int> bfs;
    vector<char> vis(n + 1, 0);
    queue<int> q;
    q.push(1); vis[1] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        bfs.push_back(u);
        for (int w : adj[u])
            if (!vis[w]) { vis[w] = 1; q.push(w); }
    }

    cout << (bfs == a ? "Yes" : "No") << "\n";
    return 0;
}
*/
