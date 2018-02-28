#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<string>
using namespace std;

//Defines variable for number of words in each file
#define ADJECTIVEMAX 15571
#define NOUNMAX 53737
#define VERBMAX 12018
#define ADVERBMAX 3237
#define ANIMALMAX 235


void closeFiles(ifstream&, ifstream&, ifstream&, ifstream&, ifstream&, fstream&);
string combineRandomWords(string, string, string, string, string);
string generateRandomWords(string*, string*, string*, string*, string*);
void loadArray(ifstream&, string*&);
void openFiles(ifstream&, ifstream&, ifstream&, ifstream&, ifstream&, fstream&);

int main()
{
	// seed random number generator
	srand(8734587);

	// declare stl map
	map<string, string> wl;


	// create an iterator to loop over your <string:string> container
	map<string, string>::iterator it;

	//Declare/define variables
	string *adjWords, *nounWords, *verbWords, *adverbWords, *animalWords;
	string key, word, value;
	string crazyword;
	int i = 0;

	//Opens files to read from and write to
	ifstream adjIn, nounIn, verbIn, adverbIn, animalIn;
	fstream wordFile;
	openFiles(adjIn, nounIn, verbIn, adverbIn, animalIn, wordFile);



	//Initializes arrays
	adjWords = new string[ADJECTIVEMAX];
	nounWords = new string[NOUNMAX];
	verbWords = new string[VERBMAX];
	adverbWords = new string[ADVERBMAX];
	animalWords = new string[ANIMALMAX];


	//Loads array with words
	loadArray(adjIn, adjWords);
	loadArray(nounIn, nounWords);
	loadArray(verbIn, verbWords);
	loadArray(adverbIn, adverbWords);
	loadArray(animalIn, animalWords);

	//Read 10,000 words into stlmap ensuring there are no dups
	while (i < 10000)
	{
		//Generates random word
		crazyword = generateRandomWords(adjWords, nounWords, verbWords, adverbWords, animalWords);

		//Makes sure no repeated words enter map
		if (wl.find(crazyword) == wl.end())
		{
			wl[crazyword] = "word";
			i++;
			wordFile << crazyword << endl;
		}
	}

	//Closes files
	closeFiles(adjIn, nounIn, verbIn, adverbIn, animalIn, wordFile);
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
*    ofstream &wordFile - outfile
* @Returns:
*    void
*/
void closeFiles(ifstream& adjIn, ifstream& nounIn, ifstream& verbIn, ifstream& adverbIn, ifstream& animalIn, fstream& wordFile)
{
	adjIn.close();
	nounIn.close();
	verbIn.close();
	adverbIn.close();
	animalIn.close();
	wordFile.close();
}

/**
* @FunctionName: combineRandomWords
* @Description:
*    Concatenates words and adds a space in between each component.
*	 Checks to see how many word components before adding random spaces together 
* @Params:
*	 ALL DEFAULT TO EMPTY SPACE
*    string lead - 1st component
*    string mid1 - 2nd componente
*    string mid2 - 4th component
*	 string end - 5th component
* @Returns:
*    string - concatenation of words 
*/
string combineRandomWords(string lead = "", string mid1 = "", string mid2 = "", string mid3 = "", string end = "")
{
	//Concatenates first three components
	string crazyWord = lead + " " + mid1 + " " + mid2;

	//Checks if word has all 5 components
	if (end == "")
	{
		//If word is only 3 components long
		if (mid3 == "")
		{
			return crazyWord;
		}
		else
		{
			crazyWord += " " + mid3;
		}
	}
	//If word is 5 components long
	else
	{
		crazyWord += " " + mid3 + " " + end;
	}

	return crazyWord;
}

/**
* @FunctionName: generateRandomWords
* @Description:
*    A random number is generated to determine how long and in what order
*	 the crazy word will be. Another random number is used to choose the 
*	 index of the array to get the random word component
*	 
* @Params:
*	 ALL DEFAULT TO EMPTY SPACE
*    string *adj - pointer to an array of adjectives
*    string *n - pointer to an array of nouns
*    string *v - pointer to an array of verbs
*	 string *adv - pointer to an array of adverbs
*	 string *an - pointer to an array of animals
* @Returns:
*    string - a crazy word
*/
string generateRandomWords(string *adj, string *n, string *v, string *adv, string *an)
{
	string word;

	int comboNumber = rand() % 3;
	int adjIndex = rand() % ADJECTIVEMAX;
	int nIndex = rand() % NOUNMAX;
	int vIndex = rand() % VERBMAX;
	int advIndex = rand() % ADVERBMAX;
	int anIndex = rand() % ANIMALMAX;

	if (comboNumber == 0)
	{
		int randomNum = ADJECTIVEMAX % (adjIndex + 1);
		word = combineRandomWords(adj[adjIndex], adj[randomNum], n[nIndex]);
	}
	else if (comboNumber == 1)
	{
		word = combineRandomWords(adj[adjIndex], an[anIndex], v[vIndex] + "ing", adv[advIndex]);
	}
	else if (comboNumber == 2)
	{
		word = combineRandomWords(adj[adjIndex], n[nIndex], an[anIndex], v[vIndex] + "ing", adv[advIndex]);
	}
	else
	{
		cout << comboNumber << " is not a valid number" << endl;
	}

	return word;
}

/**
* @FunctionName: loadArray
* @Description:
*    Reads words from a file and loads words into an array of strings
* @Params:
*    ifstream &ifile - allows to read from file
*    string *&words - address to an array of strings
* @Returns:
*    void
*/
void loadArray(ifstream &infile, string *&words)
{
	string word;
	int i = 0;

	while (!infile.eof())
	{
		infile >> word;
		words[i] = word;
		i++;
	}

}


/**
* @FunctionName: openFiles
* @Description:
*    opens files
* @Params:
*    ifstream &adjIn - allows to read from adjective file
*    ifstream &nounIn - allows to read from noun file
*    ifstream &verbIn - allows to read from verb file
*    ofstream &wordFile - allows to write/read to file
* @Returns:
*    void
*/
void openFiles(ifstream& adjIn, ifstream& nounIn, ifstream& verbIn, ifstream& adverbIn, ifstream& animalIn, fstream& wordFile)
{
	adjIn.open("adjectives.txt");
	nounIn.open("nouns.txt");
	verbIn.open("verbs.txt");
	adverbIn.open("adverbs.txt");
	animalIn.open("animals.txt");
	wordFile.open("tenthousandwords.txt");
}
