#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <numeric>

using namespace std;

// Estructura para representar las aristas
struct Edge {
  int desde, hasta, peso, idx;
  Edge(int d, int h, int p, int i) : desde(d), hasta(h), peso(p), idx(i) {}
};

// Disjoint Set de la catedra (implementado con Union-Find)
class UnionFind {
  vector<int> rank, parent;
  public:
  UnionFind(int n) {
    rank.resize(n + 1, 0);
    parent.resize(n + 1);
    for(int i = 0; i < n + 1; i++) {
      parent[i] = i;
    }
  }

  int findSet(int node) {
    if (node == parent[node]) return node;
    return parent[node] = findSet(parent[node]);
  }

  void unionByRank(int u, int v) {
    int uRepresentative = findSet(u);
    int vRepresentative = findSet(v);

    if (uRepresentative == vRepresentative) return;

    if (rank[uRepresentative] < rank[vRepresentative]) {
      parent[uRepresentative] = vRepresentative;
    } else if(rank[uRepresentative] > rank[vRepresentative]) {
      parent[vRepresentative] = uRepresentative;
    } else {
      parent[vRepresentative] = uRepresentative;
      rank[uRepresentative]++;
    }
  }
};

vector<vector<int>> lista_adyacencia_contraida;
struct GrafoContraido {
  int num_cc;
  map<pair<int,int>, int> cantidad_aristas_entre_cc;  
  map<int, int> mapeo_cc_a_id;  // Esta es la magia que hace que no se me vaya a la goma la complejidad temporal en un par de tests 

  GrafoContraido() : num_cc(0) {}
};

// Construye el grafo contraido G' para un grupo de aristas del mismo peso
GrafoContraido construirGrafoContraido(const vector<Edge>& E, int inicio, int fin, UnionFind& ds) {
  lista_adyacencia_contraida.clear();
  GrafoContraido g_prima;
  int nodos = 0;

  // Procesamos todas las aristas que tienen el mismo peso
  for (int j = inicio; j < fin; j++) {
    // Encontramos los representantes de las componentes conexas
    int componenteU = ds.findSet(E[j].desde);
    int componenteV = ds.findSet(E[j].hasta);

    // Asignamos IDs nuevos a las componentes si no los tienen
    if (g_prima.mapeo_cc_a_id.count(componenteU) == 0) {
      g_prima.mapeo_cc_a_id[componenteU] = nodos++;
      lista_adyacencia_contraida.push_back(vector<int>());
    }
    if (g_prima.mapeo_cc_a_id.count(componenteV) == 0) {
      g_prima.mapeo_cc_a_id[componenteV] = nodos++;
      lista_adyacencia_contraida.push_back(vector<int>());
    }

    // Convertimos los IDs de componentes a los nuevos IDs consecutivos
    int nuevoU = g_prima.mapeo_cc_a_id[componenteU];
    int nuevoV = g_prima.mapeo_cc_a_id[componenteV];

    // Solo nos interesan las aristas entre distintas componentes
    if (nuevoU != nuevoV) {
      // Contamos cuántas aristas hay entre estas componentes
      pair<int,int> arista = {min(nuevoU,nuevoV), max(nuevoU,nuevoV)};
      if (g_prima.cantidad_aristas_entre_cc.count(arista) == 0) {
        g_prima.cantidad_aristas_entre_cc[arista] = 0;
      }
      g_prima.cantidad_aristas_entre_cc[arista]++;

      // Solo agregamos la primera arista entre dos componentes al grafo
      if (g_prima.cantidad_aristas_entre_cc[arista] == 1) {
        lista_adyacencia_contraida[nuevoU].push_back(nuevoV);
        lista_adyacencia_contraida[nuevoV].push_back(nuevoU);
      }
    }
  }

  g_prima.num_cc = nodos;
  return g_prima;
}

// DFS para detectar puentes con Cubren de la catedra
int NO_LO_VI = 0, EMPECE_A_VER = 1, TERMINE_DE_VER = 2;
vector<int> estado;
vector<int> memo;
vector<int> padre;
vector<vector<int>> tree_edges;
vector<int> back_edges_con_extremo_inferior_en;
vector<int> back_edges_con_extremo_superior_en;

void dfs(int v, int) {
  estado[v] = EMPECE_A_VER;
  for (int u : lista_adyacencia_contraida[v]) {
    if (estado[u] == NO_LO_VI) {
      tree_edges[v].push_back(u);
      padre[u] = v;
      dfs(u, v);
    }
    else if (u != padre[v]) {
      if (estado[u] == EMPECE_A_VER) {
        back_edges_con_extremo_superior_en[v]++;
      }
      else {  // estado[u] == TERMINE_DE_VER
        back_edges_con_extremo_inferior_en[v]++;
      }
    }
  }
  estado[v] = TERMINE_DE_VER;
}

int cubren(int v, int p) {
  if (memo[v] != -1) return memo[v];
  int res = 0;
  for (int hijo : tree_edges[v]) {
    if (hijo != p) {
      res += cubren(hijo, v);
    }
  }
  res += back_edges_con_extremo_superior_en[v];
  res -= back_edges_con_extremo_inferior_en[v];
  memo[v] = res;
  return res;
}

void detectarPuentes(int n) {
  for (int k = 0; k < n; k++) {
    if (estado[k] == NO_LO_VI) {
      padre[k] = k;
      dfs(k, k);
      cubren(k, k);
    }
  }
}

string clasificarArista(const Edge& arista, UnionFind& ds, const GrafoContraido& g_prima) {
  int componenteU = ds.findSet(arista.desde);
  int componenteV = ds.findSet(arista.hasta);
  int nuevoU = g_prima.mapeo_cc_a_id.at(componenteU);
  int nuevoV = g_prima.mapeo_cc_a_id.at(componenteV);

  // Si la arista conecta la misma componente => no puede estar en ningún AGM
  if (nuevoU == nuevoV) {
    return "none";  
  }

  // Si hay múltiples aristas entre las componentes => algunas estarán en AGMs y otras no 
  pair<int,int> aristaActual = {min(nuevoU,nuevoV), max(nuevoU,nuevoV)};
  if (g_prima.cantidad_aristas_entre_cc.at(aristaActual) > 1) {
    return "at least one";  
  }

  // Si es puente => esta en todos los AGM
  if ((padre[nuevoU] == nuevoV && cubren(nuevoU, padre[nuevoU]) == 0) ||
      (padre[nuevoV] == nuevoU && cubren(nuevoV, padre[nuevoV]) == 0)) {
    return "any";
  }

  // Si conecta componentes diferentes y no es un puente =>  entonces es una de varias aristas posibles para conectar las componentes
  if (nuevoU != nuevoV && g_prima.cantidad_aristas_entre_cc.at(aristaActual) == 1) {
    return "at least one";
  }

}

int main() {
  int n, m;
  cin >> n >> m;

  vector<Edge> E;
  for (int i = 0; i < m; i++) {
    int a, b, w;
    cin >> a >> b >> w;
    // Con push_back se me iba la complejidad. Al parecer es menos eficiente porque crea un objeto temporal y despues lo copia al vector
    E.emplace_back(a-1, b-1, w, i);
  }
  // Se ordenan las aristas segun peso de menor a mayor
  sort(E.begin(), E.end(), [](const Edge& a, const Edge& b) { return a.peso < b.peso; });

  vector<string> resultado(m);
  UnionFind ds(n);  

  int i = 0;
  while (i < m) {
    int j = i;
    while (j < m && E[i].peso == E[j].peso) j++;

    // Construyo grafo G' para el subconjunto actual
    GrafoContraido g_prima = construirGrafoContraido(E, i, j, ds);

    // Estructuras para detección de puentes
    // No la tenia: assign resizea e inicializa vectores en una sola instruccion
    estado.assign(g_prima.num_cc, NO_LO_VI);
    memo.assign(g_prima.num_cc, -1);
    padre.assign(g_prima.num_cc, -1);
    tree_edges.assign(g_prima.num_cc, vector<int>());
    back_edges_con_extremo_inferior_en.assign(g_prima.num_cc, 0);
    back_edges_con_extremo_superior_en.assign(g_prima.num_cc, 0);

    detectarPuentes(g_prima.num_cc);

    // Tagear cada arista del grupo en "none", "at least one" o "any"
    for (int k = i; k < j; k++) {
      resultado[E[k].idx] = clasificarArista(E[k], ds, g_prima);
    }

    // Actualizamos las componentes conexas
    for (int k = i; k < j; k++) {
      if (ds.findSet(E[k].desde) != ds.findSet(E[k].hasta)) {
        ds.unionByRank(E[k].desde, E[k].hasta);
      }
    }

    i = j; 
  }

  for (const auto& res : resultado) {
    cout << res << endl;
  }

  return 0;
}
