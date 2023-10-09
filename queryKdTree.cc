using namespace std;
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath> // For sqrt and pow
#include <omp.h>
#include "kdTree.hh"

TreeType convertStringToTreeType(const char* s) {
    if (strcmp(s, "STANDART") == 0) return STANDART;
    if (strcmp(s, "RELAX") == 0) return RELAX;
    if (strcmp(s, "SQUARISH") == 0) return SQUARISH;
    return STANDART;
}

double euclideanDistancee(const vector<double>& point1, const vector<double>& point2) {
    double distance = 0.0;
    for (size_t i = 0; i < point1.size(); ++i) {
        double diff = point1[i] - point2[i];
        distance += pow(diff, 2);
    }
    //return sqrt(distance);
    return distance;
}

bool areExactlyEqual(const std::vector<double>& v1, const std::vector<double>& v2) {
    if (v1.size() != v2.size()) {
        return false;
    }

    for (size_t i = 0; i < v1.size(); ++i) {
        if (v1[i] != v2[i]) {
            return false;
        }
    }

    return true;
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <TreeType> [checkSolution]\n";
        return 1;
    }
    bool checkSolution = (argc == 3 and strcmp("True", argv[2]) == 0);


    TreeType type = convertStringToTreeType(argv[1]);

    int nArboles;
    cin >> nArboles;
    string result = to_string(nArboles) +"\n";

    #pragma omp parallel for // Parallelizing the outer loop
    for (int i = 0; i < nArboles; ++i) {
        int n, k, q;
        cin >> n >> k >> q;
        result.append(to_string(q) + "\n");

        kdTree tree(k);
        #pragma omp parallel for // Parallelizing the loop for tree insertion
        for (int j = 0; j < n; ++j) {
            vector<double> info(k);

            for (int w = 0; w < k; ++w) // Leemos las k coordenadas.
                cin >> info[w];

            tree.insert(info, type);
        }
        #pragma omp parallel for // Parallelizing the loop for nearest neighbor search
        for (int j = 0; j < q; ++j) {
            vector<double> info(k);

            for (int w = 0; w < k; ++w) // Leemos las k coordenadas.
                cin >> info[w];
            shared_ptr<Node> nearestNeighbor = tree.findNearestNeighbor(info);


                /*
                if (!areExactlyEqual(*nearest, nearestNeighbor->x)) {
                    for (int w = 0; w < k; ++w)
                        cout << nearestNeighbor->x[w] << " ";
                    cout << endl;
                    for (int w = 0; w < k; ++w) // Leemos las k coordenadas.
                        cout << (*nearest)[w] << " ";
                    cout << endl;
                    cout << "SOLUTION WRONG." << endl;
                    exit(1);
                }

            }*/
            for (int w = 0; w < k; ++w)
                result.append(to_string(nearestNeighbor->x[w]) + " ");
            result.append(to_string(tree.getNodosVisitados()) + "\n");

            }



        }
        cout << result << endl;
        return 0;

}
