```
///////////////////////////////////////////////////////////////////////////////
// Title:            Program 3 Part 2
// Files:            main.cpp, BSTree.cpp/h, AVLtree.cpp/h, adjectives.txt
//					 nouns.txt, verbs.txt, adverbs.txt, animals.txt, 
//					 tenthousandwords.txt, analysis.out
// Semester:         3013 Algorithms Spring 2018
//
// Author:           Jakob Lopez
// Email:            thejakoblopez@gmail.com
// Description:
//       This program compares the performances of an AVL tree to a BS tree.
//		 Word components are loaded into the trees. 10,000 crazy words are used
//		 word-by-word to search the trees so a counter can be incremented.
//		 This program is ran from command line.
/////////////////////////////////////////////////////////////////////////////////

#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include "BSTree.h"
#include "AVLtree.h"
using namespace std;

void closeFiles(ifstream&, ifstream&, ifstream&, ifstream&, ifstream&,ofstream&);
int getWordCount(map<string, string>&, ifstream&, string);
void loadTrees(AVL&, BST&, ifstream&);
void openFiles(ifstream&, ifstream&, ifstream&, ifstream&, ifstream&,ofstream&);
void searchTrees(AVL&, BST&, ifstream&);

int main(int argc, char **argv)
{
	//Opens files to read from and write to
	ifstream adjIn, nounIn, verbIn, adverbIn, animalIn;
	ifstream wordFile;
	ofstream ofile;
	openFiles(adjIn, nounIn, verbIn, adverbIn, animalIn,ofile);

	int adjCount, vCount, nCount, advCount, anCount;

	// count command line args and make sure 
	// a file name is on the line to run this file
	if (argc<2) {
		cout << "You need an input file!\n";
		cout << "Usage: stlmap filename.txt";
		exit(0);
	}

	//File name of 10,000 words  
	string file = argv[1];

	//Open 10,000 word file
	wordFile.open(file);

	// declare stl map
	map<string, string> adj;
	map<string, string> n;
	map<string, string> v;
	map<string, string> adv;
	map<string, string> an;

	//Declare instance of BST and AVL
	BST B;
	AVL A;

	//Loads map with words
	adjCount = getWordCount(adj, adjIn, "adjective");
	nCount = getWordCount(n, nounIn, "noun");
	vCount = getWordCount(v, verbIn, "verb");
	advCount = getWordCount(adv, adverbIn, "adverb");
	anCount = getWordCount(an, animalIn, "animal");

	
	//Loads Binary Search Tree and AVL tree with words
	loadTrees(A, B,adjIn);
	loadTrees(A, B, nounIn);
	loadTrees(A, B, verbIn);
	loadTrees(A, B,  adverbIn);
	loadTrees(A, B, animalIn);


	//Search BST for words in a file
	searchTrees(A ,B, wordFile);

	cout << "Number of BST comparisons: " << B.totalComparisons() << endl;
	cout << "Number of AVL comparisons: " << A.totalComparisons() << endl;
	cout << "Number of Adjectives: " << adjCount << endl;
	cout << "Number of Nouns: " << nCount << endl;
	cout << "Number of Verbs: " << vCount << endl;
	cout << "Number of Adverbs: " << advCount << endl;
	cout << "Number of Animals: " << anCount << endl;

	ofile << "Number of BST comparisons: " << B.totalComparisons() << endl;
	ofile << "Number of AVL comparisons: " << A.totalComparisons() << endl;
	ofile << "Number of Adjectives: " << adjCount << endl;
	ofile << "Number of Nouns: " << nCount << endl;
	ofile << "Number of Verbs: " << vCount << endl;
	ofile << "Number of Adverbs: " << advCount << endl;
	ofile << "Number of Animals: " << anCount << endl;

	//Closes files
	closeFiles(adjIn, nounIn, verbIn, adverbIn, animalIn,ofile);
	wordFile.close();
	system("pause");
	
	return 0;
}

/**
* @FunctionName: closeFiles
* @Description:
*    closes files
* @Params:
*    ifstream &adjIn - adjective file
*    ifstream &nounIn - noun file
*    ifstream &verbIn - verb file
*    ifstream &adverbIn - adverb file
*    ifstream &animalIn - animal file
*    ofstream &ofile - outfile
* @Returns:
*    void
*/
void closeFiles(ifstream& adjIn, ifstream& nounIn, ifstream& verbIn, ifstream& adverbIn, ifstream& animalIn,ofstream& ofile)
{
	adjIn.close();
	nounIn.close();
	verbIn.close();
	adverbIn.close();
	animalIn.close();
	ofile.close();
}



/**
* @FunctionName: getWordCount
* @Description:
*    Reads words from a file counts number of words(doesn't include duplicates)
* @Params:
*    map<string, string>& m - address to map
*    ifstream &infile - file to read from
*	 string type - type of word component
* @Returns:
*    int - number of non-repeated words in file
*/
int getWordCount(map<string, string>& m, ifstream &infile, string type)
{
	string crazyword;
	int count = 0;

	//Read 10,000 words into stlmap ensuring there are no dups
	while (!infile.eof())
	{
		infile >> crazyword;
		//Makes sure no repeated words enter map
		if (m.find(crazyword) == m.end())
		{
			m[crazyword] = type;
			count++;
		}
	}
	return count;
}

/**
* @FunctionName: loadTrees
* @Description:
*    Loops through an array of strings and inserts them in an AVL and BS tree
* @Params:
*    AVL &A - address of an AVL tree object
*	 BST &B - address of a BS tree object
*    string *wordComponent - pointer to an array of strings
*	 int size - size of array
* @Returns:
*    void
*/
void loadTrees(AVL &A, BST &B, ifstream& infile)
{
	string word;
	map<string, string> m;

	//Starts reading from beginning of file
	infile.clear();
	infile.seekg(0, ios::beg);

	while (!infile.eof())
	{
		infile >> word;
		if (m.find(word) == m.end())
		{
			A.insert(word);
			B.insert(word);
		}
		m[word] = "word";
	}

}

/**
* @FunctionName: openFiles
* @Description:
*    opens files
* @Params:
*    ifstream &adjIn - adjective file
*    ifstream &nounIn - noun file
*    ifstream &verbIn - verb file
*    ifstream &adverbIn - adverb file
*    ifstream &animalIn - animal file
*    ofstream &ofile - outfile
* @Returns:
*	 none
*/
void openFiles(ifstream& adjIn, ifstream& nounIn, ifstream& verbIn, ifstream& adverbIn, ifstream& animalIn, ofstream &ofile)
{
	adjIn.open("adjectives.txt");
	nounIn.open("nouns.txt");
	verbIn.open("verbs.txt");
	adverbIn.open("adverbs.txt");
	animalIn.open("animals.txt");
	ofile.open("analysis.out");
}

/**
* @FunctionName: searchBST
* @Description:
*    Searches Binary Search Tree for each word in file
* @Params:
*    BST &B - address of a BS tree object
*    ofstream &wordOut - allows to write/read to file
* @Returns:
*    void
*/
void searchTrees(AVL &A, BST &B, ifstream& wordFile)
{
	string word;

	//Starts reading from beginning of file
	wordFile.clear();
	wordFile.seekg(0, ios::beg);

	wordFile >> word;
	//Reads until end of file
	while (!wordFile.eof())
	{
		//If word is not a space character
		if (word != " ")
		{
			A.search(word);
			B.search(word);
		}

		wordFile >> word;
	}
}
```
