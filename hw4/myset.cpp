#include "myset.h"
#include "webpage.h"

MySetString::MySetString() : std::set<std::string>() {}

MySetString MySetString::set_intersection(const MySetString& other) {
	MySetString intersection;
	
	MySetString::iterator it;
	for(it = other.begin(); it != other.end(); ++it) {
		if( MySetString::count(*it) ) {
			intersection.insert(*it);
		}
	}
	
	return intersection;
}

MySetString MySetString::set_union(const MySetString& other) {
	MySetString union_set = *this;
	
	MySetString::iterator it;
	for(it = other.begin(); it != other.end(); ++it) {
		if( MySetString::count(*it) == 0 ) {
			union_set.insert(*it);
		}
	}
	
	return union_set;
}

MySetWebPage::MySetWebPage() : std::set<WebPage*>() {}

MySetWebPage MySetWebPage::set_intersection(const MySetWebPage& other) {

	MySetWebPage intersection;
	
	MySetWebPage::iterator it;
	for(it = other.begin(); it != other.end(); ++it) {
		if( MySetWebPage::count(*it) ) {
			intersection.insert(*it);
		}
	}
	
	return intersection;
}


MySetWebPage MySetWebPage::set_union(const MySetWebPage& other) {
	MySetWebPage union_set = *this;
	
	MySetWebPage::iterator it;
	for(it = other.begin(); it != other.end(); ++it) {
		if( MySetWebPage::count(*it) == 0 ) {
			union_set.insert(*it);
		}
	}
	
	return union_set;
}
