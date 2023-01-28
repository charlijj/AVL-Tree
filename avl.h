// Jasper Charlinski
// 658366497

#ifndef AVL
#define AVL 1

#include <string>
#include <iostream>
using namespace std;

class avl{
   private:
      struct node {
          node *right, *left, *parent;
          string data;
          int key;
          int BF = 0;
          int height; 
      };
      // we maintain a pointer to the root of the tree
      node *root = NULL;

      // private, recursive routines
      // (used by the public methods)
      void deallocate(node* &n);
      bool insert(node* &subtree, node* n);
      node* deleteElement(int k, node* &n);
      node* find(int k, node* n);
      void print(node *n);
      void debugprint(node *n); 
      void swapElements(node* n, node* m);

      // methods I added ------------------------------------
      int max(int a, int b);
      node* create(int k, string d);
      void updatePositionData_node(node* n);
      void updatePositionData_tree(node* n);
      bool rotateRight(node* n);
      bool rotateLeft(node* n);
      void rebalance(node* n);
      node* minimum(node* n){while (n->left != NULL) {n=n->left;}return n;} // returns smallest child node

   public:
      avl() { root = NULL; root->parent == NULL;}
      ~avl() { deallocate(root); }
      void display() { print(root); }
      void debug() { debugprint(root); }
      bool insert(int k, string d);
      bool deleteElement(int k) {deleteElement(k, root); return true;}
      string find( int k) {node* temp = find(k, root); if (temp==NULL) return ""; return temp->data;}
      bool rotateR(int k);
      bool rotateL(int k);
      bool rotateRL(int k);
      bool rotateLR(int k);
};

#endif
