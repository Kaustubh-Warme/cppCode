#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int> & vec, int left, int mid, int right)
{
	int i , j, k;
	int n1 = mid -left + 1;
	int n2 = right - mid;
	
	vector<int> leftVec(n1), rightVec(n2);
	
	for (i = 0; i < n1; i++)
		leftVec[i] = vec[left + i];
	
	for (j = 0; j < n2; j++)
		rightVec[j] = vec[mid +1 +j];
	
	i = j = 0;
	k = left;
	
	while( i < n1 && j < n2)
	{
		if(leftVec[i] <= rightVec[j])
		{
			vec[k] = leftVec[i];
			i++;
		}
		else
		{
			vec[k] = rightVec[j];
			j++;
		}
		k++;
	}	

	while(i < n1)
	{
		vec[k] = leftVec[i];
		i++;
		k++;
	}
}



void mergeSort(vector<int> & vec, int left, int right)
{
	if ( left < right)
	{
		int mid = left + (right-left) / 2;
		
		mergeSort(vec, left, mid);
		mergeSort(vec, mid+1, right);
		
		merge(vec, left, mid, right);
	}
}


int main()
{	
	int num;
	vector<int> vec;
	
	cout << "Enter number of elements: ";
	cin >> num;
	cout << endl;
	
	for (int i = 0; i < num; i++)
	{
		int element;
		cout << "Enter element " << i+1 << ": ";
		cin >> element;
		vec.push_back(element);
	}
	cout << endl;
	mergeSort(vec, 0, num-1);
	
	for (auto i: vec)
		cout << i << " ";
	cout << endl;
	
	return 0;
}