#ifndef WEBPAGE_H
#define WEBPAGE_H
#include <string>
#include <iostream>
#include "myset.h"

class WebPage
{
 public:
  WebPage();

  WebPage(std::string filename);

  ~WebPage();

  /**
   * Sets the filename/URL of this webpage
   */
  void filename(std::string fname);

  /**
   * Returns the filename/URL of this webpage
   */
  std::string filename() const;

  /**
   * Updates the set containing all unique words in the text
   *  with the contents of the input parameter words
   */
  void all_words(const MySetString& words);

  /**
   * Returns all the unique, tokenized words in this webpage 
   */
  MySetString all_words() const;

  /**
   * Adds a webpage that links to this page
   */
  void add_incoming_link(WebPage* wp);

  /**
   * Returns all webpages that link to this page
   */
  MySetWebPage incoming_links() const;

  /**
   * Adds a webpage that this page links to
   */
  void add_outgoing_link(WebPage* wp);

  /**
   * Returns all webpages this page links to
   */
  MySetWebPage outgoing_links() const;

  /**
   * Displays the webpage text to the screen 
   */
  friend std::ostream & operator<< (std::ostream & os, const WebPage & page);

  /**** Add other desired member functions here *****/

 private:
  /**** Add other desired data members here *****/
    std::string _filename;
    MySetString _allWords;
    MySetWebPage _allOutLinks;
    MySetWebPage _allInLinks;
    //MySetString _allOutLinksAsStrings;
    
    void removeLinks( std::string& line) const;
};
#endif
