#include "kdTree.hh"

kdTree::kdTree(int k) {
    this->k = k;
    this->n = 0;
    this->root = nullptr;
}

double kdTree::valori(int i) const{
    if (this->root == nullptr || this->root->x.empty() or i >= this->root->x.size())
        return -1;
    return this->root->x[i];
}

bool kdTree::empty() const{
    return !this->root;
}

Node* kdTree::getRoot() const{
    return this->root;
}

BoundingBox kdTree::rootBoundingBox() {
    BoundingBox rootBBox;
    int k = this->k;
    rootBBox.minPoint = vector<double>(k);
    rootBBox.maxPoint = vector<double>(k);
    for (int i = 0; i < k; ++i) {
        rootBBox.minPoint[k] = 0.0; // Minimum coordinates
        rootBBox.maxPoint[k] = 1.0; // Maximum coordinates
    }
    return rootBBox;
}

Node* kdTree::i_insert(Node*& curr, const vector<double>& info, unsigned depth) {
    if (curr == nullptr) {
        BoundingBox rootBBox = rootBoundingBox();
        root = new Node(info, nullptr, nullptr, rootBBox);
        return curr;
    }
    unsigned count_depth = depth % this->k;
    if (info[count_depth] < curr->x[count_depth]) {
        curr->left = i_insert(curr->left, info, depth +1);
    } else {
        curr-> right = i_insert(curr->right, info, depth +1);
    }
    return curr;
}

void kdTree::insert(const vector<double>& info) {
    ++n;
    i_insert(root, info, 0);
}

void kdTree::i_inorder(Node* root) {
    if (root == nullptr) return;
    i_inorder(root->left);
    for (double i : root->x) cout << i << " ";
    cout << endl;
    i_inorder(root->right);
}

void kdTree::inorder() {
   i_inorder(this->root);
}


Node* kdTree::i_insertWithBoundingBox(Node*& root, const vector<double>& info, unsigned depth) {
        if (root == nullptr) {
            BoundingBox rootBBox = rootBoundingBox();
            root = new Node(info, nullptr, nullptr, rootBBox);
            root->bbox = rootBBox; // Store the bounding box for this node
            return root;
        }

        unsigned axis = depth % k;
        BoundingBox nextBBox = root->bbox;

        if (info[axis] < root->x[axis]) {
            nextBBox.maxPoint[axis] = root->x[axis];
            root->left = i_insertWithBoundingBox(root->left, info, depth + 1);
        } else {
            nextBBox.minPoint[axis] = root->x[axis];
            root->right = i_insertWithBoundingBox(root->right, info, depth + 1);
        }

        return root;
    }

