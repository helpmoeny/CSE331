#ifndef Weightedgraph_H
#define Weightedgraph_H

#include<list>
#include<vector>
#include<string>
#include <unordered_map>

using namespace std;

class WeightedDigraph {
public:
	WeightedDigraph(const string& filename, const int source, const int dest);
	~WeightedDigraph();
	
	WeightedDigraph(const WeightedDigraph&) = delete;
	WeightedDigraph& operator=(const WeightedDigraph&) = delete;
	
	//int GetOrder() const { return numVertices; };//number of points with connections
	//int GetSize() const { return numArcs; };//number of lines in file
	
	double GetPathWeight(const std::list<int> & path) const;
	
	bool DoesPathExist(int from, int to) const;
	bool IsPathValid(const std::list<int> & path) const;
	
	std::list<int> FindMinimumWeightedPath(int from, int to) const;
	
private:
	int numVertices;
	int numArcs;

	vector<std::unordered_map<int, double> > pathMaps;
	unordered_map<int, double> emptyMap;
	vector<std::vector<bool> > boolMatrix;
	vector<bool> boolVec; 
	
	void InsertArc(int from, int to, double weight);
};


#endif