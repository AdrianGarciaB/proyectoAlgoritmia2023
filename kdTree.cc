#include "kdTree.hh"

kdTree::kdTree(int k) {
    this->k = k;
    this->n = 0;
    this->root = nullptr;
    this->visitedNodes = 0;
}

double kdTree::valori(int i) const{
    if (this->root == nullptr || this->root->x.empty() or i >= this->root->x.size())
        return -1;
    return this->root->x[i];
}

bool kdTree::empty() const{
    return !this->root;
}

shared_ptr<Node> kdTree::getRoot() const{
    return this->root;
}

/*
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
*/

shared_ptr<Node> kdTree::i_insert(shared_ptr<Node>& curr, const vector<double>& info, unsigned depth, char tipo, BoundingBox& Bb) {
    if (curr == nullptr) {
        curr = make_shared<Node>(info, nullptr, nullptr/*, nullptr*/);
        return curr;
    }

    unsigned disc_axis;
    srand(time(NULL));

    //s = standart
    //r = relax
    //q = sqaris
    if (tipo == 's')  disc_axis =  depth % k;
    else if (tipo == 'r') disc_axis = rand() % k;
    else if (tipo == 'q') {
        int dist = 0; int dnt = disc_axis = 0;
        for (int i = 0; i < k; ++i) {
            dist = Bb.maxPoint[i] - Bb.minPoint[i];
            if (dnt > dist) {
                dist = dnt;
                disc_axis = i;
            }
        }
    }

    if (info[disc_axis] < curr->x[disc_axis]) {
        Bb.maxPoint[disc_axis] = root->x[disc_axis];
        curr->left = i_insert(curr->left, info, depth +1, tipo, Bb);
    } else {
        Bb.minPoint[disc_axis] = root->x[disc_axis];
        curr-> right = i_insert(curr->right, info, depth +1, tipo, Bb);
    }
    curr->discr = disc_axis;
    //cout << disc_axis << endl;
    return curr;
}

void kdTree::insert(const vector<double>& info, char tipo) {
    ++n;
    
    BoundingBox Bb;
    Bb.minPoint = vector<double>(k, 0.0);
    Bb.maxPoint = vector<double>(k, 1.0);

    i_insert(root, info, 0, tipo, Bb);
}

void kdTree::i_inorder(shared_ptr<Node> root) {
    if (root == nullptr) return;
    i_inorder(root->left);
    for (double i : root->x) cout << i << " ";
    cout << endl;
    i_inorder(root->right);
}

void kdTree::inorder() {
   i_inorder(this->root);
}

void kdTree::debug() {
    i_debug(this->root);
}

void kdTree::i_debug(shared_ptr<Node> root) {
    if (root != nullptr) {
        for (int i = 0; i < root->x.size(); ++i )cout << root->x[i] << " ";
        cout << endl;
        cout << "right" << endl;
        i_debug(root->right);
        cout << "left" << endl;
        i_debug(root->left);
    }
}

/*
shared_ptr<Node> kdTree::i_insertWithBoundingBox(shared_ptr<Node>& root, const vector<double>& info, unsigned depth) {
    if (root == nullptr) {
        //BoundingBox rootBBox = rootBoundingBox();
        root = make_shared<Node>(info, nullptr, nullptr, &rootBBox);
        //root->bbox = &rootBBox; // Store the bounding box for this node
        return root;
    }

    unsigned axis = depth % k;
    //BoundingBox nextBBox = *root->bbox;

    if (info[axis] < root->x[axis]) {
        //nextBBox.maxPoint[axis] = root->x[axis];
        root->left = i_insertWithBoundingBox(root->left, info, depth + 1);
    } else {
        //nextBBox.minPoint[axis] = root->x[axis];
        root->right = i_insertWithBoundingBox(root->right, info, depth + 1);
    }

    return root;
}
*/

