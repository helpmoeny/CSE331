// A C++ program to determine whether a graph is bipartite
//
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "graph.h"
using namespace std;
 
int main(int argc, char* argv[])
{
    if (argc != 2) 
    {
        cerr << "Incorrect nubmer of command line arguments." << endl;
        cerr << "Usage: "<< argv[0] << " <an input file>" << endl;
        return EXIT_FAILURE;
    }

    // read data from an input file
    ifstream inf(argv[1]);
    if (!inf.is_open()) 
    {
        // check if the file can be opened
        cerr << "Error: cannot open an input file \"" << argv[1] << "\"." << endl;
        return EXIT_FAILURE;
    }

    // read data from file and store in a graph
    Graph graph(argv[1]);
    
    // determine whether an input graph is biparite
    cout << graph.isBipartitePrintTraversePath(0) << endl;
	if(graph.isBipartitePrintTraversePath(0)){
		cout<< "True" <<endl;
	}
	else{	//(1)
		cout<< "False" <<endl;
	}
	return true;
}
