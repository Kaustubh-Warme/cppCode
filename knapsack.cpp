#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item
{
	int weight;
	int value;
	
	Item(int w, int v): weight(w), value(v) {}
	
	double valuePerWeight() const { return (double)value/(double)weight; }
};

bool compare(const Item & a, const Item & b)
{
	return a.valuePerWeight() > b.valuePerWeight();
}

double fractionalKnapsack(int knapsackCapacity, vector<Item> & items)
{
	sort(items.begin(), items.end(), compare);
	
	double totalValue = 0.0;
	int currentWeight = 0;
	
	for ( const Item & item: items)
	{
		if (currentWeight + item.weight <= knapsackCapacity)
		{
			currentWeight += item.weight;
			totalValue += item.value;
		}
		else
		{
			int remainingCapacity = knapsackCapacity - currentWeight;
			totalValue += item.valuePerWeight() * remainingCapacity;
			break;
		}
	}
	
	return totalValue;
}

int main()
{
	int n, knapsackCapacity;
	
	cout << "Enter number of items: ";
	cin >> n;
	cout << endl;
	
	cout << "Enter knapsack Capaicty: ";
	cin >> knapsackCapacity;
	cout << endl;
	
	vector<Item> items;
	
	for (int i = 0; i < n ; i++)
	{
		int weight, value;
		cout << "Enter weight and value for item " << i + 1<< ": ";
		cin >> weight >> value;
		items.push_back(Item(weight, value));
	}
	
	
	double maxValue = fractionalKnapsack(knapsackCapacity, items);
	
	cout << "\nMaximum total value in the knapsack: " << maxValue << endl << endl;
	
	return 0;
}