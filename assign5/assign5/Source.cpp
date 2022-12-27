#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <sstream>

using namespace std;

class HashTable {

private:
	//Number of buckets
	int buckets;

	// Pointer to array with buckets
	list<int>* bucketTable;

public:

	// Constructor
	HashTable(int num); 

	// Insert key into the hash table
	void insertK(int key);

	// Delete key from the hash table
	void deleteK(int key);

	// Map the values to the key
	int Hash(int key) {
		
		int hashFunction = key % buckets;

		return hashFunction;

	}

	void display();
};
HashTable::HashTable(int buckets)
{
	this->buckets = buckets;
	bucketTable = new list<int>[buckets];
}

void HashTable::insertK(int key)
{
	int i = Hash(key);
	bucketTable[i].push_back(key);
}

void HashTable::deleteK(int key)
{
	// Hash index of the key
	int index = Hash(key);

	// Find key in list
	list <int> ::iterator i;
	for (i = bucketTable[index].begin();
		i != bucketTable[index].end(); i++) {
		if (*i == key)
			break;
	}

	// Remove the key if found
	if (i != bucketTable[index].end())
		bucketTable[index].erase(i);
}

// Display hash table
void HashTable::display() {
	for (int i = 0; i < buckets; i++) {
		cout << i;
		for (auto x : bucketTable[i])
			cout << " --> " << x;
		cout << endl;
	}
}

int main()
{
	string tableR2 = "table2.txt";

	//Number of tuples for each table
	const int tuples1 = 3;
	const int tuples2 = 3;

	//Joining attribute selection
	int atrb1, atrb2;

	cout << endl << "Enter the Joining attribute for table R1" << endl << endl;
	cin >> atrb1;
	cout << endl << "Enter the Joining attribute for table R2" << endl << endl;
	cin >> atrb2;

	//initialising the table's data into array
	string line;
	string r1[tuples1][4];
	string r2[tuples1][4];

	ifstream myfile("table1.txt");
	int i = 0;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			// cout << line << '\n';
			string s = line;
			string delimiter = " ";

			size_t pos = 0;
			string token;
			int j = 0;
			while ((pos = s.find(delimiter)) != std::string::npos) {
				token = s.substr(0, pos);
				s.erase(0, pos + delimiter.length());
				r1[i][j] = token;
				j++;
			}
			r1[i][j] = s;
			i++;
		}
		myfile.close();
	}
	else
		cout << "Unable to open file R1";

	// initilising table R2 data into array:
	ifstream myfile2("table2.txt");
	i = 0;
	if (myfile2.is_open())
	{
		while (getline(myfile2, line))
		{
			string s = line;
			string delimiter = " ";

			size_t pos = 0;
			string token;
			int j = 0;
			while ((pos = s.find(delimiter)) != std::string::npos) {
				token = s.substr(0, pos);
				s.erase(0, pos + delimiter.length());
				r2[i][j] = token;
				j++;
			}
			r2[i][j] = s;
			i++;
		}
		myfile2.close();
	}
	else
		cout << "Unable to open file R1";

	//let the count of buckets be 7
	HashTable h1(7);
	HashTable h2(7);
	if (tuples1 <= tuples2) {
		//R2 will be used for probing
		//assuming the attributes to be of type int
		for (int i = 0; i < tuples1; i++) {
			int x = stoi(r1[i][atrb1 - 1]);
			h1.insertK(x);
		}
		for (int i = 0; i < tuples2; i++) {
			int x = stoi(r2[i][atrb2 - 1]);
			h2.insertK(x);
		}

		// display the Hash table
		cout << endl << "The bucket for Table R1 is: " << endl << endl << endl;
		h1.display();
		cout << endl << "The bucket for Table R2 is: " << endl << endl << endl;
		h2.display();
	}
	else {
		//R1 will be used for probing
		//assuming the attributes to be of type int
		for (int i = 0; i < tuples2; i++) {
			int x = stoi(r1[i][atrb1 - 1]);
			h1.insertK(x);
		}

		HashTable h2(7);
		for (int i = 0; i < tuples1; i++) {
			int x = stoi(r2[i][atrb2 - 1]);
			h2.insertK(x);
		}

		// Display Hash table
		cout << endl << "The bucket for Table R1 is: " << endl << endl << endl;
		h1.display();
		cout << "The bucket for Table R2 is: " << endl << endl;
		h2.display();
	}


	return 0;
}