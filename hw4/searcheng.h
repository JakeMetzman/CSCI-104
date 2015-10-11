#ifndef SEARCHENG_H
#define SEARCHENG_H

#include <map>
#include <vector>
#include <string>
#include "webpage.h"
#include "myset.h"
#include "pageparser.h"

class SearchEng {
 public:
  SearchEng();
  ~SearchEng();
  void add_parse_from_index_file(std::string index_file, 
				 PageParser* parser);
  void add_parse_page(std::string filename, 
		      PageParser* parser);
  MySetWebPage find_pages(std::string& searchword);
  /**** Add other desired member functions here *****/
  void makeLower( std::string &mystring);

 private:
  /**** Add other desired data members here *****/
  MySetWebPage allPages;
  std::map<std::string, MySetWebPage> wordMap;
  WebPage* looks_for_webpage(std::string filename);
};

#endif
