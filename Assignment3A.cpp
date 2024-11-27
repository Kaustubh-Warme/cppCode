#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <ctime>
using namespace std;

struct User
{
	int id;
	string name;
	int dayOfBirth;
	int monthOfBirth;
	int numComments;
	vector<int> friends;
	
	 User() : id(0), dayOfBirth(0), monthOfBirth(0), numComments(0) {}
	
	User(int id, const string& name, int day, int month, int comments):
	id(id),
	name(name),
	dayOfBirth(day),
	monthOfBirth(month),
	numComments(comments){}
};


//graph structure
class FriendNetwork
{
	private:
	unordered_map<int,  User> users;
	
	
	public:
	void addUser(int id, const string& name, int day, int month, int comments);
	
	void addFriendship(int user1, int user2);
	
	void findMaxFriends();
	
	void findMaxMinComments();
	
	void findBirthdayInMonth(int currentMonth);
	
	void DFS(int startUserId);
	
	void DFSuntil(int userID, unordered_map<int, bool> &visited);
	
	void BFS(int startUserId);
};

void FriendNetwork::addUser(int id, const string& name, int day, int month, int comments)
{
	users[id] = User(id, name, day, month, comments); 
}

void FriendNetwork::addFriendship(int user1, int user2)
{
	users[user1].friends.push_back(user2);
	users[user2].friends.push_back(user1);
}

void FriendNetwork::findMaxFriends()
{
	int maxFriends = 0;
	int userWithMaxFriends = -1;
	
	for(const auto& pair: users)
	{
		const User &user = pair.second;
		
		if(user.friends.size() > maxFriends)
		{
			maxFriends = user.friends.size();
			userWithMaxFriends = user.id; 
		}
	}
	
	cout << "User with maximum friends: " << users[userWithMaxFriends].name;
	cout << " with " << maxFriends << " friends" << endl;
}


void FriendNetwork::findMaxMinComments()
{
	int maxComments = INT_MIN, minComments = INT_MAX;
	int userWithMaxComments = -1, userWithMinComments = -1;
	
	
	for(const auto&pair: users)
	{
		
		const User& user = pair.second;
		if(user.numComments > maxComments)
		{
			maxComments = user.numComments;
			userWithMaxComments = user.id;
		}
		
		if(user.numComments < minComments)
		{
			minComments = user.numComments;
			userWithMinComments = user.id;
		}
	}
	
	cout << "User with maximum comments: ";
	cout << users[userWithMaxComments].name;
	cout <<" with " << maxComments << " comments." << endl;
	
	cout << "User wit minimum coments: ";
	cout << users[userWithMinComments].name;
	cout << " with " << minComments << " comments." << endl;
}

void FriendNetwork::findBirthdayInMonth(int currentMonth)
{
	cout << "Users having birthday in month " << currentMonth << endl;
	
	for(const auto& pair: users)
	{
		const User& user = pair.second;
		
		if(user.monthOfBirth  ==currentMonth)
			cout << user.name << " has a birthday on " << user.dayOfBirth << endl;
	}
}


void FriendNetwork::DFS(int startUserId)
{
	unordered_map<int, bool> visited;
	cout << "DFS Travesal starting from " << users[startUserId].name << ":";
	
	DFSuntil(startUserId, visited);
	cout << endl;
}

void FriendNetwork::DFSuntil(int userId, unordered_map<int, bool>& visited)
{
	visited[userId] = true;
	cout << users[userId].name << " ";
	
	for(int friendId: users[userId].friends)
	{
		if(!visited[friendId])
			DFSuntil(friendId, visited);
	}
}


void FriendNetwork::BFS(int startUserId)
{
	unordered_map<int, bool> visited;
	queue<int> q;
	
	visited[startUserId] = true;
	q.push(startUserId);
	cout << "BFS Traversal starting from " << users[startUserId].name << ":";
	
	while(!q.empty())
	{
		int userId = q.front();
		q.pop();
		
		cout << users[userId].name << " ";
		
		for(int friendId : users[userId].friends)
		{
			if(!visited[friendId])
			{
				visited[friendId] = true;
				q.push(friendId);
			}
		}
	}
	cout << endl;
}


int doMenu()
{
	int choice;
	
	cout << "\n\n----------------- Menu -----------------" << endl;
	cout << "1. Who has most number of Friends?		  	 " << endl;
	cout << "2. Whose post has maximum comments and minimum\b comments? 	 	 " << endl;
	cout << "3. Whose birthday is in month? 		 " << endl;
	cout << "4. DFS Traaversal							 " << endl;
	cout << "5. BFS Traaversal							 " << endl;
	cout << "0. Quit								     " << endl << endl;
	
	cout << "Enter your choice: ";
	cin >> choice;
	return choice;
}

int main()
{
	FriendNetwork network;
	
	network.addUser(1, "Alice", 15, 10, 100);
	network.addUser(2, "Bob", 20, 12, 150);
	network.addUser(3, "Charlie", 5, 10, 50);
	network.addUser(4, "David", 25, 11, 200);
	network.addUser(5, "Eve", 13, 10, 30);
	
	network.addFriendship(1, 2);
	network.addFriendship(1, 3);
	network.addFriendship(2, 4);
	network.addFriendship(3, 5);
	
	
	
	bool endProgram = false;
	
	while(!endProgram)
	{	
		int choice = doMenu();
		switch(choice)
		{
			case 1:
				network.findMaxFriends();
				break;
			
			case 2:
				network.findMaxMinComments();
				break;
				
			case 3:
				int month;
				cout << "Enter month number (1-12): "; 
				cin >> month;
				cout << endl ;
				network.findBirthdayInMonth(month);
				break;
				
			case 4:
				network.DFS(1);
				break;
			
			case 5:
				network.BFS(1);
				break;
				
			case 0:
				cout << "Exiting..." << endl << endl;
				endProgram = true;
				break;
				
			default:
				cout << "Incorrect input entered" << endl;
				endProgram = true;
				break;

			
		}
	}
	
}
