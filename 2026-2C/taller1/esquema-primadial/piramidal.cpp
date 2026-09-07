/*
Esquema piramidal

La corporación Pira-mi-dal cuenta con n socios-vendedores, numerados desde 1
a n. Cada socio-vendedor recibe los productos de la corporación de a lo sumo un
revendedor, que es otro socio-vendedor con un número distinto; pero algunos no
tienen revendedor, ya que consiguen los productos directamente de la corporación.

Un socio-vendedor A es superior de otro socio-vendedor B si se cumple al menos
una de estas condiciones:
  - A es revendedor inmediato de B.
  - B tiene un revendedor inmediato C tal que A es superior a C.

La corporación descree de toda forma geométrica circular, así que no permite
ningún ciclo en la cadena de reventa: no existe ningún socio-vendedor que sea
superior a su propio revendedor inmediato.

Hoy la corporación organiza la cena anual y necesita dividir a los n
socios-vendedores entre distintas mesas. Cada socio-vendedor va a exactamente
una mesa. Para que los socios-fundadores no noten el esquema, un socio-vendedor
no puede sentarse en la misma mesa que un superior suyo: para toda mesa, no
existen A y B tal que A es superior de B. Las mesas no tienen límite de capacidad.

Pregunta: ¿cuántas mesas son necesarias como mínimo?

Input
  - Primera línea: n (1 <= n <= 2000), la cantidad de socios-vendedores.
  - Siguientes n líneas: el entero p_i (1 <= p_i <= n, o p_i = -1). p_i es el
    revendedor inmediato del i-ésimo socio-vendedor; si es -1, no tiene revendedor.
  - Se garantiza que ningún socio-vendedor se revende a sí mismo (p_i != i)
    ni hay ciclos de reventa.

Output
  Un solo número natural: la cantidad mínima de mesas necesarias.
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<vector<int>> aristas(N);
  vector<int> visitado(N, -1);
  vector<int> raices;

  for(int i = 0; i < N; i++) {
    int r;
    cin >> r;
    if (r != -1){
       aristas[i].push_back(r - 1);
       aristas[r-1].push_back(i);
    } else {
      raices.push_back(i);
    }
  }

  vector<int> niveles(raices.size());
  int nivel;
  queue<int> q;
  for(auto r : raices) {
    nivel = 0;
    visitado[r] = 1;
    q.push(r);
    while(!q.empty()){
      int sz = q.size();
      for (int i = 0; i < sz; i++) {
        int u = q.front(); q.pop();
        for(auto v : aristas[u]){
          if (visitado[v] == -1) {
            visitado[v] = 1;
            q.push(v);
          }
        }
      }
      nivel++;
    }
    niveles.push_back(nivel);
  }

  int res = 0;
  for(auto x : niveles){
    res = x > res ? x : res;
  }
  cout << res << endl;

  return 0;
}
