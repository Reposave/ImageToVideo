#include "FrameSequence.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>

int widths = 0;
int heights = 0;

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
	
   	std::ifstream infile("Images/"+filename,std::ios_base::binary);
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

	//std::cout << previous << std::endl;
	
	ss.clear();
	ss << previous;
	
	ss >> widths;
	ss >> heights;
	
	//ss.getline(buff, 10,' ');
	
	//rows = atoi(buff);
	
	//ss.getline(buff, 10,' ');
	
	//columns = atoi(buff);
	
	std::cout << widths <<" "<< heights << " " << "columns" << std::endl;
	
	unsigned char array[heights][widths];
	
	//ss << infile.rdbuf();
	
	char b;
	
	for(int row = 0; row < heights; row++){
		for (int col = 0; col < widths; col++){
				infile.get(b);
				//ss >> array[row][col];
				array[row][col] = b;
				}
			}
    
    infile.close();
    //print array
    
    //std::ofstream outfile("Images/out_"+filename,std::ios_base::binary);
    FILE* outfile;
    
    outfile = fopen("ouy.pgm", "wb");
    
    fprintf(outfile, "P5\n"); 
    fprintf(outfile,"# Created using extractor program.\n");
    fprintf(outfile, "%d %d\n", widths, heights); 
    fprintf(outfile, "255\n"); 
    
    /*outfile << "P5\n" << "# Created using extractor program.\n" << rows << " " << columns << "\n" << "255 \n";*/ 
    
  for(int row = 0; row < heights; row++) {
    for(int col = 0; col < widths; col++) {
    		fwrite(&array[row][col], 1,1,outfile);
      //outfile.write(reinterpret_cast<char*> (array[row][col]),rows*columns*sizeof(unsigned char));
      }
      
      //fwrite("\n",1,1,outfile);
    }
  
  
}
void readFile(std::string file){
   //
   }
/*void Invert(unsigned char * Arr){
	for(int row = 0; row < rows; ++row){
		for (int col = 0; col < columns; ++col){
				Arr[row][col] = 255 - *Arr[row][col];
				
			}
    }
}*/
