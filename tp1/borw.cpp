#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;


int borw_bt(int i, int prev_n, int prev_b, const vector<int>& S) {
    if (i >= S.size()) {
        return 0;
    }
    if(S[i] > prev_n && S[i] > prev_b) {
        return borw_bt(i+1, S[i], prev_b, S);
    } else if(S[i] < prev_b && S[i] < prev_n) {
        return borw_bt(i+1, prev_n, S[i], S);
    } else if(S[i] < prev_n && S[i] > prev_b) {
        return 1 + borw_bt(i+1, prev_n, prev_b, S);
    } else {
        int black = borw_bt(i+1, S[i], prev_b, S); 
        int white = borw_bt(i+1, prev_n, S[i], S);
        int unpainted = 1 + borw_bt(i+1, prev_n, prev_b, S);    
        return min({black, white, unpainted});
    }
}

const int MAX_N = 200;
const int MIN_VALOR = 1;
const int MAX_VALOR = 1000000;
const int BOTTOM = -1;

vector<vector<vector<int>>> T;
vector<int> S;
map<int,int> numero_a_indice;
int N;

int borw_dp(int i, int prev_n, int prev_b) {
    if (i == N) return 0;
    
    if (T[i][prev_n][prev_b] == BOTTOM) {
        // La idea es que si no se puede pintar de negro o blanco si o si lo dejamos sin pintar. 
        // Esto se reduce a tomar el minimo entre 3 cosas donde 2 son valores maximos.
        // Luego siempre vamos a elegir no pintar.
        int negro = MAX_VALOR;
        int blanco = MAX_VALOR;
        // Siempre consideramos la opcion de dejar sin pintar
        int sin_pintar = 1 + borw_dp(i+1, prev_n, prev_b);
        
        // Podemos pintar de negro?
        if (S[i] > prev_n) negro = borw_dp(i+1, S[i], prev_b);
        // Podemos pintar de blanco?
        if (S[i] < prev_b) blanco = borw_dp(i+1, prev_n, S[i]);
       
        T[i][prev_n][prev_b] = min({negro, blanco, sin_pintar});
    }
    
    return T[i][prev_n][prev_b];
}

int main() {
  while (true) {
    cin >> N;
    if (N == -1) break;
    
    // Inicializo la secuencia.
    S.resize(N);
    for (int i = 0; i < N; i++) {
      cin >> S[i];
    }

    // Armo el mapeo de numeros que lei en el input a indices.
    // La idea es que al fin y al cabo me interesa solamente el orden relativo de los valores,
    // no que valores per se son. Esto me permite ahorrarme un monton de memoria ya que una lista
    // como [9876, 1000000, 52, 95, 1001, 50326, 82, 22568, 95, 52, 1000000, 98767] se va a
    // transformar en [7, 8, 1, 2, 4, 6, 3, 5, 2, 1, 8, 7] lo que es mas compacto para memoizar.
    numero_a_indice.clear();
    numero_a_indice[MIN_VALOR-1] = 0; // Es para arrancar a pintar valores negros. La idea es que no hay valor mas chico que este que nos puedan pasar.
    for (int i = 0; i < N; i++) {
      numero_a_indice[S[i]] = 0; // Ponemos 0 por ahora, despues lo actualizamos
    }
    numero_a_indice[MAX_VALOR + 1] = 0; // Analogo pero para elegir valores blancos.

    // Asignamos indices a los valores unicos
    int indice = 0;
    for (auto& par : numero_a_indice) {
      par.second = indice++;
    }

    // Inicializo estructura de memoizacion. La T es de tensor (vector de matrices).
    int M = numero_a_indice.size();
    T.assign(N, vector<vector<int>>(M, vector<int>(M, BOTTOM)));

    // Uso el mapeo para actualizar los valores de la secuencia.
    for (int& num : S) {
      num = numero_a_indice[num];
    }

    int res = borw_dp(0, numero_a_indice[MIN_VALOR-1], numero_a_indice[MAX_VALOR+1]);
    cout << res << endl;    
  }
}
