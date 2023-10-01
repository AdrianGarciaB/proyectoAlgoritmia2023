//
// Created by houda on 30/09/2023.
//

#include "kdTree.hh"
#include <cmath> // For sqrt and pow
#include <limits> // For numeric_limits
#include <vector>

using namespace std;

// Define a constant for maximum double value (positive infinity)
const double MAX_DOUBLE = numeric_limits<double>::max();

// Helper function to calculate the Euclidean distance between two points
double euclideanDistance(const vector<double>& point1, const vector<double>& point2) {
    double distance = 0.0;
    for (size_t i = 0; i < point1.size(); ++i) {
        double diff = point1[i] - point2[i];
        distance += pow(diff, 2);
    }
    return sqrt(distance);
}

// Recursive function to perform nearest neighbor search
Node* kdTree::nearestNeighbor(Node* root, const vector<double>& queryPoint, unsigned depth, Node* bestNode, double& bestDistance) {
    if (root == nullptr) return bestNode;

    unsigned axis = depth % k;
    Node* nextBranch = nullptr;
    Node* otherBranch = nullptr;

    if (queryPoint[axis] < root->x[axis]) {
        nextBranch = root->left;
        otherBranch = root->right;
    } else {
        nextBranch = root->right;
        otherBranch = root->left;
    }

    // Recursively search the side of the splitting plane that the query point is on
    bestNode = nearestNeighbor(nextBranch, queryPoint, depth + 1, bestNode, bestDistance);

    // Calculate the absolute distance between the splitting coordinate of the search point and the current node
    double axisDistance = fabs(queryPoint[axis] - root->x[axis]);

    // Check if the current node is closer than the best node found so far
    double currentDistance = euclideanDistance(root->x, queryPoint);
    if (currentDistance < bestDistance) {
        bestNode = root;
        bestDistance = currentDistance;
    }

    // Check if there might be a closer point on the other side of the splitting plane
    if (axisDistance < bestDistance) {
        bestNode = nearestNeighbor(otherBranch, queryPoint, depth + 1, bestNode, bestDistance);
    }

    return bestNode;
}

// Public function to find the nearest neighbor to a query point
Node* kdTree::findNearestNeighbor(const vector<double>& queryPoint) {
    if (root == nullptr) return nullptr;

    Node* bestNode = nullptr;
    double bestDistance = MAX_DOUBLE; // Initialize with a large value

    return nearestNeighbor(root, queryPoint, 0, bestNode, bestDistance);
}
