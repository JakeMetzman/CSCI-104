#include "llistint.h"
#include "llistint.cpp"
#include <iostream>

using namespace std;

int main() {
   LListInt * list = new LListInt();

  // Check if the list is initially empty.
  if (list->empty()) {
    std::cout << "SUCCESS: List is empty initially." << std::endl;
  } else {
    std::cout << "FAIL: List is not empty initially when it should be." << std::endl;
  }
  

  // Insert an item at the head.
  list->insert(0, 3);

  // Check if the list is still empty.
  if (!list->empty()) {
    std::cout << "SUCCESS: List is not empty after one insertion." << std::endl;
  } else {
    std::cout << "FAIL: List is empty after one insertion." << std::endl;
  }

  if (list->size() == 1) {
    std::cout << "SUCCESS: List has size 1 after one insertion." << std::endl;
  } else {
    std::cout << "FAIL: List has size " << list->size() << " after one insertion.";
    std::cout << std::endl;
  }

  // Check if the value is correct.
  if (list->get(0) == 3) {
    std::cout << "SUCCESS: 3 is at the 0th index of the list." << std::endl;
  } else {
    std::cout << "FAIL: 3 is not at the 0th index of the list, " << list->get(0);
    std::cout << " is instead." << std::endl;
  }

  std::cout << "insertting 4 to location 1" << std::endl;
  list->insert(1, 4);
  std::cout << "value at location 1 should be 4: " << list->get(1) << std::endl;
  
  std::cout << "inserting 5 to location 1" << std::endl;
  list->insert(1, 5);
  
  std::cout << "list size should be 3: " << list->size() << std::endl;
  
  std::cout << "removing 3 from location 0" << std::endl;
  list->remove(0);
  std::cout << "list size should be 2: " << std::endl;
  std::cout << list->size() << std::endl;
  
  std::cout << "removing from end of list" << std::endl;
  list->remove(1);
  
  list->insert(0, 4);
  
  std::cout << "removing from begining of list" << std::endl;
  list->remove(0);
  
  std::cout << "removing from begining of list - makes it empty" << std::endl;
  list->remove(0);

  std::cout << "clearing list" << std::endl;
  list->clear();
  
  std::cout << "repopulate list" << std::endl;
  list->insert(0, 4);
  list->insert(0, 4);
  
  std::cout << "add to begining of list" << std::endl;
  list->insert(0, 4);
  
  std::cout << "add to middle of list" << std::endl;
  list->insert(2, 4);
  std::cout << "add to end of list" << std::endl;
  list->insert(4, 4);
  std::cout << "remove from middle of list" << std::endl;
  list->remove(2);


  // Clean up memory.
  list->clear();
  delete list;
  
  return 0;
}

