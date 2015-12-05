/**
 * 
 * 
 */

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

int main(int argc, char* argv[])
{

	if(argc != 4 && argc != 3) {
		cerr << "Incorrect number of command line arguments." << endl;
		cerr << "Usage: " << argv[0] << " <filename> <start vertex> <dest vertex>" << endl;
		exit(EXIT_FAILURE);
	}
	
	int source = atoi(argv[2]);
	int dest = atoi(argv[3]);
	cout<<"source: "<<source<<" Dest: "<<dest<<endl;
	
	//cout<<argv[1]<<endl;	//print name of file
	weightedgraph graph(argv[1], source, dest);
	
	/* if (graph.DoesPathExist(source, dest)) {		//do a check for instead, if returned path from graph.FindMinimumWeightedPath contains nothing...
		cout << "Path from " << source << " to " << dest << ":" << endl;
		
		list<int> path = graph.FindMinimumWeightedPath(source, dest);
		
		if (!graph.IsPathValid(path)) {			//again maybe just do a check for path returning nothing/empty...
			cerr << "NO PATH FOUND" << endl;
			return 0;
		}
		
		bool isStart = true;
		for (int v : path) {
			if (!isStart) cout << " -> ";
			cout << v;
			isStart = false;
		}
		cout << endl;
	} 
	else {
		cout << "No path from " << source << " to " << dest << " exists!" << endl;		//"NO PATH FOUND"
	} */

	return 0;
}