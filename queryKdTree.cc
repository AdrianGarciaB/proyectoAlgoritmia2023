using namespace std;
#include <iostream>
#include <vector>
#include <cstring>
#include "kdTree.hh"

TreeType convertStringToTreeType(const char* s) {
    if (strcmp(s, "STANDART") == 0) return STANDART;
    if (strcmp(s, "RELAX") == 0) return RELAX;
    if (strcmp(s, "SQUARISH") == 0) return SQUARISH;
    return STANDART;
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <TreeType>\n";
        return 1;
    }

    TreeType type = convertStringToTreeType(argv[1]);

    int nArboles;
    cin >> nArboles;
    cout << nArboles << endl;

    for (int i = 0; i< nArboles; ++i) {
        int k, n, q;
        cin >> k >> n >> q;
        cout << q << endl;
        kdTree tree(k);
        for (int j = 0; j< n; ++j) {
            vector<double> info(k);

            for (int w = 0; w < k; ++w) // Leemos las k coordenadas.
                cin >> info[w];

            tree.insert(info, type);
        }
        for (int j = 0; j < q; ++j) {
            vector<double> info(k);

            for (int w = 0; w < k; ++w) // Leemos las k coordenadas.
                cin >> info[w];

            shared_ptr<Node> nearestNeighbor = tree.findNearestNeighbor(info);

            for (int w = 0; w < k; ++w)
                cout << nearestNeighbor->x[w] << " ";
            cout << endl;

        }

    }
    return 0;
}
