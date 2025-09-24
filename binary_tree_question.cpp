#include <bits/stdc++.h>
using namespace std;

// Binary Tree Node
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};


// Inorder Traversal
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Preorder Traversal
void preorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// Postorder Traversal
void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// Level Order Traversal (BFS)
void levelOrder(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* curr = q.front(); q.pop();
        cout << curr->data << " ";
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

// Count total nodes
int countNodes(Node* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Count leaf nodes
int countLeafNodes(Node* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

// Count non-leaf nodes
int countNonLeafNodes(Node* root) {
    if (!root || (!root->left && !root->right)) return 0;
    return 1 + countNonLeafNodes(root->left) + countNonLeafNodes(root->right);
}

// Height of binary tree
int height(Node* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

// Sum of all nodes
int sumNodes(Node* root) {
    if (!root) return 0;
    return root->data + sumNodes(root->left) + sumNodes(root->right);
}

// Maximum node value
int maxNode(Node* root) {
    if (!root) return INT_MIN;
    return max(root->data, max(maxNode(root->left), maxNode(root->right)));
}

// Minimum node value
int minNode(Node* root) {
    if (!root) return INT_MAX;
    return min(root->data, min(minNode(root->left), minNode(root->right)));
}


// Diameter of binary tree
int diameterUtil(Node* root, int &res) {
    if (!root) return 0;
    int l = diameterUtil(root->left, res);
    int r = diameterUtil(root->right, res);
    res = max(res, l + r + 1);
    return 1 + max(l, r);
}
int diameter(Node* root) {
    int res = 0;
    diameterUtil(root, res);
    return res;
}

// Check if two trees are identical
bool isIdentical(Node* a, Node* b) {
    if (!a && !b) return true;
    if (!a || !b) return false;
    return a->data == b->data && isIdentical(a->left, b->left) && isIdentical(a->right, b->right);
}

// Check if tree is symmetric
bool isMirror(Node* a, Node* b) {
    if (!a && !b) return true;
    if (!a || !b) return false;
    return a->data == b->data && isMirror(a->left, b->right) && isMirror(a->right, b->left);
}
bool isSymmetric(Node* root) {
    if (!root) return true;
    return isMirror(root->left, root->right);
}

// Lowest Common Ancestor (LCA)
Node* LCA(Node* root, int n1, int n2) {
    if (!root) return nullptr;
    if (root->data == n1 || root->data == n2) return root;
    Node* left = LCA(root->left, n1, n2);
    Node* right = LCA(root->right, n1, n2);
    if (left && right) return root;
    return left ? left : right;
}

// Print all ancestors of a node
bool printAncestors(Node* root, int target) {
    if (!root) return false;
    if (root->data == target) return true;
    if (printAncestors(root->left, target) || printAncestors(root->right, target)) {
        cout << root->data << " ";
        return true;
    }
    return false;
}

// Level with maximum sum
int maxLevelSum(Node* root) {
    if (!root) return 0;
    queue<Node*> q;
    q.push(root);
    int maxSum = INT_MIN;
    while (!q.empty()) {
        int size = q.size(), levelSum = 0;
        for (int i = 0; i < size; i++) {
            Node* curr = q.front(); q.pop();
            levelSum += curr->data;
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        maxSum = max(maxSum, levelSum);
    }
    return maxSum;
}

// Maximum width of binary tree
int maxWidth(Node* root) {
    if (!root) return 0;
    queue<Node*> q;
    q.push(root);
    int maxWidth = 0;
    while (!q.empty()) {
        int count = q.size();
        maxWidth = max(maxWidth, count);
        for (int i = 0; i < count; i++) {
            Node* curr = q.front(); q.pop();
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }
    return maxWidth;
}


// Serialize and Deserialize
void serialize(Node* root, ostream &out) {
    if (!root) {
        out << "# ";
        return;
    }
    out << root->data << " ";
    serialize(root->left, out);
    serialize(root->right, out);
}

Node* deserialize(istringstream &in) {
    string val;
    if (!(in >> val) || val == "#") return nullptr;
    Node* root = new Node(stoi(val));
    root->left = deserialize(in);
    root->right = deserialize(in);
    return root;
}

// Convert Binary Tree to Doubly Linked List (Inorder)
Node* bToDLL(Node* root, Node* &prev) {
    if (!root) return nullptr;
    Node* head = bToDLL(root->left, prev);
    if (!prev) head = root;
    else {
        prev->right = root;
        root->left = prev;
    }
    prev = root;
    bToDLL(root->right, prev);
    return head;
}

// Flatten Binary Tree to Linked List (Preorder)
Node* flatten(Node* root) {
    if (!root) return nullptr;
    if (root->left) {
        Node* left = flatten(root->left);
        Node* right = root->right;
        root->right = left;
        root->left = nullptr;
        Node* temp = root->right;
        while (temp->right) temp = temp->right;
        temp->right = flatten(right);
    } else root->right = flatten(root->right);
    return root;
}

// Path Sum (Root-to-Leaf)
bool hasPathSum(Node* root, int sum) {
    if (!root) return false;
    if (!root->left && !root->right) return sum == root->data;
    return hasPathSum(root->left, sum - root->data) || hasPathSum(root->right, sum - root->data);
}

// Zigzag (Spiral) Level Order Traversal
void zigzagTraversal(Node* root) {
    if (!root) return;
    stack<Node*> currLevel, nextLevel;
    currLevel.push(root);
    bool leftToRight = true;
    while (!currLevel.empty()) {
        Node* curr = currLevel.top(); currLevel.pop();
        if (curr) cout << curr->data << " ";
        if (leftToRight) {
            if (curr->left) nextLevel.push(curr->left);
            if (curr->right) nextLevel.push(curr->right);
        } else {
            if (curr->right) nextLevel.push(curr->right);
            if (curr->left) nextLevel.push(curr->left);
        }
        if (currLevel.empty()) {
            leftToRight = !leftToRight;
            swap(currLevel, nextLevel);
        }
    }
}

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    cout << "Inorder: "; inorder(root); cout << endl;
    cout << "Preorder: "; preorder(root); cout << endl;
    cout << "Postorder: "; postorder(root); cout << endl;
    cout << "Level Order: "; levelOrder(root); cout << endl;

    cout << "Total Nodes: " << countNodes(root) << endl;
    cout << "Leaf Nodes: " << countLeafNodes(root) << endl;
    cout << "Non-Leaf Nodes: " << countNonLeafNodes(root) << endl;
    cout << "Height: " << height(root) << endl;
    cout << "Sum of Nodes: " << sumNodes(root) << endl;
    cout << "Max Node: " << maxNode(root) << endl;
    cout << "Min Node: " << minNode(root) << endl;

    cout << "Diameter: " << diameter(root) << endl;
    cout << "Is Symmetric: " << (isSymmetric(root) ? "Yes" : "No") << endl;
    cout << "Max Level Sum: " << maxLevelSum(root) << endl;
    cout << "Max Width: " << maxWidth(root) << endl;

    cout << "Zigzag Traversal: "; zigzagTraversal(root); cout << endl;

    return 0;
}
