#ifndef Weightedgraph_H
#define Weightedgraph_H

#include <utility>
#include<list>
#include<vector>
#include<string>
#include <unordered_map>
#include <map>
#include <queue>

using namespace std;

class vertex{
	private:
		int number;
		pair<int,float> arc;
	public:
		friend class weightedgraph;
		
		vertex(int n, pair<int,float> EdgeArr){	//constructor
			number = n;
			arc=EdgeArr;
		}
		~vertex(){	//destructor
		}
};

class weightedgraph {
public:
	weightedgraph(const string& filename, const int source, const int dest);
	~weightedgraph();
	
	weightedgraph(const weightedgraph&) = delete;
	weightedgraph& operator=(const weightedgraph&) = delete;
	
	list<int> FindMinimumWeightedPath(int from, int to) const;
	
private:
	vector<pair<int,float>> list;
	vector<float> weights;
	//vector<vertex> graph;
};


#endif