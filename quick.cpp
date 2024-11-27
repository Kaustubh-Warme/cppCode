#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int partition(vector<int> & arr, int low, int high)
{	
	int pivot = arr[high];
	
	int i = low - 1;
	
	
	for (int j = low; j <= high - 1; j++)
	{	
		if(arr[j] < pivot)
		{
			i++;
			swap(arr[i], arr[j]);
		}
	}
	
	swap(arr[i + 1], arr[high]);
	
	return i+1;
}

void quickSort(vector<int> & arr, int low, int high)
{	
	if(low < high)
	{	
		int pi = partition(arr, low, high);
		
		quickSort(arr, low, pi-1);
		quickSort(arr, pi+1, high);
	}
}


int main()
{
	int num;
	
	cout << "Enter number of elements: ";
	cin >> num;
	cout << endl;
	
	vector<int> arr ;
	
	for (int i = 0; i < num; i ++)
	{
		int element;
		cout << "Enter element " << i+1 << ": ";
		cin >> element;
		arr.push_back(element);
		cout << endl;
	}
	
	quickSort(arr, 0, num-1);
	
	for (int i = 0; i < num; i++)
		cout << arr[i] << " ";
	
	cout << endl;
	return 0;
}