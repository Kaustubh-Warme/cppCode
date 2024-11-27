#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include <queue>
#include <string>

using namespace std;

struct Edge{
	string destination;
	int cost;
	
	Edge(string dest, int c): destination(dest), cost(c) {}
};


class FlightNetwork
{
	private:
	unordered_map<string, list<Edge>> adjList;
	
	public:
	void addCity(string city)
	{
		if(adjList.find(city) == adjList.end())
			adjList[city] = list<Edge>();
	}
	
	void addFlight(string cityA, string cityB, int cost)
	{
		adjList[cityA].push_back(Edge(cityB, cost));
		adjList[cityB].push_back(Edge(cityA, cost));
	}
	
	
	bool isConnected()
	{
		if(adjList.empty())
			return true;
		
		unordered_map<string, bool> visited;
		
		string startCity = adjList.begin()->first;
		queue<string> q;
		
		q.push(startCity);
		visited[startCity] = true;
		int visitedCount = 0;
		
		while(!q.empty())
		{
			string city = q.front();
			q.pop();
			visitedCount++;
			
			for(const Edge& edge: adjList[city])
			{
				if(!visited[edge.destination])
				{
					visited[edge.destination] = true;
					q.push(edge.destination);
				}
			}
		}
		
		return visitedCount==adjList.size();
	}
	
	
	void printNetwork()
	{
		for(const auto&pair: adjList)
		{
			string city = pair.first;
			cout << "\t" << city << " -> ";
			
			for(const Edge& edge: pair.second)
			{
				cout << "(" << edge.destination << "," << edge.cost << ")" ;
			}
			
			cout << endl;
		}
	}	
};


int main()
{
	FlightNetwork network;
	
	network.addCity("New York");
	network.addCity("Los Angeles");
	network.addCity("Chicago");
	network.addCity("Houston");
	network.addCity("Miami");
	
	network.addFlight("New York", "Los Angeles", 300); 
	network.addFlight("New York", "Chicago", 120);
	network.addFlight("Los Angeles", "Houston", 200);
	network.addFlight("Chicago", "Houston", 180);
	network.addFlight("Houston", "Miami", 150);
	
	
	cout << "\nFlight Network (Adjacency List Representation): " << endl;
	network.printNetwork();
	
	if(network.isConnected())
	{
		cout << "\nThe flight network is connected" << endl << endl;
	}
	else
	{
		cout << "\nThe flight network is not connected" << endl << endl;
	}
	
	return 0;
}