/*
 Class Graph is a mockup class, thus you must not assume that this is a completed implementation. 
 Please add codes/comments to complete this class and where you think there is a need.
*/
#include <string>
#include <list>
#include <vector>
#include <map>
#include <queue>
#include <deque>
#include <iostream>
using namespace std;

class Graph
{
private:
	//vector<list<int> > adjList;
    //list<int> *adj = new list<int>[adjList.size()];
public:
	//UnweightedGraph(const string& t);
    //void DisplayInfo() const;
	vector<int> connections;
	deque<int,vector> graph;
	
	Graph(char* filename) {
		/* ifstream in(t);
		if(!in.is_open()) {
			cerr << "cannot open file!" << std::endl;
			exit(EXIT_FAILURE);
		}
		string line;
		while(getline(in,line)) {
			istringstream iss(line);
			int v;
			list<int> list_temp;
			while( iss >> v) {
			list_temp.push_back(v);
			}
			adjList.push_back(list_temp);
		} */
	}

	~Graph() { 
	} 

	// function to determine whether a graph is bipartite
	// start traverse a graph from node u
	// return true if a graph is bipartite. Otherwise, return false
	bool isBipartitePrintTraversePath(int u);
};

//https://github.com/danialgoodwin/dev/blob/master/algorithms-and-data-structures/graphs.md
//http://www.geeksforgeeks.org/bipartite-graph/
// function to determine whether a graph is bipartite
// start traverse a graph from node u
// return true if a graph is bipartite. Otherwise, return false
bool Graph::isBipartitePrintTraversePath(int u) {
	// add you code here
	
	// Create a color array to store colors assigned to all veritces. Vertex 
    // number is used as index in this array. The value '-1' of  colorArr[i] 
    // is used to indicate that no color is assigned to vertex 'i'.  The value 
    // 1 is used to indicate first color is assigned and value 0 indicates 
    // second color is assigned.
    int colorArr[graph.size];
    for (int i = 0; i < graph.size(); ++i){
		colorArr[i] = -1;
	}
 
    // Assign first color to source
    if(colorArr[u] % 2){	//x is odd
		colorArr[u] = "BLACK";
	}
	else{	//x is even
		colorArr[u] = "WHTIE";
	}
 
    // Create a queue (FIFO) of vertex numbers and enqueue source vertex
    // for BFS traversal
    queue <int> q;
    q.push(u);
 
    // Run while there are vertices in queue (Similar to BFS)
    while (!q.empty())
    {
        // Dequeue a vertex from queue
        int e = q.front();//access next element
        q.pop();//remove next element
 
         // Find all non-colored adjacent vertices
        for (int v = 0; v < V; ++v)
        {
            // An edge from e to v exists and destination v is not colored
            if (G[e][v] && colorArr[v] == -1)
            {
                // Assign alternate color to this adjacent v of e
                colorArr[v] = 1 - colorArr[e];
                q.push(v);
            }
 
            //  An edge from e to v exists and destination v is colored with
            // same color as e
            else if (G[e][v] && colorArr[v] == colorArr[e])
                return false;
        }
    }
 
    // If we reach here, then all adjacent vertices can be colored with 
    // alternate color
    return true;
}
