///////////////////////////////////////////////////////////////////////////////
// Title:            program_4
// Files:            Source.cpp , graph.h , distance.h , csv.h , adjacency.txt
//					 cities.csv, city.out
// Semester:         3013 Algorithms Spring 2018
//
// Author:           Jakob Lopez
// Email:            thejakoblopez@gmail.com
// Description:
//       This program loads vertices into a graph with no edges and connects them
//	 to their closest,unvisited,unconnected neighbor. No vertex has a degree 
//	 higher than the max degree defined. After the graph has been connected,
//	 its information is displayed so we can compare the different starting
//	 cities.
/////////////////////////////////////////////////////////////////////////////////

#include<iostream>
#include<fstream>
#include<string>
#include"graph.h"
#include "distance.h"
#include "csv.h"
using namespace std;



void closeFiles(ifstream&,ofstream&);
vertex* connectClosestVertex(graph*&, vertex*&, int);
void displayGraphInfo(graph*&, ofstream&,string,string);
vertex* getStartingCity(graph*&, string);
void loadGraphCSV(graph*&,string, string, int);
void openFiles(ifstream&,ofstream&);


int main()
{
	srand(984325);

	//variables
	vector<vertex *>::iterator vit;
	vector<edge>::iterator eit;
	map<string, string>::iterator it;
	vertex *v, *closest, *start;
	int max_vertices = 6000;
	int max_edges = 0;
	int max_degree;
	int numGraphs;
	string city, state;
	string adjState, line;
	string filename;

	//opens files
	ifstream infile;
	ofstream ofile;
	openFiles(infile,ofile);
	


	cout << "Enter name of cities file" << endl;
	cin >> filename;

	cout << "How many graphs would you like to make?" << endl;
	cin >> numGraphs;

	cout << "Enter max degree for any vertex in graph" << endl;
	cin >> max_degree;

	for (int count = 0; count < numGraphs; count++)
	{
		
		cout << "In which state would you like to start? Use abbreviations (eg. FL,TX,AL...)" << endl;
		cin >> state;


		graph *G = new graph();

		bool done = false;

		//loops through adjacency file until adjacent states are found
		while (!infile.eof() && !done)
		{
			//gets line by line
			getline(infile, line);

			istringstream fin(line);

			//reads first state of line
			fin >> adjState;

			//if first state is equal to starting state
			if (state == adjState)
			{
				//Loads graph with vertices and no edges
				loadGraphCSV(G, filename, adjState, max_vertices);

				//reads rest of adjacenct states and adds them to graph 
				while (fin >> adjState)
				{
					if (adjState != ",")
						loadGraphCSV(G, filename , adjState, max_vertices);
				}
				//we have finished reading in adjacent states and can now 
				//terminate loop
				done = true;
			}
		}
				
		//ignores new line character in order to getline
		cin.ignore();
		cout << "Enter name of starting city" << endl;
		getline(cin, city);
		
		start = getStartingCity(G, city);

		//If city was not found re-prompt user until city is found
		while (!start)
		{
	
			getline(cin, city);

			start = getStartingCity(G, city);
		}


		//connects vertex to closest vertex max degree - 1 times
		//every iteration will give a max degree of iteration + 1
		for (int m = 0; m < (max_degree - 1); m++)
		{
			//Assign starting city
			vit = G->vertexList.begin();
			v = start;

			//connects vertices to their closest neighbor
			for (int j = 0; j < max_vertices; j++)
			{

				int w = G->vertexList[v->ID]->E.size();

				//if vertex degree is greater than or equal to max degree
				if (w >= max_degree)
				{
					//sets iterator to first vertex in list
					vit = G->vertexList.begin();

					//degree of iterator
					w = G->vertexList[(*vit)->ID]->E.size();

					//Loops through to list to find vertex with:
					//degree smaller than max degree
					//is not visited already
					//is not equal to end of list vertex
					while ((w >= max_degree || (*vit)->getStatus()) && vit != G->vertexList.end() - 1)
					{
						vit++;

						w = G->vertexList[(*vit)->ID]->E.size();
					}
					//assigns v to qualifiable vertex
					v = *vit;
				}
				//If iterator was able to find a qualifiable vertex
				if (vit == G->vertexList.end())
				{
					break;
				}
				else
				{
					//connects v to closest vertex and return vertex
					closest = connectClosestVertex(G, v, max_degree);
					if (!closest)
						break;

					//assigns v to closest vertex
					v = closest;
				}
			}
			//resets all visited status to false
			G->resetStatus();
		}
		displayGraphInfo(G, ofile, state, city);

		//returns file reader to beginning of file
		infile.clear();
		infile.seekg(0, ios::beg);
	}

	closeFiles(infile,ofile);
	system("pause");
	return 0;
}

/**
* @FunctionName: closeFiles
{
* @Description:
*    closes file
* @Params:
*    ifstream& infile - allows to read from file
*    ofstream& ofile - allows to write to file
* @Returns:
*    none
*/
void closeFiles(ifstream& infile,ofstream& ofile)
{
	infile.close();
	ofile.close();
}

/**
* @FunctionName: connectClosestVertex
* @Description:
*    connects given vertex to next closest vertex
* @Params:
*    graph &g - address of a graph
*	 vertex *&v - address to a vertex pointer
*	 int maxdegree - max degree any vertex can have
* @Returns:
*    vertex* - closest vertex to v
*/
vertex* connectClosestVertex(graph *&G, vertex *&v, int maxdegree)
{
	vector<vertex *>::iterator vit;
	vector<edge>::iterator eit;
	double x, y, d, closest;
	vertex * closestV;

	//sets iterator to beginning of vector
	vit = G->vertexList.begin();

	//gets latitude and longitude of first element in vector
	x = (*vit)->getLat();
	y = (*vit)->getLon();
	closest = distanceEarth(v->getLat(), v->getLon(), x, y);
	closestV = *vit;

	//If v is the starting vertex, move to next element in vector
	while ((closest == 0 || closestV->getStatus() || closestV->E.size() >= maxdegree) && vit != G->vertexList.end() - 1)
	{
		vit++;
		x = (*vit)->getLat();
		y = (*vit)->getLon();
		closest = distanceEarth(v->getLat(), v->getLon(), x, y);
		closestV = *vit;
	}
	if (vit == G->vertexList.end() - 1)
	{
		return nullptr;
	}
	//Iterates through vector
	while (vit != G->vertexList.end())
	{
		//gets latitude and longitude of current element in vector
		x = (*vit)->getLat();
		y = (*vit)->getLon();

		d = distanceEarth(v->getLat(), v->getLon(), x, y);

		//if current vertex is not same given vertex
		if (d != 0)
		{
			//degree of vertex
			int degree = G->vertexList[(*vit)->ID]->E.size();

			int fID = v->ID;
			int tID = (*vit)->ID;

			//if new distance is closer than closest vertex
			//AND if not already visited
			//AND if has a degree less than maxdegree
			//AND if edge doesn't already exist between two vertices
			if (d < closest && !(*vit)->getStatus() && degree < maxdegree && !G->hasEdge(fID, tID))
			{
				closest = d;
				closestV = *vit;
			}
		}
		vit++;
	}

	//if closest is not visited, add edge and add weight to sum
	if (!closestV->getStatus())
	{
		G->addEdge(v->ID, closestV->ID, closest, false);
		G->sumWeight(closest);
	}

	//mark starting vertex as visited
	v->setStatus(true);

	return closestV;
}

/**
* @FunctionName: displayGraphInfo
* @Description:
*    displays info of graph and outputs starting city,state
* @Params:
*    graph &g - address of a graph
*	 ofstream& ofile -allows to write to file
*	 string s - state
*	 string c - city
* @Returns:
*    none
*/
void displayGraphInfo(graph *&G, ofstream& ofile,string s,string c)
{
	ofile << c << "," << s << endl;
	ofile << G->getTotalWeight() << " miles \t" << G->getNumEdges() << " edges" << endl;
	
	//Print graph if its of Puerto Rico
	if (s == "PR")
		cout << G->graphViz(false) << endl;

	ofile << endl;
}

/**
* @FunctionName: getStartingCity
* @Description:
*    Checks if city is in graph.
*	 If it is, pointer to that city is returned
* @Params:
*    graph &g - address of a graph
*	 string city - city to be searched for
* @Returns:
*    vertex* - pointer to city we searched
*/
vertex* getStartingCity(graph *&G, string city)
{
	vector<vertex *>::iterator vit;

	if (G->cityLookup.find(city) == G->cityLookup.end())
	{
		cout << "City not found. Try again." << endl;
		return nullptr;
	}

	for (vit = G->vertexList.begin(); vit != G->vertexList.end(); vit++)
	{
		if (city == (*vit)->city)
		{

			return *vit;
		}
	}
}

/**
* loadGraphCSV - loads a graph with the given csv
* Params:
*     graph &g - address of a graph
*     string cityFile  - filename to open
*     string adjState  - state that will be added to graph
*     int max  - max degree, default to 0
* Returns
*     graph
*/
void loadGraphCSV(graph *&G,string cityFile, string adjState, int max = 0)
{
	int zip;
	double lat;
	double lon;
	string city;
	string state;
	string county;


	strMapInt cityCheck;

	int i = 0;

	ifstream file(cityFile);
	for (CSVIterator loop(file); loop != CSVIterator(); ++loop)
	{
		zip = stoi((*loop)[0]);
		if ((*loop)[1].length() > 0)
		{
			lat = stod((*loop)[1]);
		}
		else
		{
			lat = 0.0;
		}

		if ((*loop)[2].length() > 0)
		{
			lon = stod((*loop)[2]);
		}
		else
		{
			lon = 0.0;
		}

		city = (*loop)[3];
		state = (*loop)[4];
		county = (*loop)[5];

		if (adjState == state)
		{
			if (cityCheck.find(city) == cityCheck.end())
			{
				// Add the city as a key to the map.
				cityCheck[city] = 0;

				G->addVertex(city, state, lat, lon);

				i++;
			}

			if (i > max && max != 0) {
				return;
			}
		}
	}

	return;
}

/**
* @FunctionName: openFiles
* @Description:
*    opens file
* @Params:
*    ifstream& infile - allows to read from file
*    ofstream& 0file - allows to write to file
* @Returns:
*    none
*/
void openFiles(ifstream& infile,ofstream &ofile)
{
	string filename;

	cout << "Enter name of adjacent states file" << endl;
	cin >> filename;
	infile.open(filename);

	cout << "Enter name of output file" << endl;
	cin >> filename;
	ofile.open(filename);
}
