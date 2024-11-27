#include <iostream>
#include <list>
#include <vector>

using namespace std;
//table size
const int TABLE_SIZE = 10;


//define key-value pair
struct Client
{
	string name;
	string phoneNum;
};

//defin hash function
int hashFunction(string name, int tableSize)
{
	int hash = 0;
	
	for(char c: name)
	{
		hash += c;
	}
	
	return hash%tableSize;
}

//define class for seprate chaining
class HashTableChaining
{
	private:
	//declare hashtable. vector of list of pairs of key-value
	vector<list<pair<string, string>>> table;
	
	public:
	//constructor
	HashTableChaining() { table.resize(TABLE_SIZE); }
	
	//insert function
	void insert(string name, string phoneNum)
	{
		int index = hashFunction(name, TABLE_SIZE);
		table[index].push_back(make_pair(name, phoneNum));
	}
	
	//search function
	string search(string name, int & comparisons)
	{	
		//calculate index
		int index = hashFunction(name, TABLE_SIZE);
		
		//for list at that index
		for(auto&entry : table[index])
		{	
			//search for the key linearly
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
	//table of key-value
	vector<pair<string, string>> table;
	
	//list of available spaces
	vector<bool> isOccupied;
	
	public:
	//constructor
	HashTableLinearProbing()
	{
		table.resize(TABLE_SIZE, {"", ""});
		isOccupied.resize(TABLE_SIZE, false);
	}
	
	//insert function
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
	
	//search function
	string search(string name, int & comparisons)
	{	
		//calculate index from hash function
		int index = hashFunction(name, TABLE_SIZE);
		int startIndex = index;
		
		while(isOccupied[index])
		{	
			//increase comparisons
			comparisons++;
			
			//if key found, return the value
			if (table[index].first == name)
			{
				return table[index].second;
			}
			
			//else increase the index linearly 
			//and start loop with new index value
			index = (index+1)%TABLE_SIZE;
			
			//if circled back, then break
			if (index == startIndex)
				break;
		}
		comparisons++;
		return "Not found";
	}
};



int main()
{
	
	//declare key-value list
	vector<Client> clients;
	
	
	int numClients;
	string name, phone;
	
	cout << "Enter number of clients: " ;
	cin >> numClients;
	cout << endl;
	
	cout << "Enter name and phone numbers for the clients" << endl;
	
	//insert value in key-value list
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
	
	//declare objects for chaining and probing
	HashTableChaining htChaining;
	HashTableLinearProbing htLinearProbing;
	
	//insert each key-value in chaining and  
	for (const auto & client : clients)
	{
		htChaining.insert(client.name, client.phoneNum);
		htLinearProbing.insert(client.name, client.phoneNum);
	}
	
	cout << "Enter 0 to quit";
	
	
	//display comparisons for all the key values;
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

