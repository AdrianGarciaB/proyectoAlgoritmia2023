#include <iostream>
#include <random>
#include <vector>
#include <cstdlib>

#include "kdTree.hh"

using namespace std;

int main () {

    
    //Generador random
    random_device myRandomDevice;
    unsigned seed = myRandomDevice(); // para generar la "semilla"
    uniform_real_distribution<double> Uniforme(0.0, 1.0);
    default_random_engine RNG(seed);
    

    srand(time(NULL));

    //Tamaño de los arboles, entre 100 y 10.000.000
    for (int nodos = 100; nodos <= 10000000; nodos *= 10) {

        //Cada grupo de arboles de k dimensiones
        for (int kk = 2; kk <= 6; ++kk){

            //Numero de arboles por cada dimension
            for (int nArboles = 0; nArboles < 100; ++nArboles) {

                kdTree treeS(kk);
                kdTree treeR(kk);
                kdTree treeQ(kk);

                for (int i = 0; i < nodos; ++i) {
                    vector<double> v(kk);
                    for (int j = 0; j < kk; ++j) v[j] = Uniforme(RNG);// double(rand()/double(RAND_MAX));
                    treeS.insert(v, STANDART);
                    treeR.insert(v, RELAX);
                    treeQ.insert(v, SQUARISH);
                }

                vector<double> query(kk);
                for (int i = 0; i < kk; ++i) query[i] = Uniforme(RNG); //double(rand()/double(RAND_MAX));

                shared_ptr<Node> infoS = treeS.findNearestNeighbor(query);
                shared_ptr<Node> infoR = treeR.findNearestNeighbor(query);
                shared_ptr<Node> infoq = treeQ.findNearestNeighbor(query);

                cout << nArboles << " Numero de nodos: " << nodos << ' ' << "Dimensiones: " << ' ' << kk << ' ' << "Numero de nodos visitados STANDART: " << treeS.getNodosVisitados() << ' ' << "Numero de nodos visitados RELAX: " << treeR.getNodosVisitados() << ' ' << "Numero de nodos visitados SQUARISH: " << treeQ.getNodosVisitados() << endl;
            }
        }
    }
}