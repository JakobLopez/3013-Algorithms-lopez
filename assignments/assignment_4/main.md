```
///////////////////////////////////////////////////////////////////////////////
// Title:            Binary Search Tree
// Files:            main.cpp , BSTree.cpp , BSTree.h , before.txt , after.txt
// Semester:         3013 Algorithms Spring 2018
//
// Author:           Jakob Lopez
// Email:            thejakoblopez@gmail.com
// Description:
//       This is an implementation of a binary search tree. Items with a lesser 
//		 value than the root will be placed to the root's left, and vice versa.
//		 Because the tree is ordered, it searches in O(logn) ,and in worst case
//		 scenario it's O(height).The tree is outputted to a file so that we can
//		 visualize it. 
/////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include"BSTree.h"
using namespace std;

//http://www.webgraphviz.com/


int main()
{
	srand(2342);

	BSTree B;

	B.insert(38);
	B.insert(10);
	B.insert(29);
	B.insert(27);
	B.insert(5);
	B.insert(43);
	B.insert(36);
	B.insert(3);
	B.printLevelOrder();
	B.GraphVizOut("before.txt");


	/*B.deleteNode(10);
	B.deleteNode(5);
	B.deleteNode(36);
	B.deleteNode(38);
	B.deleteNode(43);
	B.deleteNode(29);
	B.deleteNode(27);
	B.deleteNode(3);*/



	while (B.top())
	{
		cout << "removing: " << B.top() << endl;
		B.deleteNode(B.top());
	}

	B.printLevelOrder();

	B.GraphVizOut("after.txt");
	system("pause");
	return 0;
}
```
