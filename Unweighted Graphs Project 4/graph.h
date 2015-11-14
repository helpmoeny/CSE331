/*
 Class Graph is a mockup class, thus you must not assume that this is a completed implementation. 
 Please add codes/comments to complete this class and where you think there is a need.
	//make -f Makefile.mak
	//g++ -std=c++11 -Wall -o graph.h main.cpp, maybe flip order of files?
	//http://www.geeksforgeeks.org/bipartite-graph/
	//https://github.com/danialgoodwin/dev/blob/master/algorithms-and-data-structures/graphs.md
*/
#include <stdio.h>
#include <string.h>	//string??
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

using namespace std;

class Node{
	private:
		int number;
		string color;
		vector<int> EdgeArr;
	public:
		friend class Graph;
		
		Node(int n){	//constructor
			number = n;
			string color = "";
		}
		~Node(){	//destructor
		}
};
		
class Graph
{
	private:
		vector<Node> adjList;	//<Node<int>>?
	public:
	
		Graph(char* filename) {
			ifstream inf(filename);
			if(!inf.is_open()) {
				cerr << "cannot open file!" << std::endl;
				exit(EXIT_FAILURE);
			}
			int vertex=0;
			while(true) {
				if(!(inf>>vertex)){
					//cout<<"Vertex: "<<vertex<<endl;	//print out vertex
					break;
				}
				int v;
				Node n= Node(vertex); 		//Create my object	//(n(vertex))?
				while(inf.peek() !='\n'){
					int i=0;
					inf>>i;
					//cout<<i<<",";	//print out the edges
					n.EdgeArr.push_back(i);
				}
				//cout<<endl;
				adjList.push_back(n);		//adjList.push_back(v);
			}
		}

		~Graph() { 
		}

	// function to determine whether a graph is bipartite
	// start traverse a graph from node u
	// return true if a graph is bipartite. Otherwise, return false
	bool isBipartitePrintTraversePath(int u);
};


// function to determine whether a graph is bipartite
// start traverse a graph from node u
// return true if a graph is bipartite. Otherwise, return false
bool Graph::isBipartitePrintTraversePath(int u) {
	// add you code here
	
	if(adjList.size() <=2){	//graph is bipartite
		return true;
	}
	
	if(adjList[u].number%2 == 0){	//vertex is even, color it white
		adjList[u].color="White";
		cout<<u<<" White"<<endl;
	}
	else{		//vertex is odd, color it black
		adjList[u].color="Black";
		cout<<u<<" Black"<<endl;
	}
	
	for(int i=u; i<adjList.size(); i++){	//loops 13 times g1.txt because 13 lines/vertex_numbers
		for(int v=0; v<adjList[i].EdgeArr.size(); v++){
			//cout<<"edgeArr[v]: "<<adjList[i].EdgeArr[v]<<endl;
			//cout<<adjList[adjList[i].EdgeArr[v]].number<<endl;
			//cout<<"adjList[v].number: "<<adjList[v].number<<endl;	//same as v
			//cout<<"v: "<<v<<endl;
			
			if(adjList[adjList[i].EdgeArr[v]].color==""){	//it has no color
				if(adjList[i].color == "White"){
					adjList[adjList[i].EdgeArr[v]].color="Black";
					cout<<adjList[adjList[i].EdgeArr[v]].number<<" "<<"Black"<<endl;
				}
				else if(adjList[i].color == "Black"){
					adjList[adjList[i].EdgeArr[v]].color="White";
					cout<<adjList[adjList[i].EdgeArr[v]].number<<" "<<"White"<<endl;
				}
				else{
					//cout<<"Error, adjList[adjList[i].EdgeArr[v]] is neither color?"<<endl;
				}
			}
			else{
				if(adjList[i].color == adjList[adjList[i].EdgeArr[v]].color){
					//cout<<"i:"<<i<<" adjList[i]: "<<adjList[i].color<<" v:"<<v<<" adjList[v]: "<<adjList[v].color<<endl;
					//cout<<"edgeArr: "<<adjList[i].EdgeArr[v]<<endl;	//the adjlist edgearr # that we are at
					cout<<"CONFLICT "<<i<<" "<<adjList[i].EdgeArr[v]<<endl;
					return false;
				}
			}
		}
	}
 
    // If we reach here, then all adjacent vertices can be colored with 
    // alternate color
    return true;
}
