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
	//need to handle inputs such as >prog g1.txt 03 ->segfault
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
	
	list<int> path= graph.findpath(source,dest);
	if(path.empty()==true){
		cout<<"PATH NOT FOUND"<<endl;
	}

	
	return 0;
}