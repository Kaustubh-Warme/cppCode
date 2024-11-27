#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

struct Edge {
    int destination, weight;
    
    Edge(int d, int w) : destination(d), weight(w) {};
};

struct compare {
    bool operator() (const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    }
};

vector<int> dijkstra(int source, int destination, vector<vector<Edge>>& graph) {
    int vertices = graph.size();
    
    vector<int> distance(vertices, INT_MAX);
    vector<int> parent(vertices, -1);
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, compare> pq;
    
    distance[source] = 0;
    
    pq.push({source, 0});
    
    while (!pq.empty()) {
        int node = pq.top().first;          
        int currentDistance = pq.top().second; 
        pq.pop();
        
        if (node == destination)
            break;
        
        for (Edge& edge : graph[node]) {
            int neighbor = edge.destination;
            int weight = edge.weight;
            
            if (currentDistance + weight < distance[neighbor]) {
                pq.push({neighbor, currentDistance + weight});
                
                distance[neighbor] = currentDistance + weight;
                parent[neighbor] = node;
            }
        }
    }
    
    if (distance[destination] == INT_MAX) {
        cout << "Distance is unreachable" << endl;
        return {};
    }
    
    vector<int> path;
    
    for (int at = destination; at != -1; at = parent[at])
        path.push_back(at);
    
    reverse(path.begin(), path.end());
    
    return path;
}

enum VERTICES { A, B, C, D, F };

int main() {
    int vertices = 5;
    int source = 0;
    int destination = 4;
    
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
    
    if (!shortestPath.empty()) {
        cout << "Shortest path " << source << " to " << destination << ": " << endl;
        for (int node : shortestPath) {
            cout << node << " ";
        }
        
        cout << endl;
    }
    
    return 0;
}
