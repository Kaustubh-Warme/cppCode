#include <iostream>
#include <list>
#include <vector>

using namespace std;
const int TABLE_SIZE = 10;


struct Client
{
	string name;
	string phoneNum;
};

int hashFunction(string name, int tableSize)
{
	int hash = 0;
	
	for(char c: name)
	{
		hash += c;
	}
	
	return hash%tableSize;
}

class HashTableChaining
{
	private:
	vector<list<pair<string, string>>> table;
	
	public:
	HashTableChaining() { table.resize(TABLE_SIZE); }
	
	void insert(string name, string phoneNum)
	{
		int index = hashFunction(name, TABLE_SIZE);
		table[index].push_back(make_pair(name, phoneNum));
	}
	
	string search(string name, int & comparisons)
	{	
		int index = hashFunction(name, TABLE_SIZE);
		
		for(auto&entry : table[index])
		{	
			comparisons++;
			if (entry.first == name)
				return entry.second;
		}
		
		return "Not found";
	}	
};


class HashTableLinearProbing
{
	private:
	vector<pair<string, string>> table;
	
	vector<bool> isOccupied;
	
	public:
	HashTableLinearProbing()
	{
		table.resize(TABLE_SIZE, {"", ""});
		isOccupied.resize(TABLE_SIZE, false);
	}
	
	void insert(string name, string phoneNum)
	{
		int index = hashFunction(name, TABLE_SIZE);
		
		while(isOccupied[index])
		{
			index = (index + 1) % TABLE_SIZE;
		}
		
		table[index] = make_pair(name, phoneNum);
		isOccupied[index] = true;
	}
	
	string search(string name, int & comparisons)
	{	
		int index = hashFunction(name, TABLE_SIZE);
		int startIndex = index;
		
		while(isOccupied[index])
		{	
			comparisons++;
			
			if (table[index].first == name)
			{
				return table[index].second;
			}
			

			index = (index+1)%TABLE_SIZE;
			
			if (index == startIndex)
				break;
		}
		comparisons++;
		return "Not found";
	}
};



int main()
{
	
	vector<Client> clients;
	
	
	int numClients;
	string name, phone;
	
	cout << "Enter number of clients: " ;
	cin >> numClients;
	cout << endl;
	
	cout << "Enter name and phone numbers for the clients" << endl;
	
	for (int i = 0; i < numClients; i++)
	{
		cout << "Client " << i + 1 << "\t name: ";
		cin >> name;
		cout << endl;
		
		cout << "Client " << i + 1 << "\tphone number: ";
		cin >> phone;
		cout << endl;
		
		clients.push_back({name, phone});
		cout << endl;
	}
	
	HashTableChaining htChaining;
	HashTableLinearProbing htLinearProbing;
	
	for (const auto & client : clients)
	{
		htChaining.insert(client.name, client.phoneNum);
		htLinearProbing.insert(client.name, client.phoneNum);
	}
	
	cout << "Enter 0 to quit";
	cout << endl;
	while(true)
	{
		string searchName;
		cout << "\n\nEnter the name to search: ";
		cin >> searchName;
		
		if (searchName == "0")
		{
			cout << "Exiting...." << endl;
			break;
		}
		
		int chainComparisons, linearComparisons;
		
		chainComparisons = linearComparisons = 0;
		
		string phoneChaining = htChaining.search(searchName, chainComparisons);
		string phoneLinear = htLinearProbing.search(searchName, linearComparisons);
		
		cout << "Separate Chaining: " << phoneChaining;
		cout << "\t\tComparisons: " << chainComparisons << endl;
		
		cout << "Linear Probing: " << phoneLinear;
		cout << "\t\tComparisons: " << linearComparisons << endl << endl;
	}
	
	return 0;
}

