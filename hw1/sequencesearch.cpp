#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	ifstream ifile(argv[1]);
	stringstream line;
	string lineString;

	// Gets first line (number of data lines). Puts into numLines
	getline( ifile, lineString);

	int numLines;
	line << lineString;
	line >> numLines;
	line.clear();

	double** dataLines = new double*[numLines]; // where data will be saved

	// Gets second line (lengths of every data line). Puts into array "lineLength"
	getline( ifile, lineString);
	int* lineLength = new int[numLines];
	stringstream newLine;
	// reads line into stringstream
	for(int i = 0; i < numLines; i++)
	{
		newLine << lineString << " ";
	}
	// reads stringstream into array
	for(int i = 0; i < numLines; i++)
	{
		newLine >> lineLength[i];
		newLine.clear();
	}

	//Reads in Data
	for(int i = 0; i < numLines; i++)
	{
		line.clear();
		line.str("");
		lineString = "";
		getline( ifile, lineString);
		double* currentLine  = new double[lineLength[i]];
		for(int j = 0; j <lineLength[i]; j++)
		{
			line << lineString;
			line >> currentLine[j];
			lineString = "";
		}
		dataLines[i] = currentLine;
	}
	ifile.close();

	// Processes Data
	int bigSequence = 0, currentSequence = 0;

	for(int i = 0; i < numLines; i++)
	{
		currentSequence = 0;
		//Goes accross row
		for(int j = 0; j < lineLength[i] - 1; j++)
		{
			if(dataLines[i][j] < dataLines[i][j+1])
			{
				currentSequence++;
			}
			else
			{
				currentSequence = 0;
			}

			if(currentSequence > bigSequence)
			{
				bigSequence = currentSequence;
			}
		}
		currentSequence = 0;
		// Now does it backwards
		for(int j = 0; j < lineLength[i] - 1; j++)
		{
			if(dataLines[i][j] > dataLines[i][j+1])
			{
				currentSequence++;
			}
			else
			{
				currentSequence = 0;
			}

			if(currentSequence > bigSequence)
			{
				bigSequence = currentSequence;
			}
		}
		currentSequence = 0;
	}
	
	//Goes down collumn 
	
	//Finds max line lengths
	
	int maxLength = 0;
	
	for(int i = 0; i < numLines; i++)
	{
		if (lineLength[i] > maxLength)
		{
			maxLength = lineLength[i];
		}
	}
	//down
	for(int i = 0; i < maxLength; i++)
	{
		currentSequence = 0;
		for(int j = 1; j < numLines; j++)
		{
			if(i < lineLength[j] && i < lineLength[j-1] )
				{
					if(dataLines[j][i] > dataLines[j-1][i])
					{
						currentSequence++;
					}
					else
					{
						currentSequence = 0;	
					}
				}
			else
			{
				currentSequence = 0;
			}
			
			if(currentSequence > bigSequence)
				{
					bigSequence = currentSequence;
				}
		}
	}
		//up
	for(int i = 0; i < maxLength; i++)
	{
		for(int j = 1; j < numLines; j++)
		{
			if(i < lineLength[j] && i < lineLength[j-1] && dataLines[j][i] < dataLines[j-1][i])
			{
				currentSequence++;
			}
			else
			{
				currentSequence = 0;
			}
			if(currentSequence > bigSequence)
			{
				bigSequence = currentSequence;
			}
		}
		currentSequence = 0;
	}
	
	// Prints output
	ofstream ofile(argv[2]);
	ofile << bigSequence+1; // accounts for starting number of 1
	ofile.close();
	
	for(int i = 0; i < numLines; i++)
	{
		delete [] dataLines[i];
	}
	//delete currentLine;
	delete [] lineLength;
	delete [] dataLines;
	return 0;
}