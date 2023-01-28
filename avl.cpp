// Implemented by Jasper Charlinski
// 658366497

#include "avl.h"

void avl::deallocate(node* &n)
// delete all nodes in the subtree rooted at n,
//    and set n to null
{
   if (n == NULL) return;
   deallocate(n->left);
   deallocate(n->right);
   delete n;
   n = NULL; 
}

bool avl::insert(node* &subtree, node* n)
// insert a new node in the bst rooted at subtree,
// returning true if successful, false otherwise
//
{
   if (n == NULL) // If not enough memory to create a new node
   {
      return false;
   }

   // if we've found the end of a chain,
   //    insert the node here
   if (subtree == NULL) 
   {
      subtree = n;
      return true;
   }

   if (subtree->key > n->key) // if the new node's key is less thn than the current subtree's key
   {
      n->parent = subtree;
      insert(subtree->left, n); // insert to the left
   } 
   else // if the new node's key is greater than than the current subtree's key
   {
      n->parent = subtree;
      insert(subtree->right, n); // insert to the right
   } 

   updatePositionData_node(subtree); // update the height and BF of the current subtree

   // comment this out to test manual rotations ----------------------------------------
   if (subtree->BF > 1 || subtree->BF < -1) // if the current subtree is not an avl tree
   {
      rebalance(subtree);
   }
   // -----------------------------------------------------------------------------------
   return true;
}

bool avl::insert(int k, string d)
// public helper fo insert function
   // takes in a key k, and data d,
   // return true if successful, false if otherwise.
{
   node* n = find(k, root); // search if key already exists
         
   if (n) // if key already exists, updated the data of the node and return
   {
      cout << "Node with key " << k << " already exist, data updated" << endl;
      n->data = d;
      return false;
   }

   n = create(k ,d); // create new node with key k and data d

   if (n != NULL) // if the node was successfully created
   {
      if (insert(root, n))
      {
         return true;
      }
      else{delete n;} // If node was not successfully inserted, delete the new node
   }

   return false;
}

avl::node* avl::create(int k, string d)
// initializes a new node n and assigns the given key and data values
{
   node* n = new node;

   if (n != NULL)
   {
      n->key = k;
      n->data = d;
      n->left = NULL;
      n->right = NULL;
      n->parent = NULL;
      n->height = 0;
      n->BF = 0;
   }

   return n;
}

avl::node* avl::find(int k, node* n)
// finds a node with the given key starting from the root
   // if no node with key k exists returns NULL
{
   if (n == NULL) // if no node with key k is found / if tree does not exist 
   {
      return n;
   }

   if (k == n->key) // if node with key k is found 
   {
		return n;
   }

   // else search tree
   if (n->key > k)
   {
		return find(k, n->left);
   }

   return find(k, n->right);
}

avl::node* avl::deleteElement(int k, node* &n)
// if the subtree rooted at n contains a node whose key
//    matches k then remove it from the subtree, and return true,
//    otherwise return false.
{
	if (n==NULL) // if tree is NULL
   {
      return 0;
   }
   // else, search for key k
   else if (k < n->key)
   {
      n->left = deleteElement(k, n->left);
   }
   else if (k > n->key)
   {
      n->right = deleteElement(k, n->right);
   }
   // if key is found
   else
   {
      if (n->left == NULL && n->right == NULL) // if node has no children
      {
         delete n;
         n = NULL;
         return n;
      }
      else if (n->left == NULL) // if node only has a right child
      {
         node* tmp = n;
         n = n->right;
         delete tmp;
      }
      else if (n->right == NULL) // if node only has a left child
      {
         node* tmp = n;
         n = n->left;
         delete tmp; 
      }
      else // if node has both children
      {
         node* tmp = minimum(n->right); // get smallest child of node's right subtree
         swapElements(n, n->left);
         n->right = deleteElement(tmp->key, n->right);
      }
   }

   updatePositionData_tree (n);

   if (n->BF > 1 || n->BF < -1)
   {
      rebalance(n);
   }

   return n;
}

void avl::print(node *n)
// display the key/data contents of the subtree rooted at n,
// sorted (ascending) by key value
{

   if (n == NULL) return;
   print(n->left);
   cout << endl << n->key << ":" << n->data << "  height: " << n->height << "  BF: " << n->BF  << endl; // Parent: " << parent
   print(n->right);
}

void avl::debugprint(node *n)
// display the contents and structure of the subtree rooted at n,
// performed via preorder traversal
{
   if (n == NULL) return;
   cout << n->key << ":" << n->data << " (";
   if (n->left) cout << n->left->key;
   else cout << "NULL";
   cout << "<-left,right->";
   if (n->right) cout << n->right->key;
   else cout << "NULL";
   cout << ") " << " height: " << n->height << " BF: " << n->BF << endl; // I made it also print out height and BF and a endl

   debugprint(n->left);
   debugprint(n->right);
}

void avl::swapElements(node* n, node* m)
// only used in deleteElement
{
   node temp;
   temp.data = n->data;
   n->data = m->data;
   m->data = temp.data;

   temp.key = n->key;
   n->key= m->key;
   m->key= temp.key;

//   temp.height = n->height;
//   n->height = m->height;
//   m->height = temp.height;

//   temp.BF = n->BF;
//   n->BF = m->BF;   
//   m->BF = temp.BF;
}

int avl::max(int a, int b)
// returns the max of two integers
{
   if (a >= b)
   {
      return a;
   }
   return b;
}

bool avl::rotateRight(node* n)
// rotate a node and its subtree right
   // if successful returns true, otherwise returns false
{
   node* y = n->left;

   if (y == NULL)
   {
      return false; // right rotate not possible if left child of n is NULL
   }

   n->left = y->right;

   if (y->right != NULL)
   {
      y->right->parent = n;
   }

   y->parent = n->parent;

   if (n->parent == NULL)
   {
      root = y;
   }
   else if (n == n->parent->right)
   {
      n->parent->right = y;
   }
   else 
   {
      n->parent->left = y;
   }

   y->right = n;
   n->parent = y;

   return true;
}

bool avl::rotateLeft(node* n)
// rotate a node and its subtree right
   // if successful returns true, otherwise returns false
{
   node* y = n->right;

   if (y == NULL) // left rotate not possible if right child of n is NULL
   {
      return false;
   }

   n->right = y->left;

   if (y->left != NULL)
   {
      y->left->parent = n;
   }

   y->parent = n->parent;

   if (n->parent == NULL)
   {
      root = y;
   }
   else if (n == n->parent->left)
   {
      n->parent->left = y;
   }
   else 
   {
      n->parent->right = y;
   }

   y->left = n;
   n->parent = y;

   return true;
}

bool avl::rotateR(int k)
// finds a node from the key it is passed and attempts to rotate it right
   // if successful returns true, otherwise returns false
{
   node* n = find(k, root);

   if (n != NULL) // if node with key k exists
   {
      if (rotateRight(n))
      {
         updatePositionData_tree(n); // update the height and BF of the tree
         return true;
      }
   }
   return false;
}

bool avl::rotateL(int k)
// finds a node from the key it is passed and attempts to rotate it to the left
   // if successful returns true, otherwise returns false
{
   node* n = find(k, root);

   if (n != NULL)
   {
      if (rotateLeft(n))
      {
         updatePositionData_tree(n);
         return true;
      }
   }
   return false;
}

bool avl::rotateRL(int k)
// finds a node from the key it is passed and attempts to rotate it to double rotate it right-left
   // if successful returns true, otherwise returns false
{
   node* n = find(k, root);

   if (n != NULL)
   {
      if (rotateL(n->left->key))
      {
         if (rotateRight(n))
         {
            updatePositionData_tree(n);
            return true;
         }
      }
   }
   return false;
}

bool avl::rotateLR(int k)
// finds a node from the key it is passed and attempts to rotate it to double rotate it left-right
   // if successful returns true, otherwise returns false
{
   node* n = find(k, root);

   if (n != NULL)
   {
      if (rotateR(n->right->key))
      {
         if (rotateLeft(n))
         {
            updatePositionData_tree(n);
            return true;
         }
      }
   }
   return false;
}

void avl::updatePositionData_node(node* n)
// updates the height and BF of the node it is passed
{
   if (n == NULL)
   {
      return;
   }

   if (n->left && n->right) // If the current node has left and right children
   {
      n->height = max(n->left->height, n->right->height) + 1; // The height of the current node is the max height of its children plus one

      n->BF = n->right->height - n->left->height;
   }
   else if (n->left && n->right == NULL) // If the current node has a left child but no right child
   {
      n->height = n->left->height + 1; // The height of the current node is the height of its left child plus one
      n->BF =  0 - n->left->height - 1; // The BF of the current node is 0 minus the height of its left child
   }
   else if (n->left == NULL && n->right) // If the current node has a right child but no left child
   {
      n->height = n->right->height + 1; // The height of the current node is the height of its right child plus one
      n->BF = n->right->height + 1; // The BF of the current node is the height of its right child
   }
   else if (n->left == NULL && n->right == NULL)
   {
      n->height = 0;
      n->BF = 0;
   }
   // For all other cases height and BF does not change
}

void avl::updatePositionData_tree(node* n)
// recursively updates the height and BF of the node it is passed
// and the parents of the node until the root is reached
{
   if (n == NULL)
   {
      return;
   }
   updatePositionData_node(n); // updated the height and BF of the node
   updatePositionData_tree(n->parent); // recurse through node n's parents
}

void avl::rebalance(node* n)
// rotates the passed node right, left, right-left, or left-right depending on the BF of the node and it children
{
   if (n->BF > 0) // node is right heavy
   {
      if (n->right->BF < 0) // if node's right child is left heavy
      {
         // rotate node left-right
         rotateR(n->right->key);
         rotateL(n->key);
      }
      else
      {
         rotateL(n->key);
      }
   }
   else if (n->BF < 0) // if node is left heavy
   {
      if (n->left->BF > 0) // if node's left child is right heavy 
      {
         // rotate node right-left
         rotateL(n->left->key);
         rotateR(n->key);
      }
      else
      {
         rotateR(n->key);
      }
   }
}
