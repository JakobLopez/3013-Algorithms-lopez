//graph.h
// A simple representation of graph using STL

#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Might use as a lookup from city name to ID.
// And to filter duplicate cities.
typedef map<string, int> strMapInt;
typedef map<int, int> intint;

//represents latitude and longitude of a vertex
struct latlon
{
	double lat;
	double lon;

	//default constructor
	latlon()
	{
		lat = 0.0;
		lon = 0.0;
	}

	//parameterized constructor
	latlon(double y, double x)
	{
		lat = y;
		lon = x;
	}

	/**
	* operator= - overload assignment for latlon
	* Params:
	*     const latlon ll     - lat lon to assign
	* Returns
	*     reference to assignment for chaining (e.g. a = b = c )
	*/
	latlon& operator=(const latlon &ll)
	{
		// do the copy
		lat = ll.lat;
		lon = ll.lon;

		// return the existing object so we can chain this operator
		return *this;
	}

	/**
	* operator<< - overload cout for latlon
	* Params:
	*     const latlon ll     - lat lon to print
	* Returns
	*     formatted output for a latlon
	*/
	friend ostream &operator<<(ostream &output, const latlon &ll)
	{
		output << "(" << ll.lat << "," << ll.lon << ")";
		return output;
	}
};

/**
* edge - represents the edge of a graph.
*/
struct edge
{
	int toID;      // id of vertex edge is going to
	double weight; // weight of edge if any
	bool used;     // was edge used in some traversal

	//parameterized constructor
	edge(int id,double w)
	{
		toID = id;
		weight = w;
		used = false;
	}

	/**
	* operator<< - overload cout for edge
	* Params:
	*     const edge e     - edge to print
	* Returns
	*     formatted output for an edge
	*/
	friend ostream &operator<<(ostream &output, const edge &e)
	{
		output << "(To:" << e.toID << " W: " << e.weight << " U: " << e.used << ")";
		return output;
	}
};

/**
* vertex - represents a vertex in a graph.
*/
struct vertex
{
	int ID;
	string city;
	string state;
	latlon loc;
	vector<edge> E;
	int degree;
	bool visited;

	/**
	* vertex
	* Description:
	*	  parameterized constructor
	* Params:
	*     int id - ID of vertex
	*     string c - city of vertex
	*     string s - state of vertex
	*     latlon ll - latitude and longitude
	* Returns
	*     none
	*/
	vertex(int id, string c, string s, latlon ll = latlon())
	{
		ID = id;
		city = c;
		state = s;
		loc = ll;
		visited = false;
		degree = 0;
	}

	//returns degree of vertex
	//return degree of vertex
	int getDegree()
	{
		return degree;
	}

	//returns latitude
	double getLat()
	{
		return loc.lat;
	}

	//returns longitude
	double getLon()
	{
		return loc.lon;
	}


	//changes visit status
	void setStatus(bool flag)
	{
		visited = flag;
	}

	//returns visited status
	bool getStatus()
	{
		return visited;
	}

	/**
	* operator<< - overload cout for vertex
	* Params:
	*     const vertex v     - vertex to print
	* Returns
	*     formatted output for a vertex
	*/
	friend ostream &operator<<(ostream &output, const vertex &v)
	{
		output << "(ID:" << v.ID << " C: " << v.city << " S: " << v.state << " L: " << v.loc << " Edges:" << v.E.size() << ")";
		return output;
	}
};

/**
* graph - set of vertices and edges
*
* Methods (private):
*     vertex* createVertex(string city,string state)
* Methods (public):
*     graph()
*/
class graph
{
public:
	int id;                      // id counter for new vertices
	int num_edges;               // edge count
	int totalWeight;
	vector<vertex *> vertexList; // vector to hold vertices
	strMapInt cityLookup;


	/**
	* private: createVertex - returns a new vertex with unique id.
	* Params:
	*     string city
	*     string state
	*	  latlon ll
	*/
	vertex* createVertex(string city, string state, latlon ll)
	{
		return new vertex(id++, city, state, ll);
	}

	/**
	* graph - constructor
	*/
	graph()
	{
		id = 0;
		num_edges = 0;
		totalWeight = 0;
	}

	//copy constructor
	graph(const graph &G)
	{
		id = G.id;
		num_edges = 0;
		vertexList = G.vertexList;
		cityLookup = G.cityLookup;
		totalWeight = G.totalWeight;
	}

	//prints map of cityLookup
	void printmap()
	{
		map<string, int>::iterator it;

		for (it = cityLookup.begin(); it != cityLookup.end(); it++)
		{
			string key = it->first;        // first = array index 
			int value = it->second;     // second = array value pointed to by index
			cout << key << "->" << value << endl;
		}
	}

	/**
	* addVertex - adds a vertex to the graph
	* Params:
	*     string   city     - name of city
	*     string   state    - two letter abbr of state
	*     double   lat      - latitude
	*     double   lon      - longitude
	* Returns
	*     void
	*/
	int addVertex(string city, string state, double lat = 0.0, double lon = 0.0)
	{
		if (cityLookup.find(city) == cityLookup.end())
		{
			// Add the city as a key to the map.
			cityLookup[city] = 0;
		}
		else
		{
			return -1;
		}

		vertex *temp = createVertex(city, state, latlon(lat, lon));
		vertexList.push_back(temp);

		//update the value that city points to.
		cityLookup[city] = temp->ID;
		return temp->ID;
	}

	/**
	* addEdge - adds a relationship between two vertices to the graph
	* Params:
	*     int      fromID   - the ID of the vertex in which the edge is leaving
	*     int      toID     - ID of the receiving vertex
	*     double   weight   - weight of the edge if any
	*     bool     directed - is the edge directed or not
	* Returns
	*     void
	*/
	void addEdge(int fromID, int toID, double weight = 0, bool directed = false)
	{
		edge e1(toID, weight);
		vertexList[fromID]->E.push_back(e1);
		num_edges++;

		//cout<<"adding "<<fromID<<" to "<<toID<<endl;

		if (!directed)
		{
			edge e2(fromID, weight);
			vertexList[toID]->E.push_back(e2);

			//cout<<"adding "<<toID<<" to "<<fromID<<endl;

			num_edges++;
		}
	}

	//returns true if edge between 2 vertices
	bool hasEdge(int fromId, int toId)
	{

		vector<edge>::iterator eit;
		eit = vertexList[fromId]->E.begin();

		//loops through vector of edges at index of vertex
		while (eit != vertexList[fromId]->E.end())
		{
			//returns true if edge between vertices
			if (toId == (*eit).toID)
				return true;

			eit++;
		}

		return false;

	}

	//Resets all visited status to false
	void resetStatus()
	{
		vector<vertex *>::iterator vit;
		for (vit = vertexList.begin(); vit != vertexList.end(); vit++)
		{
			(*vit)->setStatus(false);
		}
	}

	//adds weight to weight sum
	void sumWeight(int w)
	{
		totalWeight += w;
	}

	//Returns total weight of all edges
	int getTotalWeight()
	{
		return totalWeight;
	}

	//returns number of edges in graph
	int getNumEdges()
	{
		return num_edges;
	}

	/**
	* printGraph - prints the graph out for debugging purposes
	* Params:
	*     void
	*/
	void printGraph()
	{

		vector<vertex *>::iterator vit;
		vector<edge>::iterator eit;



		for (vit = vertexList.begin(); vit != vertexList.end(); vit++)
		{

			cout << *(*vit) << endl;

			if ((*vit)->E.size() > 0)
			{
				for (eit = (*vit)->E.begin(); eit != (*vit)->E.end(); eit++)
				{
					cout << "\t" << (*eit) << endl;
				}
			}
		}
	}

	void printVids() {
		vector<vertex *>::iterator vit;
		vector<edge>::iterator eit;

		for (vit = vertexList.begin(); vit != vertexList.end(); vit++)
		{
			cout << (*vit)->ID << endl;
		}
	}

	string graphViz(bool directed = true) {
		vector<vertex *>::iterator vit;
		vector<edge>::iterator eit;

		// [label="hi", weight=100];

		string viz = "";
		string labels = "";
		string conns = "";
		int weight = 0;
		string arrow = "";

		if (directed) {
			viz = "digraph G {\n";
			arrow = "->";

		}
		else {
			viz = "graph G {\n";
			arrow = "--";
		}

		for (vit = vertexList.begin(); vit != vertexList.end(); vit++)
		{
			if ((*vit)->E.size() > 0)
			{
				labels += "\t" + to_string((*vit)->ID) + " [label=\"" + (*vit)->city + ", " + (*vit)->state + "\"]\n";

				for (eit = (*vit)->E.begin(); eit != (*vit)->E.end(); eit++)
				{


					labels += "\t" + to_string(eit->toID) + " [label=\"" + vertexList[eit->toID]->city + ", " + vertexList[eit->toID]->state + "\"]\n";

					weight = eit->weight;
					conns += "\t" + to_string((*vit)->ID) + arrow
						+ to_string(eit->toID) + " [weight=" + to_string(weight) + ", label=" + to_string(weight) + "]\n";
				}
			}
		}

		viz += labels;
		viz += conns;
		viz += "}\n";

		return viz;
	}

	/**
	* addEdge - adds a relationship between two vertices to the graph
	* Params:
	*     string   fromCity   - the city of the vertex in which the edge is leaving
	*     string   toCity     - city of the receiving vertex
	*     double   weight     - weight of the edge if any
	*     bool     directed   - is the edge directed or not
	* Returns:
	*     void
	*/
	void addEdge(string fromCity, string toCity, double weight = 0, bool directed = false)
	{
	}


	/**
	* maxID - returns the max id assigned to any vertex
	* Params:
	*     void
	* Returns:
	*     int
	*/
	int maxID()
	{
		return id;
	}

	/**
	* graphSize - returns the number of vertices and edges
	* Params:
	*     void
	* Returns:
	*     int
	*/
	int* graphSize() {
		int* vals = new int[2];
		vals[0] = vertexList.size();
		vals[1] = num_edges;
		return vals;
	}

	/**
	* operator= - overload assignment for Graph
	* Params:
	*     const latlon ll     - lat lon to assign
	* Returns
	*     reference to assignment for chaining (e.g. a = b = c )
	*/
	graph& operator=(const graph &g)
	{
		// do the copy
		vertexList = g.vertexList;
		id = g.id;

		// return the existing object so we can chain this operator
		return *this;
	}



};
