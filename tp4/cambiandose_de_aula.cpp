#include <iostream>
#include <string>
#include <vector>
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

int aula_bt(const vector<vector<int>>& M, ) {
    if 
}

int main() {
    int tests;
    cin >> tests;
    //cout << "Tests: " << tests << endl;

    for (int k = 0; k < tests; k++) {
        int n, m;
        cin >> n >> m;
        //cout << "n: " << n << " m: " << m << endl;

        vector<vector<int>> M(n, vector<int>(m));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++){
                cin >> M[i][j];
                //cout << "pos: " << M[i][j] << endl;
            }
        }

        //cout << "Matriz " << k+1 << ":" << endl;
        //printMatrix(M);
        int res = aula_bt();
        //cout << res << endl;
    }

    return 0; 
}