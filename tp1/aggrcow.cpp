#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


bool esDistanciaViable(int D, int C, const vector<int>& stalls) {
  // La primera vaca va siempre en la primera posicion
  C--;
  int ultimaVacaColocada = stalls[0];
  
  // Iteramos hasta que nos quedamos sin vacas que colocar (True)
  // o sin posiciones (False)
  for (int i = 1; i < stalls.size() && C > 0; i++) {
    // Colocamos a la vaca a una distancia D
    if(stalls[i] - ultimaVacaColocada >= D) {
      C--;
      ultimaVacaColocada = stalls[i];
    }
  }

  return (C == 0);
}

// Busqueda binaria modificada.
// Lo intersante de este ejercicio es darse cuenta que la guarda clasica de la busqueda binaria, arr[mid] == x,
// es solamente una condicion. El fuerte de la busqueda binaria viene de:
//  1. Poder modificar esa condicion para que sea otra cosa
//  2. Eliminar una mitad del arreglo en cada iteracion
// En este caso, usamos busqueda binaria para encontrar la distancia minima entre vacas.
// No es que cualquiera problema lo podes convertir a uno de busqueda binaria si es que podes ordenar los inputs
// (o sí, no lo se) pero acá si una distiancia es viable, todas las menores tambien lo son (y hay posibilidad
// de que mayores tambien lo sean), y si no lo es todas las mayores tampoco. 
// Lo más confuso es quizas el hecho que estamos tratando a posiciones como distancias. Fijate que es mid: es la
// diferencia entre las posiciones del ultimo y primer elemento de stalls, justamente una distancia. 
int aggrcow(int N, int C, const vector<int>& stalls) {
  int min_dist, low, mid, high;
  
  min_dist = 0;
  low = stalls[0];
  high = stalls [N-1];
  
  while (low <= high) {
    mid = low + (high - low) / 2;
    if (esDistanciaViable(mid, C, stalls)) {
      low = mid + 1;
      min_dist = mid;
    } else {
      high = mid - 1;
    } 
  }

  return min_dist;
}

int main() {
  int T;
  std::cin >> T;

  for (int t = 0; t < T; t++) {
    int N, C;
    std::cin >> N >> C;

    std::vector<int> stalls(N);
    for (int i = 0; i < N; i++) {
      std::cin >> stalls[i];
    }
    
    // Pre-Condicion para poder usar Busqueda Binaria  
    sort(stalls.begin(), stalls.end());
    
    cout << aggrcow(N, C, stalls) << endl;
  }
  return 0;
}
