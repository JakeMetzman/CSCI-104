#ifndef MD_PARSER_H
#define MD_PARSER_H
#include "myset.h"
#include "pageparser.h"
#include <string>
#include <fstream>

class MDParser : public PageParser
{
	public:
		//MDParser();
		//~MDParser();
		void parse(std::string filename,
		     MySetString& allWords,
		     MySetString& allLinks);	
	private:
		void removeSymbols( std::string &mystring );
		//void makeLower( std::string &mystring);
		void addToSet( std::string &mystring, MySetString &allWords );
};

#endif