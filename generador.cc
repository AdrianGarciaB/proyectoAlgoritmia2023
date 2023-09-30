#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    int T;      //num de arboles a generar
    int k;      //dimension de cada arbol
    int n;      //num de nodos de cada arbol

    cin >> T;

    srand(time(NULL));

    for(int i = 1; i <= T; ++i) {   
        cin >> k >> n;
        cout << "Arbol #" << i << ": " << k << " dimensiones y " << n << " nodos" << endl;

        for(int j = 0; j < n; ++j) {
            for(int l = 0; l < k; ++l) {
                cout << double(rand()/double(RAND_MAX)) << " ";
            }
            cout << endl;
        }
        cout << endl << endl << "----------------------------------" << endl << endl; 
    }
}