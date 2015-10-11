#include <iostream>
#include <map>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cstring>
#include "stackint.h"

using namespace std; 

void RemoveWhiteSpace( string& line) {
	for( int i = 0; i < line.length(); i++) {
		if( line.substr(i,1) == " ") {
			line.erase( i, 1);
			i--;
		}
	}
}

void AddtoStack( StackInt& stack, string add) {
	if( add == "") {
		return;
	} else if( add == "(" ) {
		//cout << "pushing (" << endl; //debug
		stack.push(-1);
	} else if( add == "~" ) {
		//cout << "pushing ~" << endl; //debug
		stack.push(-2);
	} else if ( add == "&" ) {
		//cout << "pushing &" << endl; //debug
		stack.push(-3);
	} else if ( add == "|" ) {
		//cout << "pushing |" << endl; //debug
		stack.push(-4);
	} else if( add == "0"){
		stack.push(0);
	} else if( add == "1") {
		stack.push(1);
	}
}

bool isNumber( int check) {
	if( check >= 0) {
		return true;
	} else {
		return false;
	}
}

int main(int argc, char* argv[]) {
	if( argc !=3) {
		cout << "Incorrect Input" << endl;
		return -1;
	}
	//initializes many things
	ifstream ifile(argv[1]);
	ifstream varfile(argv[2]);
	string current;
	stringstream line;
	string name;
	string boolvalue;
	bool flag = false;
	bool flag2 = false;
	map<string,int> vars;
	map<string,int>::iterator it;
	const int OPEN_PAREN = -1;
	const int NOT = -2;
	const int AND = -3;
	const int OR = -4;
	
	bool flag_and = false, flag_or = false; //flas for use in later loops
	
	//reads in varfile to map
	while(getline( varfile, current )) {
		if( varfile.fail()) {
			break;
		}
		line << current; 
		line >> name >> boolvalue;
		
		if( boolvalue == "T") {
			vars.insert(make_pair( name, 1));
		} else {
			vars.insert(make_pair( name, 0));
		}
		line.clear();
		current = "";
	}
	varfile.close();

// Reads out vars map	
/*for(it = vars.begin(); 
      it != vars.end(); 
      ++it)
    {
      cout << it->first << " " << it->second << endl;
    }*/
	// steps through in file
	while( getline(ifile, current)) {
		if(ifile.fail()) {
			break;
		}
		RemoveWhiteSpace(current); //removes whitespace from line
		if( current == "") { //if empty line, goes to next line immedietly 
			continue;
		}
		//cout << "working on line: " << current << endl; // debug
		
		//checks to ensure same number of open and close parentheses
		int counter_open = 0, counter_close = 0;
		for(unsigned int i = 0; i < current.size(); i ++) {
			if (current[i] == '(') {
				counter_open++;
			} else if (current[i] == ')' ) {
				counter_close++;
			}
		}
		if( counter_open != counter_close ) {
			cout << "Malformed" << endl;
			continue;
		}
		
		StackInt stack;
		string currentName = ""; // holds current integer variable
		
		while(current.size() != 0) {
			if( current[0] == ')' ) { // close parentheses found. evaluates bool expression. 
				//cout << "found )" << endl; //debug
				if( currentName != "") { // if current value in currentName, adds to stack
					it = vars.find(currentName);
					if(it != vars.end()) {
						int value_to_push = it->second;
						if( value_to_push == 0) {
							stack.push(0);
						} else {
							stack.push(1);
						}
						currentName = "";
					} else {
						cout << "Unknown Variable 3: " << currentName << endl;
						flag2 = true;
						break;
					}
				}
				
				current.erase(0,1);
				while( stack.top() != OPEN_PAREN  ) { // pops and evaluates stack until (
					int top = stack.top();
					stack.pop();
					if(stack.empty()) { // no opening parentheses 
							cout << "Malformed" << endl;
							flag2 = true;
							break;
						
					} else if( stack.top() == NOT) {
						if(top) {
							top = 0;
							stack.pop();
							stack.push(top);
						} else {
							top = 1;
							stack.pop();
							stack.push(top);
						}
					} else if( stack.top() == AND ) {
						flag_and = true;
						if( flag_or ) {
							flag_or = false;
							cout << "Malformed" << endl;
							flag2 = true;
							break;
						}
						
						stack.pop();
						if(!isNumber(stack.top())) {
							cout << "Malformed" << endl;
							flag = true;
							flag2 = true;
							break;
						}
						if( top && stack.top()) {
							stack.pop();
							stack.push(1);
						} else {
							stack.pop();
							stack.push(0);
						}
					} else if(stack.top() == OR) {
						flag_or = true;
						if( flag_and ) {
							flag_and = false;
							cout << "Malformed" << endl;
							flag2 = true;
							break;
						}
						stack.pop();
						if(!isNumber(stack.top())) {
							cout << "Malformed" << endl;
							flag = true;
							flag2= true;
							break;
						}
						if( top || stack.top() ) {
							stack.pop();
							stack.push(1);
						} else {
							stack.pop();
							stack.push(0);
						}
					} else if(stack.top() == OPEN_PAREN) {
						stack.pop();
						stack.push(top);
						break;
					}
				}
				if(flag) {
					flag = false;
					break;
				}
				
				flag_and = false;
				flag_or = false;
				
				int top = stack.top();
				stack.pop();
				if(stack.top() == NOT) { // evaluates ~ before parentheses
					stack.pop();
					if(top) {
						stack.push(0);
					} else {
						stack.push(1);
					}
				}
			} else if( (int)current[0] >= 48 && (int)current[0] <=57 ) { // if current[0] is an int (0-9)
				currentName.append(current.substr(0,1));
				current.erase(0,1);
				if( current.size() == 1) {
					it = vars.find(currentName);
					if(it != vars.end()) {
						int value_to_push = it->second;
						if( value_to_push == 0) {
							stack.push(0);
						} else {
							stack.push(1);
						}
						currentName = "";
					} else {
						cout << "Unknown Variable 1: " << currentName << endl;
						flag2 = true;
						break;
					}
				}
			} else { // if current[0] is a symbol(~,&,|)
				if( currentName.size() > 0 ) { // adds currentName to stack
					it = vars.find(currentName);
					if(it != vars.end()) {
						int value_to_push = it->second;
						if( value_to_push == 0) {
							stack.push(0);
						} else {
							stack.push(1);
						}
					currentName = "";
					} else {
						cout << "Unknown Variable 2: " << currentName << endl;
						flag2 = true;
						break;
					}
				}
				AddtoStack(stack, current.substr(0,1));
				current.erase(0,1);	
				
		}
	
		}
		if( flag2) {
			flag2 = false;
			continue;
		}
		flag_and = false;
		flag_or = false;
		
		int top = stack.top();
		stack.pop();
		while(!stack.empty()) { // finds/evaluates all initial ~s
			if(stack.top() == NOT) {
				stack.pop();
				if( top == 1) {
					top = 0;
				} else {
					top = 1;
				}
			} else {
				stack.pop();
			}
		}
		if(top) { //reads out result
			cout << "T" <<endl;
		} else {
			cout << "F" << endl;
		}
	}
	ifile.close();
	return 0;
}