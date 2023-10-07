using namespace std;
#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <cmath> // For sqrt and pow

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
    return sqrt(distance);
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
    cout << nArboles << endl;

    for (int i = 0; i < nArboles; ++i) {
        int n, k, q;
        cin >> n >> k >> q;
        cout << q << endl;
        kdTree tree(k);
        for (int j = 0; j < n; ++j) {
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

            if (checkSolution) {
                istringstream stream(tree.inorder());
                string line;
                vector<double> *nearest;
                vector<double> currentCandidateInfo;
                double d_nearest = -1; //Inf
                while (getline(stream, line)) {
                    istringstream lineStream(line);

                    for (int i = 0; i < k; ++i) {
                        double value;
                        if (lineStream >> value) {
                            currentCandidateInfo.push_back(value);
                        }
                        double d = euclideanDistancee(nearestNeighbor->x, currentCandidateInfo);
                        if (d == -1 || d < d_nearest) {
                            for (int w = 0; w < k; ++w) // Leemos las k coordenadas.
                                cout << (currentCandidateInfo)[w] << " ";
                            nearest = &currentCandidateInfo;
                            d_nearest = d;
                        }
                    }
                }
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
                    cout << nearestNeighbor->x[w] << " ";
                cout << endl;

            }

            for (int w = 0; w < k; ++w)
                cout << nearestNeighbor->x[w] << " ";

            cout << tree.getNodosVisitados() << endl;

        }

        return 0;
    }
}