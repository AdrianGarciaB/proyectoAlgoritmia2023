#include <iostream>
#include <cstdlib>
#include <vector>

#include "kdTree.hh"
using namespace std;

typedef vector<double> Coord;

int main() {
    int T;      //num de arboles a generar
    int k;      //dimension de cada arbol
    int n;      //num de nodos de cada arbol

    cout << "Numero de arboles:" << endl;
    cin >> T;

    srand(time(NULL));

    for(int i = 1; i <= T; ++i) {   

        //QUE K NO SEA > QUE 6 PORFA
        cout << "Dimension:" << endl;
        cin >> k;
        cout << "Numero de nodos:" << endl;
        cin >> n;

        vector<Coord> Coords(n, Coord(k));

        cout << "Arbol #" << i << ": " << k << " dimensiones y " << n << " nodos" << endl;

        for(int j = 0; j < n; ++j) {
            for(int l = 0; l < k; ++l) {
                double val = double(rand()/double(RAND_MAX));
                Coords[j][l] = val;
                cout << val << " ";
            }
            cout << endl;
        }
        cout << endl << endl << "----------------------------------" << endl << endl;

        kdTree Tree(k);
        for (int j = 0; j < n; ++j) {
            Tree.insert(Coords[j], 's');
        }
        Tree.debug();
    }
}