#include <iostream>
#include <cstdlib>

using namespace std;

struct Node {
    int value;
    Node *next;
};

void split (Node*& in, Node*& smaller, Node*& larger, int pivot)
	{
 /* When this function terminates, the following holds:
    - smaller is the pointer to the head of a new singly linked list containing
      all elements of "in" that were less than or equal to the pivot.
    - larger is the pointer to the head of a new singly linked list containing
      all elements of "in" that were (strictly) larger than the pivot.
    - the linked list "in" no longer exists (should be set to NULL). */
	smaller = NULL;
	larger = NULL;
	
	if( in->next == NULL) // base case
	{
		if(in->value > pivot)
		{
			in->next = larger;
			larger = in;
			return;
		}
		else
		{
			in->next = smaller;
			smaller = in;
			return;
		}
	}
	else
	{
		split(in->next, smaller, larger, pivot); //recursion
		if( in->value > pivot)
		{
			in->next = larger;
			larger = in;
		}
		else
		{
			in->next = smaller;
			smaller = in;
		}
	}
	
	in = NULL;
	return;
	}

int main()
{
	//Test Code
	/*Node* head;
	Node n1, n2, n3, n4, n5, n6;
	
	head = &n1;
	
	n1.value = 1;
	n1.next = &n2;
	
	n2.value = 2;
	n2.next = &n3;
	
	n3.value = 3;
	n3.next = &n4;
	
	n4.value = 4;
	n4.next = &n5;
	
	n5.value = 5;
	n5.next = &n6;
	
	n6.value = 6;
	n6.next = NULL;
	
	Node* small = NULL;
	Node* large = NULL;
	
	split(head, small, large, 4);
	
	cout << "smaller" << endl;
	
	while( small -> next != NULL)
	{
		cout << small->value << endl;
		small = small->next;
	}
	cout << small->value << endl << endl;
	
	cout << "larger" << endl;
	
	while( large->next != NULL)
	{
		cout << large->value << endl;
		large = large-> next;
	}
	cout << large->value << endl;*/
	
	return 0;
}