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
	//cout<<"lines: "<<lines<<endl;
	
	cout<<"File Print out:"<<endl;
	for(int i=0; i<graph.size();i++){
		cout<<"vertex: "<<graph[i].first<<" arc: "<<graph[i].second<<" weight: "<<weights[i];
		cout<<endl;
	}
	cout<<endl;
	
}

//Destructor
weightedgraph::~weightedgraph() {
	//empty
}

/**
 * Finds a path of minimum weight between source and dest
 * If there is no path it returns up empty
 */
list<int> weightedgraph::findpath(int source, int dest) const {	//const??
  
  list<int> path;
  //path.push_back(source);
  if (source == dest)
  {
    path.push_back(source);
    return path;
  }
  int element=0;
  for(int j=0; j<graph.size();j++){
		if(graph[j].first == source){
			element=j;
			break;
		}
		else{
			path.clear();
			break;
		}
	}
  //need code to loop through my graph vector of pairs and traverse the least weighted options
  //until destination is reached, then return the path and weight/cost
  
  return path;
}