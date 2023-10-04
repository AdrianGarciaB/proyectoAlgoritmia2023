#ifndef _KDTREE_HH_
#define _KDTREE_HH_

#include <vector>
#include <iostream>
using namespace std;

struct BoundingBox {
    vector<double> minPoint;
    vector<double> maxPoint;
};

struct Node {
    //int dim;
    vector<double> x/*(dim)*/;

    Node* left;
    Node* right;
    BoundingBox* bbox;

    Node(const vector<double>& i, Node* l, Node* r, BoundingBox* b):
            x(i), left(l), right(r), bbox(b) { }

};

class kdTree {
    private:
        int k; //dimensiones
        int n; //num de nodos

        Node* root;

        static void free(Node* p);

        BoundingBox rootBoundingBox();
        Node* i_insert(Node*& currNode, const vector<double>& infoNewNode, unsigned depth);

        static void i_inorder(Node* root);


        Node* i_insertWithBoundingBox(Node*& root, const vector<double>& info, unsigned depth);
        Node* nearestNeighbor(Node* root, const vector<double>& queryPoint, unsigned depth, Node* bestNode, double& bestDistance);


        void i_debug(Node* root);
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

    Node* findNearestNeighbor(const vector<double>& queryPoint);

    //Escritura
    void inorder();
    void debug();
};

#endif