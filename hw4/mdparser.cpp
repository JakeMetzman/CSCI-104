#include "myset.h"
#include "mdparser.h"
#include "pageparser.h"
#include <string>
#include <fstream>


//MDParser::MDParser() { }

//MDParser::~MDParser() { }

void MDParser::parse(std::string filename,
		     MySetString& allWords,
		     MySetString& allLinks) {
				 
				 std::string current = "";
				 std::ifstream ifile( filename.c_str() );
				 
				 while( ifile >> current) {
					 if( current.substr(0,1) == "[") {
						std::string link = "";
						current.erase(0,1);
						while( current.substr(0,1) != "]" ) {
							link.append( current.substr(0,1) );
							current.erase(0,1);
						}
						MDParser::removeSymbols(link);
						//makeLower(link);
						MDParser::addToSet(link, allWords);
						
						link = "";
						current.erase(0,2);
						while( current.substr(0,1) != ")" ) {
							link.append( current.substr(0,1) );
							current.erase(0,1);
						}
						//MDParser::makeLower(link);
						MDParser::addToSet(link, allLinks);
						
					 } else {
						 MDParser::removeSymbols(current);
						 //makeLower(current);
						 MDParser::addToSet(current, allWords);
					 }
				 }
				 
				 ifile.close();
				 return;
			 }
			 
void MDParser::removeSymbols( std::string &myString) // Removes any non-letter/number from string.
{
	for( unsigned int i = 0; i < myString.length(); i++)
	{
		if( (int)(myString[i]) < 48 || (int)(myString[i]) > 122)
		{
			myString.erase( i, 1 );
			myString.insert(i, " ");
			continue;
		}
		else if ( (int)(myString[i]) > 57 && (int)(myString[i]) < 65)
		{
			myString.erase( i, 1 );
			myString.insert(i, " ");
			continue;
		}
		else if ( (int)(myString[i]) > 90 && (int)(myString[i]) < 97)
		{
			myString.erase( i, 1 );
			myString.insert(i, " ");
			continue;
		}
	}
	
	return;
}

/*void MDParser::makeLower( std::string &mystring) {
	for(unsigned int x = 0; x< mystring.size(); x++) // makes string lower case before adding to set
		{
			mystring[x] = tolower(mystring[x]);
		}
	return;
}*/

void MDParser::addToSet( std::string &mystring, MySetString &currentSet ) {
	int location = 0;
	for( unsigned int i = 0; i < mystring.size(); i++) { //removes spaces
		if( mystring.substr(i,1) == " " ) {
			currentSet.insert( mystring.substr(location, i-location) );
			location = i;
			mystring.erase(i,1);
			i--;
		}
	}
	currentSet.insert( mystring.substr(location, mystring.size()-location) );
	return;
}