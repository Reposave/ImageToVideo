#include "FrameSequence.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>

void DLMARD001::FrameSequence::myMethod(int maxSpeed) {
	std::cout << "Hello World!";
	}

void DLMARD001::FrameSequence::AddFrame(unsigned char** frame) {
	DLMARD001::FrameSequence::imageSequence.push_back(frame);
}
DLMARD001::FrameSequence::FrameSequence(int x, int y, int x2, int y2, int width, int height){
	this->x=x;
	std::cout << "x is" << x << std::endl;
	this->y=y;
	std::cout << "y is" << y << std::endl;
	this->x2 = x2;
	std::cout << "x2 is" << x2 << std::endl;
	this->y2 = y2;
	std::cout << "y2 is" << y2 << std::endl;
	this->width = width;
	this->height = height;
}

void DLMARD001::FrameSequence::noneAddFrame(){
			unsigned char ** frame = nullptr;
			
			if((frame = new unsigned char*[height])!= nullptr){
				for(int i=0; i<height; ++i){
					if((frame[i] = new unsigned char[width]) == nullptr)
						{std::cerr << "Allocation error!"; break;}
				}
			}
			
			//frame's starting point for each frame.
			int fx = x;
			int fy = y;
			
			//set boundaries to avoid seg faults.
			if(y2 > imageHeight){
				y2 = imageHeight - height; //This part may cause problems if the code has to be continuously looped for different fucntions.
			}
			if(x2 > imageWidth){
				x2 = imageWidth - width;
			}
			std::cout << "Creating a video sequence." << std::endl;
			
			//Create video sequence.
			while(fx < x2 && fy < y2){
				std::cout << "hello" << std::endl;
					int v1 = 0;
					int h1 = 0;
					
					for(int i = fy; i< fy + height; i++){
						
						for(int j = fx; j< fx + width ; j++){
							
							frame[v1][h1] = static_cast<unsigned char>(array[i][j]);
							
							h1++;
							}
						std::cout << h1 << std::endl;
						h1 = 0;	
						v1++;	
					}
					std::cout << v1 << std::endl;
					v1 = 0;
					DLMARD001::FrameSequence::AddFrame(static_cast<unsigned char **>(frame));
					frame = nullptr;
					
					if((frame = new unsigned char*[height])!= nullptr){
						for(int i=0; i<height; ++i){
							if((frame[i] = new unsigned char[width]) == nullptr)
								{std::cerr << "Allocation error!"; break;}
						}
					}
					
					//next frame
					fx++;
					fy++;
			}
	
	}
	
void DLMARD001::FrameSequence::noneExportFrames(std::string outputName){

	for(std::vector<unsigned char **>::size_type i = 0; i != imageSequence.size(); i++) {
		FILE* outfile;
		
		std::string out = "Frames/" + std::to_string(i) +"out_" + outputName;
		outfile = fopen(out.c_str(), "wb");
		
		fprintf(outfile, "P5\n"); 
		fprintf(outfile,"# Created using extractor program.\n");
		fprintf(outfile, "%d %d\n", width, height); 
		fprintf(outfile, "255\n"); 


	  for(int row = 0; row < height; row++) {
		for(int col = 0; col < width; col++) {
				fwrite(&imageSequence[i][row][col], 1,1,outfile);
		  }
		}
	}
}

void DLMARD001::FrameSequence::ExportOriginalImage(std::string filename){
	FILE* outfile;
    
    std::string out = "Images/out_"+filename;
    outfile = fopen(out.c_str(), "wb");
    
    fprintf(outfile, "P5\n"); 
    fprintf(outfile,"# Created using extractor program.\n");
    fprintf(outfile, "%d %d\n", imageWidth, imageHeight); 
    fprintf(outfile, "255\n"); 

    
  for(int row = 0; row < imageHeight; row++) {
    for(int col = 0; col < imageWidth; col++) {
    		fwrite(&array[row][col], 1,1,outfile);
      }
    }

}
void DLMARD001::FrameSequence::BuildArray(std::string filename){

	int buffsize = 80;
	
	//Reading PGM Header info.
	std::string line;
	std::string previous; //Stores the previous line after an iteration.
	
   	std::ifstream infile("Images/"+filename,std::ios_base::binary);
	std::stringstream ss;
	
	char buff[buffsize];
	
	while(line.compare("255")!=0){ //Iterate through the non-binary data.	
		previous = line;
		getline(infile, line);
		
		std::cout << line << std::endl;
	}
	
	getline(infile, line);//Go to next line with Binary data.

	//std::cout << previous << std::endl;
	
	ss.clear();
	ss << previous;
	
	ss >> imageWidth;
	ss >> imageHeight;
	
	std::cout << imageWidth <<" "<< imageHeight << " " << "columns" << std::endl;
	
	if((array = new unsigned char*[imageHeight])!= nullptr){
		for(int i=0; i<imageHeight; ++i){
			if((array[i] = new unsigned char[imageWidth]) == nullptr)
				{std::cerr << "Allocation error!"; break;}
		}
	}
	
	//ss << infile.rdbuf();
	
	char b;
	
	//Populate the array with the whole image data.
	for(int row = 0; row < imageHeight; row++){
		for (int col = 0; col < imageWidth; col++){
				infile.get(b);
				//ss >> array[row][col];
				array[row][col] = b;
				}
			}
			
	infile.close();
}

DLMARD001::FrameSequence::FrameSequence(void){}

DLMARD001::FrameSequence::~FrameSequence(){

	for(int i =0; i< imageHeight; ++i)
  	{ delete [] array[i]; }
  	
  	delete [] array;
  	
	for(std::vector<unsigned char **>::size_type i = 0; i != imageSequence.size(); i++) {
		unsigned char** m = imageSequence[i];
		for(int j =0; j< height; ++j)
		  	{ delete [] m[j]; }
		  	
		  	delete [] m;
	}
	
}


