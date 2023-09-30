#include "kdTree.hh"


kdTree::kdTree(int k) {
    this->k = k;
    this->n = 0;
    this->root = nullptr;
}

double kdTree::valori(int i) const{
    cout << this->root->x.empty()<< endl;
    if (this->root->x.empty() or i >= this->root->x.size())
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
    for (int i = 0; i < k; ++i) {
        rootBBox.minPoint.push_back(0.0); // Minimum coordinates
        rootBBox.maxPoint.push_back(1.0); // Maximum coordinates
    }
    return rootBBox;
}

Node* kdTree::i_insert(Node*& root, const vector<double>& info, unsigned depth) {
    if (root == nullptr) {
        BoundingBox rootBBox = rootBoundingBox(info);
        root = new Node(info, nullptr, nullptr, rootBBox);
        return root;
    }
    unsigned count_depth = depth % this->k;
    if (info[count_depth] < root->x[count_depth]) {
        root->left = i_insert(root->left, info, depth +1);
    } else {
        root -> right = i_insert(root->right, info, depth +1);
    }
    return root;
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
            root->left = i_insertWithBoundingBox(root->left, info, depth + 1, nextBBox);
        } else {
            nextBBox.minPoint[axis] = root->x[axis];
            root->right = i_insertWithBoundingBox(root->right, info, depth + 1, nextBBox);
        }

        return root;
    }

