#include "FrameSequence.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

int rows = 0;
int columns= 0;

int buffsize = 80;

int main (int argc, char *argv[])
{
	std::string filename = argv[1];
	
	std::string x1 = argv[3];
	//std::cout << x1 << std::endl;
	std::string y1 = argv[4];
	
	std::string x2 = argv[5];
	std::string y2 = argv[6];
	
	std::string width = argv[8];
	std::string height = argv[9];
	
	std::vector<std::string> w;
	
	for(int i = 11 ; i < argc; i=i+3){
		w.push_back(argv[i]);
		//std::cout << argv[i] << std::endl;
		w.push_back(argv[i+1]);
	}
	
	//Reading PGM File.
	std::string line;
	std::string previous; //Stores the previous line after an iteration.
	
   	std::ifstream infile("Images/"+filename);
	std::stringstream ss;
	
	char buff[buffsize];
	
	while(line.compare("255")!=0){ //Iterate through the non-binary data.	
		previous = line;
		getline(infile, line);
		
		
		//ss << buff;
		//ss >> line;
		//ss << "";
		
		std::cout << line << std::endl;
	}
	
	getline(infile, line);//Go to next line with Binary data.

	std::cout << previous << std::endl;
	
	ss.clear();
	ss << previous;
	
	ss >> rows;
	ss >> columns;
	
	//ss.getline(buff, 10,' ');
	
	//rows = atoi(buff);
	
	//ss.getline(buff, 10,' ');
	
	//columns = atoi(buff);
	
	std::cout << rows <<" "<< columns << " " << "columns" << std::endl;
	
	char array[rows][columns];
	
	ss << infile.rdbuf();
	
	for(int row = 0; row < rows; ++row){
		for (int col = 0; col < columns; ++col){
				ss >> array[row][col];
			}
    }
    
    infile.close();
    ss.clear();
    //print array
  for(int row = 0; row < rows; ++row) {
    for(int col = 0; col < columns; ++col) {
      std::cout << array[row][col] << " ";
    }
    std::cout << std::endl;
  }
  
}
void readFile(std::string file){
   //
   }
