#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

// ------------------ BST Basics ------------------

// Insert node into BST
Node* insertBST(Node* root, int val){
    if(!root) return new Node(val);
    if(val<root->val) root->left=insertBST(root->left,val);
    else root->right=insertBST(root->right,val);
    return root;
}

// Search in BST
bool searchBST(Node* root,int val){
    if(!root) return false;
    if(root->val==val) return true;
    return val<root->val ? searchBST(root->left,val) : searchBST(root->right,val);
}

// Find min node
Node* minNode(Node* root){ while(root->left) root=root->left; return root; }

// Find max node
Node* maxNode(Node* root){ while(root->right) root=root->right; return root; }

// Delete node from BST
Node* deleteBST(Node* root,int val){
    if(!root) return nullptr;
    if(val<root->val) root->left=deleteBST(root->left,val);
    else if(val>root->val) root->right=deleteBST(root->right,val);
    else{
        if(!root->left){ Node* temp=root->right; delete root; return temp; }
        if(!root->right){ Node* temp=root->left; delete root; return temp; }
        Node* temp=minNode(root->right);
        root->val=temp->val;
        root->right=deleteBST(root->right,temp->val);
    }
    return root;
}

// Count nodes
int countNodes(Node* root){ if(!root) return 0; return 1+countNodes(root->left)+countNodes(root->right); }

// Count leaf nodes
int countLeaf(Node* root){ if(!root) return 0; if(!root->left&&!root->right) return 1; return countLeaf(root->left)+countLeaf(root->right); }

// Count non-leaf nodes
int countNonLeaf(Node* root){ if(!root||(!root->left&&!root->right)) return 0; return 1+countNonLeaf(root->left)+countNonLeaf(root->right); }

// Height of BST
int heightBST(Node* root){ if(!root) return 0; return 1+max(heightBST(root->left),heightBST(root->right)); }

// ------------------ BST Traversals ------------------

// Inorder
void inorder(Node* root){ if(!root) return; inorder(root->left); cout<<root->val<<" "; inorder(root->right); }

// Preorder
void preorder(Node* root){ if(!root) return; cout<<root->val<<" "; preorder(root->left); preorder(root->right); }

// Postorder
void postorder(Node* root){ if(!root) return; postorder(root->left); postorder(root->right); cout<<root->val<<" "; }

// Level order
void levelOrder(Node* root){
    if(!root) return;
    queue<Node*> q; q.push(root);
    while(!q.empty()){
        Node* curr=q.front(); q.pop();
        cout<<curr->val<<" ";
        if(curr->left) q.push(curr->left);
        if(curr->right) q.push(curr->right);
    }
}

// ------------------ BST Queries ------------------

// Check if tree is BST
bool isBST(Node* root,int minv=INT_MIN,int maxv=INT_MAX){
    if(!root) return true;
    if(root->val<minv||root->val>maxv) return false;
    return isBST(root->left,minv,root->val-1) && isBST(root->right,root->val+1,maxv);
}

// Lowest Common Ancestor
Node* LCA(Node* root,int n1,int n2){
    if(!root) return nullptr;
    if(root->val>n1&&root->val>n2) return LCA(root->left,n1,n2);
    if(root->val<n1&&root->val<n2) return LCA(root->right,n1,n2);
    return root;
}

// Kth smallest element
void kthSmallestUtil(Node* root,int& k,int& ans){
    if(!root) return;
    kthSmallestUtil(root->left,k,ans);
    k--; if(k==0){ ans=root->val; return; }
    kthSmallestUtil(root->right,k,ans);
}
int kthSmallest(Node* root,int k){ int ans=-1; kthSmallestUtil(root,k,ans); return ans; }

// Floor value
int floorBST(Node* root,int val){
    int res=-1;
    while(root){
        if(root->val==val) return root->val;
        if(root->val>val) root=root->left;
        else{ res=root->val; root=root->right; }
    }
    return res;
}

// Ceiling value
int ceilBST(Node* root,int val){
    int res=-1;
    while(root){
        if(root->val==val) return root->val;
        if(root->val<val) root=root->right;
        else{ res=root->val; root=root->left; }
    }
    return res;
}

// Inorder predecessor
Node* inorderPredecessor(Node* root,int val){
    Node* pre=nullptr;
    while(root){
        if(root->val<val){ pre=root; root=root->right; }
        else root=root->left;
    }
    return pre;
}

// Inorder successor
Node* inorderSuccessor(Node* root,int val){
    Node* suc=nullptr;
    while(root){
        if(root->val>val){ suc=root; root=root->left; }
        else root=root->right;
    }
    return suc;
}

// Count nodes in a range
int countInRange(Node* root,int l,int r){
    if(!root) return 0;
    if(root->val<l) return countInRange(root->right,l,r);
    if(root->val>r) return countInRange(root->left,l,r);
    return 1+countInRange(root->left,l,r)+countInRange(root->right,l,r);
}

// ------------------ BST Construction ------------------

// Sorted array to BST
Node* sortedArrayToBST(vector<int>& arr,int l,int r){
    if(l>r) return nullptr;
    int m=(l+r)/2;
    Node* root=new Node(arr[m]);
    root->left=sortedArrayToBST(arr,l,m-1);
    root->right=sortedArrayToBST(arr,m+1,r);
    return root;
}

// ------------------ BST Advanced ------------------

// Merge two BSTs
void inorderStore(Node* root,vector<int>& v){
    if(!root) return;
    inorderStore(root->left,v);
    v.push_back(root->val);
    inorderStore(root->right,v);
}
Node* mergeTwoBSTs(Node* root1,Node* root2){
    vector<int> v1,v2; inorderStore(root1,v1); inorderStore(root2,v2);
    vector<int> merged(v1.size()+v2.size());
    merge(v1.begin(),v1.end(),v2.begin(),v2.end(),merged.begin());
    return sortedArrayToBST(merged,0,merged.size()-1);
}

// Distance between two nodes
int distFromRoot(Node* root,int val){
    if(root->val==val) return 0;
    if(val<root->val) return 1+distFromRoot(root->left,val);
    return 1+distFromRoot(root->right,val);
}
int distanceBetweenNodes(Node* root,int n1,int n2){
    Node* lca=LCA(root,n1,n2);
    return distFromRoot(lca,n1)+distFromRoot(lca,n2);
}

// Recover BST if two nodes swapped
Node* prevNode=nullptr;
Node* first=nullptr;
Node* second=nullptr;
void recoverBSTUtil(Node* root){
    if(!root) return;
    recoverBSTUtil(root->left);
    if(prevNode && root->val<prevNode->val){
        if(!first) first=prevNode;
        second=root;
    }
    prevNode=root;
    recoverBSTUtil(root->right);
}
void recoverBST(Node* root){
    first=second=prevNode=nullptr;
    recoverBSTUtil(root);
    if(first && second) swap(first->val,second->val);
}

// ------------------ MAIN ------------------
int main(){
    Node* root=nullptr;
    root=insertBST(root,50);
    root=insertBST(root,30);
    root=insertBST(root,70);
    root=insertBST(root,20);
    root=insertBST(root,40);
    root=insertBST(root,60);
    root=insertBST(root,80);

    cout<<"Inorder: "; inorder(root); cout<<endl;
    cout<<"Preorder: "; preorder(root); cout<<endl;
    cout<<"Postorder: "; postorder(root); cout<<endl;
    cout<<"Level Order: "; levelOrder(root); cout<<endl;
    cout<<endl;

    cout<<"Search 40: "<<searchBST(root,40)<<endl;
    cout<<"Min Node: "<<minNode(root)->val<<endl;
    cout<<"Max Node: "<<maxNode(root)->val<<endl;

    cout<<"Delete 20"<<endl; root=deleteBST(root,20); inorder(root); cout<<endl;
    cout<<"Height: "<<heightBST(root)<<endl;
    cout<<"Count Nodes: "<<countNodes(root)<<endl;
    cout<<"Count Leaf Nodes: "<<countLeaf(root)<<endl;

    cout<<"Is BST: "<<isBST(root)<<endl;
    Node* lca=LCA(root,40,60);
    cout<<"LCA of 40 and 60: "<<lca->val<<endl;
    cout<<"Kth Smallest(3): "<<kthSmallest(root,3)<<endl;
    cout<<"Floor of 65: "<<floorBST(root,65)<<endl;
    cout<<"Ceil of 65: "<<ceilBST(root,65)<<endl;

    vector<int> arr={10,20,30,40,50,60,70};
    Node* bst2=sortedArrayToBST(arr,0,arr.size()-1);
    cout<<"Merged BST Inorder: "; Node* merged=mergeTwoBSTs(root,bst2); inorder(merged); cout<<endl;

    return 0;
}
