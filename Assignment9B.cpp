#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Job
{
	char id;
	int deadline;
	int profit;
	
	Job(char jobID, int dl, int pr): id(jobID), deadline(dl), profit(pr) {}
};


bool compare(Job a, Job b)
{
	return a.profit > b.profit;
}

void jobScheduling(vector<Job> & jobs, int timeSlots)
{
	sort(jobs.begin(), jobs.end(), compare);
	
	vector<int> result(timeSlots, -1);
	
	vector<bool> slot(timeSlots, false);
	
	int totalProfit = 0;
	
	for(int i = 0; i < jobs.size(); i++)
	{
		for(int j = min(timeSlots, jobs[i].deadline)-1; j >= 0 ;j--)
		{
			if(!slot[j])
			{
				result[j] = i;
				slot[j] = true;
				totalProfit += jobs[i].profit;
				break; 
			}
		}	
	}
	
	
	cout << "Selected jobs with their deadlines: " << endl;
	
	for (int i = 0; i< timeSlots; i++)
	{
		if(slot[i])
		{
	cout << "Job " << jobs[result[i]].id << " with deadline" << jobs[result[i]].deadline << endl;
		}
	}
	
	cout << "Total Profit: " << totalProfit << endl << endl;
}


int main()
{
	int numJobs, timeSlots;
	cout << "Enter number of jobs: ";
	cin >> numJobs;
	cout << endl << endl;
	
	vector<Job> jobs;
	
	cout << "Enter jobs in the format (job, deadline, profit)" << endl;
	
	for (int i = 0; i < numJobs ; i++)
	{	char jobId;
		int deadline, profit;
		cout << "Jobs " << i+1 << ": " ;
		cin >> jobId >> deadline >> profit;
		jobs.push_back(Job(jobId, deadline, profit));
		cout << endl;
	}
	
	
	cout << "\nEnter number of time slots: ";
	cin >> timeSlots;
	cout << endl;
	
	jobScheduling(jobs, timeSlots);
	
	return 0;
}