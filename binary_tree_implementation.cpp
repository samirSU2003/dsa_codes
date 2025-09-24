#include <bits/stdc++.h>
using namespace std;

// Node structure
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v): val(v), left(nullptr), right(nullptr) {}
};

// Insert in Binary Tree (level order insertion for example)
TreeNode* insertLevelOrder(TreeNode* root, int val){
    TreeNode* newNode = new TreeNode(val);
    if(!root) return newNode;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        TreeNode* temp = q.front(); q.pop();
        if(!temp->left){ temp->left = newNode; return root; }
        else q.push(temp->left);
        if(!temp->right){ temp->right = newNode; return root; }
        else q.push(temp->right);
    }
    return root;
}

// Traversals
void inorder(TreeNode* root){
    if(!root) return;
    inorder(root->left);
    cout<<root->val<<" ";
    inorder(root->right);
}

void preorder(TreeNode* root){
    if(!root) return;
    cout<<root->val<<" ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(TreeNode* root){
    if(!root) return;
    postorder(root->left);
    postorder(root->right);
    cout<<root->val<<" ";
}

void levelOrder(TreeNode* root){
    if(!root) return;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        TreeNode* temp = q.front(); q.pop();
        cout<<temp->val<<" ";
        if(temp->left) q.push(temp->left);
        if(temp->right) q.push(temp->right);
    }
}

// Height of tree
int height(TreeNode* root){
    if(!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

// Count nodes
int countNodes(TreeNode* root){
    if(!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// ------------------ MAIN ------------------
int main(){
    TreeNode* root = nullptr;
    root = insertLevelOrder(root,1);
    root = insertLevelOrder(root,2);
    root = insertLevelOrder(root,3);
    root = insertLevelOrder(root,4);
    root = insertLevelOrder(root,5);

    cout<<"Inorder: "; inorder(root); cout<<endl;
    cout<<"Preorder: "; preorder(root); cout<<endl;
    cout<<"Postorder: "; postorder(root); cout<<endl;
    cout<<"Level Order: "; levelOrder(root); cout<<endl;
    cout<<"Height: "<<height(root)<<endl;
    cout<<"Total Nodes: "<<countNodes(root)<<endl;

    return 0;
}
