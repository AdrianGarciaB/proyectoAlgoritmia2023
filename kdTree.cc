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

Node* kdTree::i_insert(Node*& curr, const vector<double>& info, unsigned depth) {
    if (curr == nullptr) {
        curr = new Node(info, nullptr, nullptr, nullptr);
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
