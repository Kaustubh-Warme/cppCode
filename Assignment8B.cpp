#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
//partition function
int partition(vector<int> & arr, int low, int high)
{	
	//define pivot
	int pivot = arr[high];
	
	//define low element pointer
	int i = low - 1;
	
	
	//iterate till high - 1
	for (int j = low; j <= high - 1; j++)
	{	
		//if element is smaller than pivot
		if(arr[j] < pivot)
		{
			//increase the low element pointer
			i++;
			//swap with the higher element;
			swap(arr[i], arr[j]);
		}
	}
	
	//finally swap last pivot with next lower element index
	swap(arr[i + 1], arr[high]);
	
	// return index of the pivot
	return i+1;
}

//define quick sort
void quickSort(vector<int> & arr, int low, int high)
{	
	//if low is less than high
	if(low < high)
	{	
		//get partition index
		int pi = partition(arr, low, high);
		
		//separater arr to the left and right of the partition index
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