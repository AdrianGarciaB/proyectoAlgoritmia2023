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

Node* kdTree::i_insert(Node*& root, const vector<double>& info, unsigned depth) {
    if (root == nullptr) {
        root = new Node(info, nullptr, nullptr);
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
