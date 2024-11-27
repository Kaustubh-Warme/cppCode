#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

#define INF INT_MAX

//number of cities
int n = 4;

int tsp[4][4] = {
    {-1, 12, 10, 19},
    {12, -1, 8, 20},
    {10, 8, -1, 15},
    {19, 20, 15, -1}
};


int TSP(vector<vector<int>> & dp, int mask, int pos)
{
	if(mask == (1 << n) -1)
	{
		return tsp[pos][0] == -1 ? INF : tsp[pos][0];
	}
	
	if (dp[mask][pos] != -1)
	{
		return dp[mask][pos];
	}
	
	int minCost = INF;
	
	for(int city = 0; city < n; city++)
	{
		if((mask & (1 << city)) == 0 && tsp[pos][city] != -1)
		{
			int newMask = mask | (1 << city);
			int newCost = tsp[pos][city] + TSP(dp, newMask, city);
			minCost = min(minCost, newCost);
		}
	}
	
	return dp[mask][pos] = minCost;
}

int main()
{
	vector<vector<int>> dp(1 << n, vector<int>(n, -1));
	
	int minCost = TSP(dp, 1, 0);
	
	if(minCost == INF)
	{
		cout << "There is not valid TSP cycle" << endl;
	}
	else{
		cout << "The minimum cost of the TSP cycle is: " << minCost << endl;
	}
	
	return 0;
}