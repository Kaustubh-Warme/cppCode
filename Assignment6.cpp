#include <iostream>
#include <queue>
#include <vector>


using namespace std;

int main()
{
	int numStudents;
	cout << "Enter number of students: ";
	cin >> numStudents;
	cout << endl;
	
	priority_queue<int> maxHeap;
	
	priority_queue<int, vector<int>, greater<int>> minHeap;
	
	cout << "Enter the marks of students: " << endl;
	
	for (int i = 0; i <numStudents ; ++i)
	{
		cout << "Student " << i + 1 << ": ";
		int mark;
		cin >> mark;
		maxHeap.push(mark);
		minHeap.push(mark);
		cout << endl;
	}
	
	
	int maxMarks = maxHeap.top();
	int minMarks = minHeap.top();
	
	cout << "Maximum marks obtained: " << maxMarks << endl;
	cout << "Minimum marks obtained: " << minMarks << endl;
	
	return 0;
}