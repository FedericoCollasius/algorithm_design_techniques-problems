#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

void printMatrix(const vector<vector<int>>& M) {
    for (const auto& row : M) {
        for (const auto& elem : row) {
            cout << setw(5) << elem << " ";
        }
        cout << endl;
    }
}

int BOTTOM = 1000000;
int n;
int m;

vector<vector<int>> MAX;
int DPMax(int x, int y, vector<vector<int>>& aulas) {
    cout << "(" << x << "," << y << "): Entre a la funcion" << endl;
    int curr_aula = aulas[x][y];

    if (MAX[x][y] == BOTTOM) {
        int res = 0;

        if (x == n-1 && y == m-1) {
            cout << "(" << x << "," << y << "): Llegamos al limite de la matriz" << endl;
            res = curr_aula;
        
        } else if (y == m-1) {
            cout << "(" << x << "," << y << "): Llegue al limite derecho, me muevo hacia abajo" << endl;
            res = curr_aula + DPMax(x + 1, y, aulas);
        
        } else if (x == n-1) {
            cout << "(" << x << "," << y << "): Llegue al limite inferior, me muevo hacia la derecha" << endl;
            res = curr_aula + DPMax(x, y + 1, aulas);
        
        } else {
            int abajo = DPMax(x + 1, y, aulas);
            int derecha = DPMax(x, y + 1, aulas);
            res = curr_aula + max(abajo, derecha);
        }

        MAX[x][y] = res;
    }
    cout << "(" << x << "," << y << "): Devuelvo " << MAX[x][y] << endl;
    return MAX[x][y];
}

vector<vector<int>> MIN;
int DPMin(int x, int y, vector<vector<int>>& aulas) {
    cout << "(" << x << "," << y << "): Entre a la funcion" << endl;
    int curr_aula = aulas[x][y];

    if (MIN[x][y] == BOTTOM) {
        int res = 0;

        if (x == n-1 && y == m-1) {
            cout << "(" << x << "," << y << "): Llegamos al limite de la matriz" << endl;
            res = curr_aula;
        
        } else if (y == m-1) {
            cout << "(" << x << "," << y << "): Llegue al limite derecho, me muevo hacia abajo" << endl;
            res = curr_aula + DPMin(x + 1, y, aulas);
        
        } else if (x == n-1) {
            cout << "(" << x << "," << y << "): Llegue al limite inferior, me muevo hacia la derecha" << endl;
            res = curr_aula + DPMin(x, y + 1, aulas);
        
        } else {
            int abajo = DPMin(x + 1, y, aulas);
            int derecha = DPMin(x, y + 1, aulas);
            res = curr_aula + min(abajo, derecha);
        }

        MIN[x][y] = res;
    }
    cout << "(" << x << "," << y << "): Devuelvo " << MIN[x][y] << endl;
    return MIN[x][y];
}

int main() {
    int tests;
    cin >> tests;
    cout << "Tests: " << tests << endl;

    for (int k = 0; k < tests; k++) {
        cin >> n >> m;
        cout << "n:" << n << " m:" << m << endl;

        
        vector<vector<int>> aulas(n, vector<int>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++){
                cin >> aulas[i][j];
            }
        }
        cout << "La distribucion de aulas del ejercicio actual es: " << endl;
        printMatrix(aulas);

        if ((n + m - 1) % 2) {
            cout << "NO" << endl;
            continue;
        }

        MAX.assign(n, vector<int>(m, BOTTOM));
        int res_max = DPMax(0, 0, aulas);
        cout << "MAX:" << endl;
        printMatrix(MAX);
        
        MIN.assign(n, vector<int>(m, BOTTOM));
        int res_min = DPMin(0, 0, aulas);
        cout << "MIN:" << endl;
        printMatrix(MIN);

        if (res_min <= 0 && res_max >= 0) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0; 
}
