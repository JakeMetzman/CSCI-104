#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <set>

using namespace std;

void removeSymbols( string &myString, set<string> &wordList) // Removes any non-letter from string, adds word to set
{
	int location = 0;
	for( unsigned int i = 0; i < myString.length(); i++)
	{
		if( (int)(myString[i]) < 65 || (int)(myString[i]) > 122) // finds non- letters
		{
			myString.erase( i, 1 );
			string temp = myString.substr(location, i-location);
			
			for(unsigned int x = 0; x< temp.size(); x++) // makes string lower case before adding to set
			{
				temp[x] = tolower(temp[x]);
			}
			
			wordList.insert(temp);
			location =i;
			i--;
			continue;
		}
		else if ( (int)(myString[i]) > 90 && (int)(myString[i]) < 97)
		{
			myString.erase( i, 1 );
			string temp = myString.substr(location, i-location);
			
			for(unsigned int x = 0; x< temp.size(); x++)
			{
				temp[x] = tolower(temp[x]);
			}
			
			wordList.insert(temp);
			location = i;
			i--;
			continue;
		}
	}
	
	string temp = myString.substr(location, myString.length()-location);
	for(unsigned int x = 0; x< temp.size(); x++) //end case
			{
				temp[x] = tolower(temp[x]);
			}
	wordList.insert( temp );
	
	return; 
	
}

int main(int argc, char* argv[])
{
	ifstream ifile(argv[1]);
	string current = "";
	stringstream line;
	set<string> wordList;
	
	while( ifile >> current ) // pulls word, removes symbols, and adds to set
	{
		removeSymbols(current, wordList);
		
	}
	
	//prints set
	/* for(set<string>::iterator it=wordList.begin(); it != wordList.end(); ++it){
 cout << "word: " << *it << endl; }*/

 	//querries user for word, searches
	
	while(1)
	{
		cout << "Word to check: ";
		getline( cin, current );
		if( current == "") // exit case
		{
			break;
		}
		
		for(unsigned int i = 0; i< current.size(); i++) // makes input lower case before searching set
			{
				current[i] = tolower(current[i]);
			}
		
		if(wordList.count(current))
		{	
			cout << "in the file" << endl;
		}
		else
		{
			cout << "not in the file" << endl;	
		}
	}
return 0;	
}