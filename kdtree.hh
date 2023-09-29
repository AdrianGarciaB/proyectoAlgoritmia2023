#ifndef _KDTREE_HH_
#define _KDTREE_HH_

#include <vector>
#include <iostream>
using namespace std;

struct Node {
    //int dim;
    vector<double> x/*(dim)*/;

    Node* left;
    Node* right;

    Node (const vector<double>& i, Node* l, Node* r):
        x(i), left(l), right(r) { }
};

class kdTree {
    private:
        int k; //dimensiones
        int n; //num de nodos

        Node* root;

        static void free(Node* p);

        Node* i_insert(Node*& root, const vector<double>& info, unsigned depth);

        static void i_inorder(Node* root);

    public:

    //Constructura

    //Crea un k-d Tree con dimension k
    kdTree(int k);

    //Consultoras

    //Devuelve el valor de la coordenada i
    //Pre:  0 <= i < k
    //Post: root[i]
    double valori(int i) const;

    //Devuelve si el k-d Tree está vacio
    bool empty() const;

    Node* getRoot() const;

    //Modificadoras
    void insert(const vector<double>& info);

    //Escritura
    void inorder();
};

#endif