/*
Consider a situation where we have a set of intervals and we need following operations to be implemented efficiently.
1) Add an interval
2) Remove an interval
3) Given an interval x, find if x overlaps with any of the existing intervals.

Every node of Interval Tree stores following information.
a) i: An interval which is represented as a pair [low, high]
b) mx: Maximum high value in subtree rooted with this node.

Interval overlappingIntervalSearch(root, x)
1) If x overlaps with root's interval, return the root's interval.

2) If left child of root is not empty and the max  in left child
is greater than x's low value, recur for left child

3) Else recur for right child.
*/
#include <iostream>
using namespace std;
struct interval{
    int low, high;
};
// Structure to represent a node in Interval Search Tree
struct node{
    interval *cur;  // 'cur' could also be a normal variable
    int mx;
    node *lft, *rght;
};
// A utility function to create a new Interval Search Tree Node
node * newnode(interval cur){
    node *temp = new node;
    temp->cur = new interval(cur);
    temp->mx = cur.high;
    temp->lft = temp->rght = NULL;
    return temp;
};

// A utility function to insert a new Interval Search Tree Node
// This is similar to BST Insert.  Here the low value of interval
// is used to maintain BST property
node *Insert(node *root, interval cur){
    // Base case: Tree is empty, new node becomes root
    if (root == NULL)
        return newnode(cur);
    // Get low value of interval at root
    int lo = root->cur->low;
    // If root's low value is smaller, then new interval goes to
    // left subtree
    if (cur.low < lo)
        root->lft = Insert(root->lft, cur);

    // Else, new node goes to right subtree.
    else
        root->rght = Insert(root->rght, cur);

    // Update the max value of this ancestor if needed
    if (root->mx < cur.high)
        root->mx = cur.high;

    return root;
}

// A utility function to check if given two intervals overlap
bool Overlap(interval i1, interval i2){
    if (i1.low <= i2.high && i2.low <= i1.high) return true;
    return false;
}

// The main function that searches a given interval i in a given
// Interval Tree.
interval *Search(node *root, interval cur){
    // Base Case, tree is empty
    if (root == NULL) return NULL;
    // If given interval overlaps with root
    if (Overlap(*(root->cur), cur))
        return root->cur;
    // If left child of root is present and max of left child is
    // greater than or equal to given interval, then cur may
    // overlap with an interval is left subtree
    if (root->lft != NULL && root->lft->mx >= cur.low)
        return Search(root->lft, cur);

    // Else interval can only overlap with right subtree
    return Search(root->rght, cur);
}

void inorder(node *root){
    if (root == NULL) return;
    inorder(root->lft);
    cout << "[" << root->cur->low << ", " << root->cur->high << "]"
         << " max = " << root->mx << endl;
    inorder(root->rght);
}
int main(){
    // Let us create interval tree shown in above figure
    interval arr[] = {{15, 20}, {10, 30}, {17, 19},
        {5, 20}, {12, 15}, {30, 40}};
    int n = sizeof(arr)/sizeof(arr[0]);
    node *root = NULL;
    for (int i = 0; i < n; i++)
        root = Insert(root, arr[i]);
//    cout << "Inorder traversal of constructed Interval Tree is\n";
//    inorder(root);
    interval x = {6, 7};
    cout << "\nSearching for interval [" << x.low << "," << x.high << "]";
    interval *res = Search(root, x);
    if (res == NULL)
        cout << "\nNo Overlapping Interval";
    else
        cout << "\nOverlaps with [" << res->low << ", " << res->high << "]";
    return 0;
}
