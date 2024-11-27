#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

//define edge
struct Edge
{
	int destination, weight;
	
	Edge(int d, int w): destination(d), weight(w) {};
};

//define compare class with operator function
struct compare
{	
	bool operator() (const pair<int, int> & a, const pair<int, int> &b)
	{
		return a.second > b.second;
	}
};

//define main dijkstras function
//takes source, destination, adjacency list
vector<int> dijkstra(int source, int destination, vector<vector<Edge>> & graph)
{	
	//number of vertices
	int vertices = graph.size();
	
	//list for distance and parents
	vector<int> distance(vertices, INT_MAX);
	vector<int> parent(vertices, -1);
	
	//priority queue for minimumedge weight
	priority_queue<pair<int, int>, vector<pair<int, int>>, compare> pq;
	
	//initial distance of source
	distance[source] = 0;
	
	//push into pq
	pq.push({source, 0});
	
	//while pq is not empty
	while(!pq.empty())
	{
		//take out the top
		int node = pq.top().first;	//destination
		int currentDistance = pq.top().second; //weight
		
		//pop the top
		pq.pop();
		
		//if source is destination then break
		if (node == destination)
			break;
		
		
		//for every corresponding edge for top node in adjacency list
		for (Edge & edge: graph[node])
		{	
			//destination
			int neighbor = edge.destination;
			//destination distance
			int weight = edge.weight;
			
			//if distance from the source and that node is less than assigned distance to that node
			if(currentDistance + weight < distance[neighbor])
			{	
				//push the node into pq
				pq.push({neighbor, weight});
				
				//new distance is edge distance + current distance
				distance[neighbor] = currentDistance + weight;
				
				//assign parent of the edge
				parent[neighbor] = node;
			}
		}
	}
	
	//if no node reaches hte destination the unreachable
	if(distance[destination] == INT_MAX)
	{
		cout << "Distance is unreachable" << endl;
		return {};
	}
	
	//defin list of shortest path nodes
	vector<int> path;
	
	//reverse map to path and insert into path
	for(int at = destination; at != -1 ; at = parent[at])
		path.push_back(at);
	
	//reverse path
	reverse(path.begin(), path.end());
	
	//return path
	return path;
	
}

enum VERTICES { A, B, C, D, F};

int main()
{
	int vertices, edges, source, destination;
	
	/*
	cout << "Enter the number of vertices: " ;
	cin >> vertices;
	cout << endl;
	
	
	cout << "Enter number of edges: ";
	cin >> edges;
	cout << endl;
	
	cout << "Enter the edges in the format (source destination weight): " << endl;
	
	for (int i = 0; i < edges; i++ )
	{	
		cout << "Edge: ";
		int src, dest, weight;
		cin >> src >> dest >> weight;
		graph[src].push_back(Edge(dest, weight));
		cout << endl;
	}
	
	
	cout << "Enter source vertex: ";
	cin >> source;
	cout << endl;
	
	cout << "Enter the destination vertex: ";
	cin >> destination;
	cout << endl;
	*/
	
	vertices = 5;
	source = 0;
	destination = 3;
	vector<vector<Edge>> graph(vertices);
	
	graph[0].push_back(Edge(1, 10));
    graph[0].push_back(Edge(2, 5));
    graph[1].push_back(Edge(2, 2));
    graph[1].push_back(Edge(3, 1));
    graph[2].push_back(Edge(1, 3));
    graph[2].push_back(Edge(3, 9));
    graph[2].push_back(Edge(4, 2));
    graph[3].push_back(Edge(4, 4));
	
	
	vector<int> shortestPath = dijkstra(source, destination, graph);
	
	if(!shortestPath.empty())
	{
		cout << "Shortest path " << source << " to " << destination << ": " << endl;
		for (int node: shortestPath)
		{
			cout << node << " ";
		}
		
		cout << endl;
	}
	
	
	return 0;
}