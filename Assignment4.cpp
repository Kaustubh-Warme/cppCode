#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
	int source, destination, weight;
};

bool compareEdge(Edge a, Edge b)
{
	return a.weight<b.weight;
}

class DisjointSets
{
	private:
	vector<int> parent, rank;
	
	public:
	DisjointSets(int n)
	{
		parent.resize(n);
		rank.resize(n, 0);
		
		for(int i =0; i<n ; ++i)
			parent[i] = i;
	}
	
	
	int find(int u)
	{
		if(parent[u]!=u)
			parent[u] = find(parent[u]);
		
		return parent[u];
	}
	
	
	
	void unionSets(int u, int v)
	{
		int rootU = find(u);
		int rootV = find(v);
		
		if(rootU!=rootV)
		{
			if(rank[rootU] > rank[rootV])
				parent[rootV] = rootU;
			else if(rank[rootU] < rank[rootV])
				parent[rootU] = rootV;
			else
			{
				parent[rootV] = rootU;
				rank[rootU]++;
			}
		}
	}
};



//kruskals algorithm
vector<Edge> kruskalMST(vector<Edge>& edges, int V)
{
	sort(edges.begin(), edges.end(), compareEdge);
	
	DisjointSets ds(V);
	
	vector<Edge> mst;
	int mstWeight = 0;
	
	for(Edge& edge: edges)
	{
		int u = edge.source;
		int v = edge.destination;
		
		
		if(ds.find(u) != ds.find(v))
		{
			mst.push_back(edge);
			mstWeight += edge.weight;
			
			ds.unionSets(u, v);
			
			if(mst.size() == V-1)
				break;
		}
	}
	
	cout << "\n\nTotal weight of MST: " << mstWeight << endl;
	return mst;
}


int main()
{
	int V = 5;
	int E = 7;
	
	vector<Edge> edges = {
		{0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 5}, {1, 2, 15}, {2, 3, 4}, {1, 2, 8}, {2, 4, 12}
	};
	
	vector<Edge> mst = kruskalMST(edges, V);
	
	cout << "\nEdges in the Minimum Spanning Tree: " << endl;
	
	for(const Edge& edge: mst)
	{
		cout << edge.source << "--" << edge.destination << "--" << edge.weight << endl;
	}
	
	cout << endl;
	return 0;
}