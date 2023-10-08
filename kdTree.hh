#ifndef _KDTREE_HH_
#define _KDTREE_HH_

#include <vector>
#include <iostream>
#include <memory>
#include <cstdlib>
using namespace std;

struct BoundingBox {
    vector<double> minPoint;
    vector<double> maxPoint;
};


struct Node {
    vector<double> x;

    shared_ptr<Node> left;
    shared_ptr<Node> right;
    int discr;
    //BoundingBox* bbox;

    Node(const vector<double>& i, shared_ptr<Node> l, shared_ptr<Node> r):
            x(i), left(l), right(r) { }

};

typedef enum {
    STANDART,
    RELAX,
    SQUARISH,
} TreeType;

class kdTree {
    private:
        int k; //dimensiones
        int n; //num de nodos
        shared_ptr<Node> root;
        int visitedNodes;

        void clear();

        static void free(shared_ptr<Node> p);

        //BoundingBox rootBoundingBox();
        shared_ptr<Node> i_insert(shared_ptr<Node>& currNode, const vector<double>& infoNewNode, unsigned depth, TreeType tipo, BoundingBox& Bb);

        static string i_inorder(shared_ptr<Node> root);


        shared_ptr<Node> i_insertWithBoundingBox(shared_ptr<Node>& root, const vector<double>& info, unsigned depth);
        shared_ptr<Node> nearestNeighbor(shared_ptr<Node> root, const vector<double>& queryPoint, unsigned depth, shared_ptr<Node> bestNode, double& bestDistance);
        int getVisitedNodes() const;

        void i_debug(shared_ptr<Node> root);
    public:

    //Constructura

    //Crea un k-d Tree con dimension k
    kdTree(int k);
    //~kdTree() {clear();}

    //Consultoras

    //Devuelve el valor de la coordenada i
    //Pre:  0 <= i < k
    //Post: root[i]
    double valori(int i) const;

    //Devuelve si el k-d Tree está vacio
    bool empty() const;

    shared_ptr<Node> getRoot() const;

    int getNodosVisitados();

    //Modificadoras
    void insert(const vector<double>& info, TreeType tipo);

    shared_ptr<Node> findNearestNeighbor(const vector<double>& queryPoint);

    //Escritura
    string inorder();
    void debug();
};

#endif