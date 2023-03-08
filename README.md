# AVL-Tree in C++
This GitHub repository contains a C++ implementation of an AVL tree, a self-balancing binary search tree. The implementation includes basic operations such as insertion, deletion, and searching, functions to maintain the balance of the tree, as well as options to manualy rotate nodes. 

<h2>Getting Started</h2>

To use this implementation, clone the repository and use the makefile to generate an executable called testapp. Once the executable is generated, you can run testapp to test the implementation.

git clone https://github.com/charlijj/AVL-Tree </br>
cd AVL-tree-cpp </br>
make </br>
./testapp </br>

Menu:
   
   I to insert a new element<br
   F to find an element with given key and print its data
   R to remove an element with given key
   P to print all elements,
   D to for debug data display
   H for help
   W for left-rotation
   X for right-rotation
   Y for left-right double rotation
   Z for right-left double rotation
   Q to quit.

or ./testapp < input.500 to test results of a tree with 500 nodes

<h2>Usage</h2>
  
The testapp program allows you to test the basic operations of the AVL tree, including insertion, deletion, and searching. The program will prompt you for input and display the results of each operation. There are also addtional operations that allow the user test manual rotations. 

<h2>Note</h2>
  
This program is for demonstration and testing purposes only. It is not production ready.
  
  
  
Created for CSCI 260 with Dr. Gara Pruesse
