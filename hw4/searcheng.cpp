#include "searcheng.h"
#include "webpage.h"
#include "myset.h"
#include "pageparser.h"
#include <fstream>
#include <map>
#include <set>

SearchEng::SearchEng() {
	MySetWebPage allPages;
}

SearchEng::~SearchEng() {
	for(MySetWebPage::iterator it = allPages.begin(); it != allPages.end(); ++it) {
		delete *it;
	}
}

MySetWebPage SearchEng::find_pages(std::string& searchword) {
	std::map<std::string, MySetWebPage>::iterator it = wordMap.find(searchword);
	if( it != wordMap.end() ){
		return it->second;	
	} else {
		MySetWebPage emptySet;
		return emptySet;
	}
}

WebPage* SearchEng::looks_for_webpage(std::string filename) {
	for(MySetWebPage::iterator it = allPages.begin();it != allPages.end(); ++it) {
		WebPage* tempPage = *it;
		if( tempPage->filename() == filename) {
			return *it;
		}
	}
		WebPage* newPage = new WebPage;
		newPage->filename(filename);
		allPages.insert(newPage);
		return newPage;
}

void SearchEng::makeLower( std::string &mystring) {
	for(unsigned int x = 0; x< mystring.size(); x++) // makes string lower case before adding to set
		{
			mystring[x] = tolower(mystring[x]);
		}
	return;
}

void SearchEng::add_parse_from_index_file(std::string index_file, 
				 PageParser* parser) {
					 std::ifstream indexFile( index_file.c_str() );
					 std::string currentFileString;
					// MySetString currentWords;
					// MySetString currentLinks_strings;
					 
					 while( getline( indexFile, currentFileString) ) {
						 if(currentFileString != "") {
							 //std::cout << "trying to parse: " << currentFileString << std::endl;//debug
							 add_parse_page(currentFileString, parser);
						 }					
						 	 
						 /*parser.parse(currentFileString, currentWords, currentLinks_strings);
						 WebPage* currentPage = new Webpage;
						 
						 currentPage.filename( currentFileString );
						 currentPage.allWords(currentWords);
						 for( MySetString::iterator it = currentLinks_strings.begin(): it != currentLinks_strings.end(); ++it) {
							 WebPage::iterator it2 = allPages.find(*it);
							 if(it2 != allPages.end() ) {
								 currentPage.add_outgoing_link(it);
							 }
						 }
						 allPages.insert(currentPage);
						 delete currentPage;*/
					 }
					 
					 indexFile.close();
					 return; 
				 }
				 
void SearchEng::add_parse_page(std::string filename, 
		      PageParser* parser) {
				  
				MySetString currentWords;
				MySetString currentLinks_strings;
			  	parser->parse(filename, currentWords, currentLinks_strings);
				  std::cout << "Just ran parse" << std::endl;
				WebPage* currentPage = new WebPage;
						 
				currentPage->filename( filename );
				currentPage->all_words(currentWords);
				for( MySetString::iterator it = currentLinks_strings.begin(); it != currentLinks_strings.end(); ++it) {
					currentPage->add_outgoing_link(looks_for_webpage(*it));
					
					//Need to deal with links still
					
					/*MySetString::iterator it2 = allPages.find(*it);
					if(it2 != allPages.end() ) {
						currentPage->add_outgoing_link(it);
					}*/
				}
				allPages.insert(currentPage); 
				 // std::cout << "inserted page" << std::endl; //debug
				  MySetString::iterator it;
				for( it = currentWords.begin(); it != currentWords.end(); ++it ) { // makes wordMap;
					std::string word = *it;
					makeLower(word);
					std::map<std::string, MySetWebPage>::iterator it2 = wordMap.find(word);
					//std::cout << "trying to insert: " << word << std::endl; //debug
					if(it2 != wordMap.end()) {
						it2->second.insert(currentPage);
						//std::cout << "added page to " << it2->first << std::endl; //debug
					} else {
						MySetWebPage newSet;
						newSet.insert( currentPage );
						wordMap.insert( make_pair(word, newSet));
						//std::cout << "inserted: " << word << std::endl; //debug
					}
					//std::cout << "went through for loop" << std::endl; //debug
				}  
				
				//deals with all incoming links;
				MySetWebPage::iterator it3;
				for( it3 = allPages.begin(); it3!= allPages.end(); ++it3) {
					WebPage* outgoingPage = *it3;
					MySetWebPage outgoingLinks = outgoingPage->outgoing_links();
					
					MySetWebPage::iterator it4;
					for( it4 = outgoingLinks.begin(); it4 != outgoingLinks.end(); ++it4) {
						WebPage* incomingPage = *it4;
						incomingPage->add_incoming_link(outgoingPage);
					}
				}
				
				//delete currentPage;
				return;
			  }