#include "WeightedGraph.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <sstream>
#include <limits>	//need for infinity
#include <string>
#include <queue>
#include <list>

using namespace std;

weightedgraph::weightedgraph(const string& file, const int source, const int dest){
	
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
	ifstream in(file);
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
		
		graph.push_back(make_pair(a,b));
		weights.push_back(weight);

		//graph[a].push_back(b);	//
		//cout<<graph.size()<<endl;
		//cout<<line<<endl;	//print subsequent line
		lines++;
	}
	
	for(int i=0; i<graph.size();i++){
		cout<<"vertex: "<<graph[i].first<<" arc: "<<graph[i].second<<" weight: "<<weights[i];
		cout<<endl;
	}
	//cout<<"lines: "<<lines<<endl;

}

//Destructor
weightedgraph::~weightedgraph() {
	//empty
}

/**
 * Finds a path of minimum weight between source and dest
 * If there is no path it returns up empty
 */
/* list<int> weightedgraph::findpath(int source, int dest) const {	//const??
  vector<int> previous;
  list<int> path;
  vector<float> minDistance;
  int vertices=7;
  
  if (source == dest)
  {
    path.push_back(source);
    return path;
  }
  
  const float maxWeight = numeric_limits<float>::infinity();
  minDistance.clear();
  minDistance.resize(vertices, maxWeight);
  minDistance[source] = 0;
  previous.clear();
  previous.resize(vertices, -1);

  set<pair<int, float>> vertexQueue;
  vertexQueue.insert(make_pair(source, minDistance[source]));

  while (! vertexQueue.empty() )
  {
    auto distance = vertexQueue.begin()->second;
    auto u = vertexQueue.begin()->first;
    vertexQueue.erase(vertexQueue.begin());
    auto neighbors = graph[u].second;
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
  
  auto vertex = dest;
  path.push_front(dest);
  bool foundPath = false;
  while (! foundPath)
  {
    vertex = previous[vertex];
    path.push_front(vertex);
    if (vertex == source)
      foundPath = true;
  }
  
  return path;
} */