#include "llistint.h"
#include <cstdlib>
#include <stdexcept>

#include <iostream>

LListInt::LListInt()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListInt::~LListInt()
{
  clear();
}

bool LListInt::empty() const
{
  return size_ == 0;
}

int LListInt::size() const
{
  return size_;
}

/**
 * Complete the following function
 */
void LListInt::insert(int loc, const int& val)
{
  if(size_ == 0 && loc == 0) // inserting into empty list
  {
    Item* node = new Item;
    node->val = val;
    node->prev = NULL;
    node->next = NULL;
    head_ = node;
    tail_ = node;
    
    size_++;
    return;
  }
  
  if(loc > size_ || loc < 0 ) // invalid case
  {
    throw std::invalid_argument("bad location");
  }

  
  if( loc != 0 && loc != size_) //middle of list
  {
    Item* insertLocation = getNodeAt(loc);
    
    Item* node = new Item;
    node->val = val;
    node->prev = insertLocation->prev;
    node->next = insertLocation;
    
    insertLocation->prev->next = node;
    insertLocation->prev = node;
    
  }
  
  else if( loc == 0) // begining of list
  {
    Item* insertLocation = getNodeAt(loc);
    
    Item* node = new Item;
    node->val = val;
    node->prev = insertLocation->prev;
    node->next = insertLocation;
    
    insertLocation->prev = node;
    head_ = node;
  }
  
  else if( loc == size_) // end of list
  {
    Item* insertLocation = getNodeAt(loc-1);
    
    Item* node = new Item;
    node->val = val;
    node->prev = insertLocation;
    node->next = insertLocation->next;
    
    insertLocation->next = node;
    tail_ = node;
  }
  
  size_++;
  return;
}

/**
 * Complete the following function
 */
void LListInt::remove(int loc)
{
  if(loc >= size_ || loc < 0 ) // invalid
    {
      throw std::invalid_argument("bad location");
    }
  
  if( loc != 0 && loc != size_-1) //middle
  {
    Item* insertLocation = getNodeAt(loc);
    
    insertLocation->prev->next = insertLocation->next;
    insertLocation->next->prev = insertLocation->prev;
    
    delete insertLocation;
  }
  
  else if( loc == 0 && size_ == 1) //removing last item from list.
  {
    clear();
  }
  
  else if( loc == 0 && size_ != 1) // remove from begining
  {
    Item* insertLocation = getNodeAt(loc);
    
    insertLocation->next->prev = insertLocation->prev;
    head_ = insertLocation->next;
    
    delete insertLocation;
  }
  
  else if( loc == size_ - 1) // remove from end
  {
    Item* insertLocation = getNodeAt(loc);
    
    insertLocation->prev->next = NULL;
    tail_ = insertLocation->prev;
    
    delete insertLocation;
  }

size_--;
return;
}

void LListInt::set(int loc, const int& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

int& LListInt::get(int loc)
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

int const & LListInt::get(int loc) const
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListInt::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


/**
 * Complete the following function
 */
LListInt::Item* LListInt::getNodeAt(int loc) const
{
  if(loc >= size_ || loc < 0 )
  {
    throw std::invalid_argument("bad location");
  }
  
  Item* temp = head_;
  int current = 0;
  while( current != loc) // move through array to get to location
  {
    temp = temp->next;
    current++;
  }
  return temp;
}

