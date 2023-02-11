// Jasper Charlinski
// 658366497

#include "avl.h"
#include <iostream>

char getcommand();
void printmenu();
bool processcommand(char cmd, avl &tree);

int main()
{
   avl B;
   
   printmenu();
   char cmd = getcommand();
   while (processcommand(cmd, B)) { 
      cout << endl;
      cmd = getcommand();
   }

   return 0;
}

char getcommand()
{
   cout << "Enter your command choice (D, P, H, I, Q, R, W, X, Y, or Z)" << endl;
   char cmd;
   cin >> cmd;
   cmd = toupper(cmd);
   switch (cmd) {
      case 'H':
      case 'I':
      case 'R':
      case 'F':
      case 'W': 
      case 'X': 
      case 'Y': 
      case 'Z': 
      case 'P':
      case 'Q':
      case 'D': return cmd;
      default:  cout << "You have entered an invalid command" << endl;
                cin.clear(); cin.ignore(265, '\n'); 
                return getcommand();
   }
}

void printmenu()
{
   cout << "Enter I to insert a new element," << endl;
   cout << "   or F to find an element with given key and print its data," << endl;
   cout << "   or R to remove an element with given key," << endl;
   cout << "   or P to print all elements," << endl;
   cout << "   or D to for debug data display," << endl;
   cout << "   or H for help," << endl;
   cout << "   or W for left-rotation," << endl;
   cout << "   or X for right-rotation," << endl;
   cout << "   or Y for left-right double rotation," << endl;
   cout << "   or Z for right-left double rotation," << endl;
   cout << "   or Q to quit." << endl;
}

bool processcommand(char cmd, avl &tree)
{
   int k; string d;
   int find_key;
   switch (cmd) {
      case 'H': 
               printmenu(); 
               break;
      case 'I': 
               cout << "Enter the key integer" << endl;
               cin >> k;
               cout << "Enter the data word" << endl;
               cin >> d;
               cout << "(" << k << "," << d << ") ";
               if (tree.insert(k, d)) 
               {
               cout << k << " was inserted successfully" << endl;
               break;
               }
               cout << "Error: " << k << " was not inserted correctly" << endl;
               break;
      case 'R': 
               cout << "Enter the key integer" << endl;
               cin >> k;
               if (tree.deleteElement(k))
               {
               cout << k << " was successfully deleted." << endl;
               break;
               }
               cout << "Error: " << k << " was not deleted -- not in tree." << endl;
               break;
      case 'P': 
               cout << "The tree contents are: ";
               tree.display();
               break; 
      case 'D': 
               cout << "The tree debug data is:" << endl;
               tree.debug();
               break;
      case 'F': 
               cout << "Enter the key of the node you would like to find:" << endl;
               cin >> find_key;
               d = tree.find(find_key);
               if (d == "")
               {
               cout << "Error: No node found with key " << find_key << endl;
               break;
               }
               cout << "The data at key " << find_key << " is: " << d << endl;
               break;
      case 'W': 
               cout << "Enter the key of the node you would like to rotate left:" << endl;
               cin >> k;
               if (tree.rotateL(k))
               {
               cout << k << " was successfully rotated." << endl;
               break;
               }
               cout << "Error: left rotation of " << k << " was unsuccessful." << endl;
               break;
      case 'X': 
               cout << "Enter the key of the node you would like to rotate right:" << endl;
               cin >> k;
               if (tree.rotateR(k))
               {
               cout << k << " was successfully rotated." << endl;
               break;
               }
               cout << "Error: right rotation of " << k << " was unsuccessful." << endl;
               break;
      case 'Y': 
               cout << "Enter the key of the node you would like to rotate left-right:" << endl;
               cin >> k;
               if (tree.rotateLR(k))
               {
               cout << k << " was successfully rotated." << endl;
               break;
               }
               cout << "Error: left-right rotation of " << k << " was unsuccessful." << endl;
               break;
      case 'Z': 
               cout << "Enter the key of the node you would like to rotate right-left:" << endl;
               cin >> k;
               if (tree.rotateRL(k))
               {
               cout << k << " was successfully rotated." << endl;
               break;
               }
               cout << "Error: right-left rotation of " << k << " was unsuccessful." << endl;
               break;
      default:  
               return false;
   }
   return true;
}

