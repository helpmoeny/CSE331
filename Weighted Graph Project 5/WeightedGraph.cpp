#include "WeightedGraph.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <sstream>
#include <limits>
#include <unordered_map>
#include <string>
#include <queue>
#include <list>

using namespace std;

/**
 * Constructs the digraph from a file.
 * You may add any additional construction to this section.
 */
weightedgraph::weightedgraph(const string& filename, const int source, const int dest){
	
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
	
	int lines=0;
	while(getline(in,line)) {
		istringstream iss(line);
		int a, b;
		float weight;
		iss >> a >> b >> weight;
		//cout<<"a: "<<a<<" "<<"b: "<<b<<" "<<"weight: "<<weight<<endl;
		
		list.push_back(make_pair(a,b));
		weights.push_back(weight);

		//graph[a].push_back(b);	//
		//cout<<graph.size()<<endl;
		//cout<<line<<endl;	//print subsequent line
		lines++;
	}
	
	for(int i=0; i<list.size();i++){
		cout<<"vertex: "<<list[i].first<<" arc: "<<list[i].second<<" weight: "<<weights[i];
		cout<<endl;
	}
	//cout<<"lines: "<<lines<<endl;
	list<int> weightedgraph::FindMinimumWeightedPath(source, dest);
}

/**
 * Destructor
 */
weightedgraph::~weightedgraph() {

}

/**
 * Finds a path of minimum weight between the two nodes
 */
/* list<int> WeightedDigraph::FindMinimumWeightedPath(int from, int to) const {	//const??
	
	
} */


/**
 * Finds a path of minimum weight between the two nodes.
 * The behavior is undefined if no such path exists
 * (you may assume that such a path does exist).
 */
list<int> weightedgraph::FindMinimumWeightedPath(int from, int to) const {
  vector<int> previous;
  std::list<int> path;
  vector<double> minDistance;
  int numVertices=7;
  
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
    auto neighbors = list[u].second;
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