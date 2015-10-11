#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cstdlib>

using namespace std;

void makePalindromeHelper(ostream& ofile, string options, int len, int size, string pal, int numOptions)
{
  if(len == 0) // base case 
  {
    ofile << pal<< endl;
    for(int i = 0; i < numOptions; i++)
    {
      string str = options.substr(i,1);
      makePalindromeHelper(ofile, options, 1, size, str, numOptions); // calls recursive function for each option
    }
  }
  else if(len == 1) // goes here second
  {
    ofile << pal << endl;
    for(int i = 0; i < numOptions; i++)
    {
      string str = options.substr(i,1);
      makePalindromeHelper(ofile, options, len+2, size,  str + pal + str, numOptions);// creates/calls function for size 3
    }
    makePalindromeHelper(ofile, options, 2, size, pal+pal, numOptions);// creates/calls function for size 2
  }
  else if( len < size-1 && len > 1) //until reaches max size
  {
    ofile << pal << endl;
    for(int i = 0; i < numOptions; i++)
    {
      string str = options.substr(i,1);
      makePalindromeHelper(ofile, options, len+2, size, str + pal + str, numOptions);
    }
  }
  else //when reaches max size
  {
    ofile << pal << endl;
  }
  return;
}

void makePalindromes(ostream& ofile, char* options, int size)
{
  string pal = "";
  int numOptions = 0;
  while( options[numOptions] != 0 ) // finds needed numOptions
  {
    numOptions++;
  }
  string str(options);
  makePalindromeHelper(ofile, str, 0, size, pal, numOptions); // calls helper function
  return;
}


int main(int argc, char* argv[])
{
  if(argc < 4){
    cerr << "Please provide an output file, a string of characters, and the max length" << endl;
    return 1;
  }

  ofstream ofile(argv[1]);
  int len = atoi(argv[3]);
  makePalindromes(ofile, argv[2], len);
  ofile.close();
  return 0;
}

