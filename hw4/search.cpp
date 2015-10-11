#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <sstream>

#include "webpage.h"
#include "searcheng.h"
#include "mdparser.h"
#include "myset.h"

using namespace std;

void display_results(MySetWebPage& results);

int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "usage: ./search index_file...Please provide an index file" << endl;
    return 1;
  }

  /****************   Add code to ***************************/
  /* Initialize your search engine and parse all the pages */
  SearchEng eng;
  PageParser* parser = new MDParser;
  string index_file(argv[1]);
  //cout << "About to Parse" << endl; //debug
  eng.add_parse_from_index_file(index_file, parser);
  //cout << "Finished Parsing" << endl; //debug
  delete parser;

  string myline;
  bool done = false;
  while( !done ){
    cout << "\n++++++++++++++++++++" << endl;
    cout << "Enter search terms: " << endl;
    getline(cin, myline);
    cout << "++++++++++++++++++++\n" << endl;

    /* Add your code here and feel free to modify    */
    /*  what is above but don't change the display.  */
    /* Call display_results() with the set of pages  */
    /*  that match the search. It will display the   */
    /*  matching results to the screen for you.      */

    if( myline == ".") {
      break;
    } 
    stringstream ss;
    ss  << myline;
    string word1;
    ss >> word1;
    
    if( word1 == "AND") {
      string word2;
      MySetWebPage pageSet;
      ss >> word1 >> word2;
      eng.makeLower(word1);
      eng.makeLower(word2);
      pageSet = (eng.find_pages(word1)).set_intersection(eng.find_pages(word2));
      while(ss >> word1) {
        eng.makeLower(word1);
        pageSet = pageSet.set_intersection(eng.find_pages(word1));
      }
      display_results(pageSet);
    } else if (word1 == "OR") {
      string word2;
      MySetWebPage pageSet;
      ss >> word1 >> word2;
      eng.makeLower(word1);
      eng.makeLower(word2);
      pageSet = (eng.find_pages(word1)).set_union(eng.find_pages(word2));
      while(ss >> word1) {
        eng.makeLower(word1);
        pageSet = pageSet.set_union(eng.find_pages(word1));
      }
      display_results(pageSet);
    } else if( word1 == myline) {
      eng.makeLower(word1);
      MySetWebPage pageSet1 = eng.find_pages(word1);
    //  std::cout << pageSet1.size() << std::endl;// debug;
      display_results(pageSet1);
    }
    
    
    }
    return 0;
  }

void display_results(MySetWebPage& results)
{
  int hits = results.size();
  cout << hits << " hits." << endl;
  cout << "=====" << endl;
  int i=0;
  for(set<WebPage*>::iterator it = results.begin();
      it != results.end();
      ++it)
    {
      cout << (*it)->filename() << endl;
      cout << "+---+" << endl;
      cout << (**it) << "\n" << endl;
      i++;
    }
  
}
