#include "WeightedGraph.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <sstream>
#include <limits>
#include <unordered_map>
#include <string>
#include <list>

using namespace std;

/**
 * Constructs the digraph from a file.
 * You may add any additional construction to this section.
 */
WeightedDigraph::WeightedDigraph(const string& filename, const int source, const int dest) : numVertices(0), numArcs(0) {
	
	//another way to loop through the file and do something
	/* for(string line; getline(in,line);){
		istringstream iss(line);
		int a, b;
		float weight;
		iss >> a >> b >> weight;
		cout<<"a: "<<a<<" "<<"b: "<<b<<" "<<"weight: "<<weight<<endl;
		//cout<<line<<endl;	//print subsequent
	} */
	
	string line;
	//cout<<source<<" "<<dest<<endl;
	ifstream in(filename);
	if(!in.is_open()) {
		cerr << "cannot open file!" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	while(getline(in,line)) {
		istringstream iss(line);
		int a, b;
		float weight;
		iss >> a >> b >> weight;
		cout<<"a: "<<a<<" "<<"b: "<<b<<" "<<"weight: "<<weight<<endl;
		//cout<<line<<endl;	//print subsequent
		
	}
	
  // Data structures for constructing bool matrix

  // Iterate through length of list, insert "false" into vector of bools
  // that signal whether or not path is visited
  /* for (auto itr = 0; itr != numVertices; itr++)
  {
    boolVec.push_back(0);
  }

  // Iterate through length and insert "false" lists into matrix
  for (auto itr = 0; itr != numVertices; itr++)
  {
    boolMatrix.push_back(boolVec);
  }
  // Iterate through length and insert "false" lists into matrix
  for (auto itr = 0; itr != numVertices; itr++)
  {
    pathMaps.push_back(emptyMap);
  } */
  
}

/**
 * Destructor
 * You can do any needed cleanup here.
 */
WeightedDigraph::~WeightedDigraph() {
  // Intentionally left empty
  // You may do any needed cleanup here
}

/**
 * Inserts a weighted arc into the digraph.
 * This is the sole mutator of this class and it is private
 * so the digraph is immutable once created.
 */
void WeightedDigraph::InsertArc(int from, int to, double weight) {
  boolMatrix[from][to] = 1;      
  std::pair<int, double> weightedPath (to, weight);
  pathMaps[from].insert (weightedPath);

  numArcs++;
}


/**
 * Finds the sum weight of the given path.
 * Returns infinity if the path is broken.
 */
double WeightedDigraph::GetPathWeight(const list<int> & path) const {
  double cumWeight = 0;
  if (! IsPathValid(path))
    return numeric_limits<double>::infinity();
  else
  {
    auto elem = path.begin();
    int prev = *elem;
    elem++;
    for (; elem != path.end(); elem++)
    {
      double weight = pathMaps[prev].find(*elem)->second; 
      cumWeight += weight;
      prev = * elem;
    }
    return cumWeight;
  }
}


/**
 * Determines whether a path between the two vertices exists.
 */
bool WeightedDigraph::DoesPathExist(int from, int to) const {
  bool *visited = new bool[numVertices];
  int head = from, tail = to;
  std::unordered_map<int, double> availablePaths = pathMaps[head];

  //You can use either DFS or BFS approach
  int startNode = from;

  for(auto i = 0; i != numVertices; i++)
  {
    visited[i] = false;
  }

  // Queue for list
  std::list<int> queue;

  // Visit start and add it to queue
  visited[startNode] = true;
  queue.push_back(startNode);

  while ( ! queue.empty() )
  {
    // Dequeue a vertex and print it
    startNode = queue.front();
    queue.pop_front();

    for(auto iter = pathMaps[startNode].begin(); iter != pathMaps[startNode].end(); ++iter)
    {
      auto found = pathMaps[from].find(to); 
      if (found != pathMaps[from].end())
      {
        cout << endl << "1" << endl;
        return true;
      }

      // These are connected, but there is not a valid path
      else if (from == to)
      { 
        cout << endl << "2" << endl;
        return false;
      }

      else if (pathMaps[from].size() == 0)
      {
        cout << endl << "3" << endl;
        return false;
      }
      else if (! visited[iter->first])
      {
        if (iter->first == to)
          return true;
        visited[iter->first] = true;
        queue.push_back(iter->first);
      }
      // if the node has already been visited, end the search 
    }
  }
  return false;
}


/**
 * Checks whether the given path goes over existing arcs.
 */
bool WeightedDigraph::IsPathValid(const list<int> & path) const {
  auto i = path.begin();
  int prev = *i;
  i++;
  for ( ; i != path.end(); i++)
  {
    if (pathMaps[*i].size() == 0)
    {
      if (*i == *path.end())
        return true;
      else
        return false;
    }
    else
    {
      auto found = pathMaps[prev].find(*i); 
      if (found ==  pathMaps[prev].end() )
      {
        return false;
      }
    }
    prev = *i;
  }
  return true;
}


/**
 * Finds a path of minimum weight between the two nodes.
 * The behavior is undefined if no such path exists
 * (you may assume that such a path does exist).
 */
list<int> WeightedDigraph::FindMinimumWeightedPath(int from, int to) const {
  vector<int> previous;
  std::list<int> path;
  vector<double> minDistance;

  const double maxWeight = std::numeric_limits<double>::infinity();
  minDistance.clear();
  minDistance.resize(numVertices, maxWeight);
  minDistance[from] = 0;
  previous.clear();
  previous.resize(numVertices, -1);

  std::set<std::pair<int, double> > vertexQueue;
  vertexQueue.insert(std::make_pair(from, minDistance[from]));

  if (from == to)
  {
    path.push_front(from);
    return path;
  }

  while (! vertexQueue.empty() )
  {
    auto distance = vertexQueue.begin()->second;
    auto u = vertexQueue.begin()->first;
    vertexQueue.erase(vertexQueue.begin());
    auto neighbors = pathMaps[u];
    for ( auto i = neighbors.begin(); i != neighbors.end(); i++)
    {
      auto v = i->first;
      auto weight = i->second;
      auto distanceThroughU = distance + weight;
      if (distanceThroughU < minDistance[v])
      {
        vertexQueue.erase(std::make_pair(v, minDistance[v]));
        minDistance[v] = distanceThroughU;
        previous[v] = u;
        vertexQueue.insert(std::make_pair(v, minDistance[v]));
      }
    }
  }
  
  auto vertex = to;
  path.push_front(to);
  bool foundPath = false;
  while (! foundPath)
  {
    vertex = previous[vertex];
    path.push_front(vertex);
    if (vertex == from)
      foundPath = true;
  }
  
  return path;
}