#include <bits/stdc++.h>
using namespace std;

// ------------------ Node Structure ------------------
struct Node {
    int val;
    Node* next;
    Node(int v): val(v), next(nullptr) {}
};

// ------------------ Basic Operations ------------------

// Insert at head
Node* insertHead(Node* head,int val){
    Node* newNode=new Node(val);
    newNode->next=head;
    return newNode;
}

// Insert at tail
Node* insertTail(Node* head,int val){
    Node* newNode=new Node(val);
    if(!head) return newNode;
    Node* temp=head;
    while(temp->next) temp=temp->next;
    temp->next=newNode;
    return head;
}

// Delete node by value
Node* deleteNode(Node* head,int val){
    if(!head) return nullptr;
    if(head->val==val){ Node* temp=head->next; delete head; return temp; }
    Node* temp=head;
    while(temp->next && temp->next->val!=val) temp=temp->next;
    if(temp->next){ Node* del=temp->next; temp->next=del->next; delete del; }
    return head;
}

// Search value
bool searchNode(Node* head,int val){
    while(head){ if(head->val==val) return true; head=head->next; }
    return false;
}

// Print list
void printList(Node* head){
    while(head){ cout<<head->val<<" -> "; head=head->next; }
    cout<<"NULL"<<endl;
}

// Count nodes
int countNodes(Node* head){
    int cnt=0;
    while(head){ cnt++; head=head->next; }
    return cnt;
}

// ------------------ Reversal ------------------

// Reverse linked list iteratively
Node* reverseList(Node* head){
    Node *prev=nullptr, *curr=head;
    while(curr){ Node* next=curr->next; curr->next=prev; prev=curr; curr=next; }
    return prev;
}

// Reverse linked list recursively
Node* reverseListRecursive(Node* head){
    if(!head || !head->next) return head;
    Node* rest=reverseListRecursive(head->next);
    head->next->next=head;
    head->next=nullptr;
    return rest;
}

// ------------------ Cycle Detection ------------------

// Detect cycle (Floyd’s algorithm)
bool detectCycle(Node* head){
    Node *slow=head,*fast=head;
    while(fast && fast->next){
        slow=slow->next;
        fast=fast->next->next;
        if(slow==fast) return true;
    }
    return false;
}

// Find start of cycle
Node* detectCycleStart(Node* head){
    Node *slow=head,*fast=head;
    while(fast && fast->next){
        slow=slow->next;
        fast=fast->next->next;
        if(slow==fast){
            slow=head;
            while(slow!=fast){ slow=slow->next; fast=fast->next; }
            return slow;
        }
    }
    return nullptr;
}

// Remove cycle
void removeCycle(Node* head){
    Node* start=detectCycleStart(head);
    if(!start) return;
    Node* temp=start;
    while(temp->next!=start) temp=temp->next;
    temp->next=nullptr;
}

// ------------------ Advanced Problems ------------------

// Middle of linked list
Node* middleNode(Node* head){
    Node *slow=head,*fast=head;
    while(fast && fast->next){ slow=slow->next; fast=fast->next->next; }
    return slow;
}

// Kth node from end
Node* kthFromEnd(Node* head,int k){
    Node *first=head,*second=head;
    for(int i=0;i<k;i++) if(first) first=first->next;
    while(first){ first=first->next; second=second->next; }
    return second;
}

// Merge two sorted linked lists
Node* mergeSorted(Node* l1,Node* l2){
    if(!l1) return l2;
    if(!l2) return l1;
    if(l1->val>l2->val) swap(l1,l2);
    Node* res=l1;
    while(l1 && l2){
        Node* temp=nullptr;
        while(l1 && l1->val<=l2->val){ temp=l1; l1=l1->next; }
        temp->next=l2;
        swap(l1,l2);
    }
    return res;
}

// Remove duplicates from sorted list
Node* removeDuplicates(Node* head){
    Node* curr=head;
    while(curr && curr->next){
        if(curr->val==curr->next->val){ Node* del=curr->next; curr->next=del->next; delete del; }
        else curr=curr->next;
    }
    return head;
}

// Palindrome linked list
bool isPalindrome(Node* head){
    Node* slow=head,*fast=head;
    stack<int> st;
    while(fast && fast->next){ st.push(slow->val); slow=slow->next; fast=fast->next->next; }
    if(fast) slow=slow->next;
    while(slow){ if(st.top()!=slow->val) return false; st.pop(); slow=slow->next; }
    return true;
}

// Intersection of two linked lists
Node* getIntersection(Node* headA,Node* headB){
    Node* a=headA,*b=headB;
    while(a!=b){ a=a?a->next:headB; b=b?b->next:headA; }
    return a;
}

// ------------------ MAIN ------------------
int main(){
    Node* head=nullptr;
    head=insertTail(head,1);
    head=insertTail(head,2);
    head=insertTail(head,3);
    head=insertTail(head,4);
    head=insertTail(head,5);
    printList(head);

    cout<<"Search 3: "<<searchNode(head,3)<<endl;
    cout<<"Count: "<<countNodes(head)<<endl;

    head=reverseList(head);
    cout<<"Reversed: "; printList(head);

    Node* mid=middleNode(head);
    cout<<"Middle Node: "<<mid->val<<endl;

    Node* kth=kthFromEnd(head,2);
    cout<<"2nd from end: "<<kth->val<<endl;

    Node* head2=nullptr;
    head2=insertTail(head2,2);
    head2=insertTail(head2,4);
    head2=insertTail(head2,6);

    Node* merged=mergeSorted(head,head2);
    cout<<"Merged list: "; printList(merged);

    merged=removeDuplicates(merged);
    cout<<"After removing duplicates: "; printList(merged);

    cout<<"Is palindrome: "<<isPalindrome(merged)<<endl;

    return 0;
}
