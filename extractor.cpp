#include "FrameSequence.h"
#include "extractor.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>

int imageWidth = 0;
int imageHeight = 0;

unsigned char ** array = nullptr;

int x;
//std::cout << x << std::endl;
int y;
	
int x2;
int y2;
	
int width; //video width
int height; //video heigth

std::vector<std::string> w;

class extractor{
	//public:
		
};
		

int main (int argc, char *argv[])
{
	std::string filename = argv[1];
	
	x = std::stoi(argv[3]);
	//std::cout << x << std::endl;
	y = std::stoi(argv[4]);
	
	x2 = std::stoi(argv[5]);
	y2 = std::stoi(argv[6]);
	
	width = std::stoi(argv[8]); //video width
	height = std::stoi(argv[9]); //video heigth
	
	//std::vector<std::string> w;
	
	for(int i = 11 ; i < argc; i=i+3){
		w.push_back(argv[i]); //function name
		w.push_back(argv[i+1]); //output name
	}
	
	
	
	DLMARD001::FrameSequence myVideoFrames(x,y,x2,y2,width,height);
	
	
	myVideoFrames.BuildArray(filename);
    
  
    //print array
    //myVideoFrames.ExportOriginalImage(filename);
    
    for(std::vector<std::string>::size_type i = 0; i != w.size(); i=i+2) {
    	std::cout << w[i];
    	std::cout << w[i+1];
    	
    	if(w[i] == "invert"){
    		std::cout << "invert" << std::endl;
    		myVideoFrames.invertAddFrame();
    		myVideoFrames.noneExportFrames(w[i+1]);
    		
    	}else if(w[i] == "reverse"){
    		std::cout << "reverse"<< std::endl;
    		myVideoFrames.noneAddFrame();
    		myVideoFrames.reverseExportFrames(w[i+1]);
    		
    	}else if(w[i] == "none"){
    		std::cout << "none"<< std::endl;
    		myVideoFrames.noneAddFrame();
    		myVideoFrames.noneExportFrames(w[i+1]);
    		
    	}else if(w[i] == "revinvert"){
    		std::cout << "revinvert"<< std::endl;
    		myVideoFrames.invertAddFrame();
    		myVideoFrames.reverseExportFrames(w[i+1]);
    	}
	}
  	
  	
  	
}
