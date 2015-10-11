#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <vector>

using namespace std;

void removeSymbols( string &myString) // Removes any non-letter from string
{
	for( int i = 0; i < myString.length(); i++)
	{
		if( (int)(myString[i]) < 65 || (int)(myString[i]) > 122)
		{
			myString.erase( i, 1 );
			i--;
			continue;
		}
		else if ( (int)(myString[i]) > 90 && (int)(myString[i]) < 97)
		{
			myString.erase( i, 1 );
			i--;
			continue;
		}
	}
	return;
}

int main(int argc, char* argv[])
{
	ifstream ifile(argv[1]);
	ofstream ofile(argv[2]);
	stringstream currentPull;
	string current;
	string link = "";
	string link2 = "";
	
	
	//with strings
	while( ifile >> current )
	{
		if(current.substr(0,1) == "(" || current.substr(0,1) == "[") // if first character is ( or [
		{
			link = "", link2 = "";
			if( current.substr(0,1) == "(" ) // if first character is (
			{
				current.erase(0,1);
				while (current.substr(0,1) != ")")
				{
					link.append(current.substr(0,1));
					current.erase(0,1);
				}
				ofile << "LINK (" << link << ", " << link << ")" << endl;
				removeSymbols(current);
				if( current.length() >0)
				{
					ofile << current << endl;
				}
			}
			else if (current.substr(0,1) == "[") //if first character is [
			{
				current.erase(0,1);
				while( current.substr(0,1) != "]" ) // processes through ]
				{
					link2.append(current.substr(0,1));
					current.erase(0,1);
					if(current.length() == 0)
						{
							ifile >> current;
						}
				}
				current.erase(0,1);
				if( current.substr(0,1) != "(") // if next character isn't (
				{
					removeSymbols(link2);
					ofile << link2 << endl;
					removeSymbols(current);
					if( current.length() >0)
					{
						ofile << current << endl;
					}
				}
				else // if next character is (
				{
					current.erase(0,1);
					while( current.substr(0,1) != ")")
					{
						link.append(current.substr(0,1));
						current.erase(0,1);	
						if(current.length() == 0)
						{
							ifile >> current;
						}
					}
					current.erase(0,1);
					removeSymbols(current);
					ofile << "LINK (" << link << ", " << link2 << ")" << endl;
					removeSymbols(current);
					if( current.length() >0)
					{
						ofile << current << endl;
					}
				}
			}
		}
		else // if just normal word
		{
			removeSymbols(current);
			if( current.length() >0)
			{
				ofile << current << endl;
			}
		}
	} 
	
	ifile.close();
	ofile.close();
	return 0;
}