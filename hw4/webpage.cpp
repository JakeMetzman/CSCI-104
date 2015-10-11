#include "webpage.h"
#include "pageparser.h"
#include "mdparser.h"
#include <string>
#include <fstream>
#include <cstring>

WebPage::WebPage() {
	_filename = "";
}

WebPage::WebPage(std::string filename) {
	_filename = filename;
}

WebPage::~WebPage() {
	
}

void WebPage::filename(std::string fname) {
	_filename = fname;
	return;
}

std::string WebPage::filename() const {
	return _filename;
}

void WebPage::all_words(const MySetString& words) {
	MySetString union_set = _allWords.set_union(words);
	_allWords = union_set;
	return;
}

MySetString WebPage::all_words() const {
	return _allWords;
}

void WebPage::add_incoming_link(WebPage* wp) {
	_allInLinks.insert(wp);
	return;
}

MySetWebPage WebPage::incoming_links() const {
	return _allInLinks;
}

void WebPage::add_outgoing_link(WebPage* wp) {
	_allOutLinks.insert(wp);
	return;
}

MySetWebPage WebPage::outgoing_links() const {
	return _allOutLinks;
}

void WebPage::removeLinks( std::string& line) const {
	bool flag = false; // flag for when between "(" and ")"
	for( unsigned int i = 0; i < line.size(); i++) {
		if( line.substr(i,1) == "(") {
			flag = true;
			line.erase(i,1);
			i--;
			continue;
		} else if( line.substr(i,1) == ")" ) {
			flag = false;
			line.erase(i,1);
			i--;
			continue;
		} else if( flag ) {
			line.erase(i,1);
			i--;
			continue;
		}
	}
}

std::ostream & operator<< (std::ostream & os, const WebPage & page) {
	std::ifstream ifile( (page.filename()).c_str() );
	//ifile.open( page.filename() );
	std::string line;
	while( getline(ifile, line) ) {
		page.removeLinks(line);
		os << line << std::endl;
	}
	
	ifile.close();
	return os;
}