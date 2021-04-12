#include "FrameSequence.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <iomanip>
#include <cmath>

void DLMARD001::FrameSequence::myMethod(int maxSpeed) {
	std::cout << "Hello World!";
	}

void DLMARD001::FrameSequence::AddFrame(unsigned char** frame) {
	DLMARD001::FrameSequence::imageSequence.push_back(frame);
}
DLMARD001::FrameSequence::FrameSequence(int x, int y, int x2, int y2, int width, int height){
	this->x=x;
	this->y=y;
	this->x2 = x2;
	this->y2 = y2;
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
			
			
			//set boundaries to avoid seg faults.
			if(y2 + height > imageHeight){
				y2 = imageHeight - height;
			}
			if(x2 + width > imageWidth){
				x2 = imageWidth - width;
			}
			if(y2<0){
				y2 = 0;
			}
			if(x2<0){
				x2 = 0;
			}
			
			if(y + height > imageHeight){
				y = imageHeight - height;
			}
			if(x + width > imageWidth){
				x = imageWidth - width;
			}
			if(y<0){
				y = 0;
			}
			if(x<0){
				x = 0;
			}
			
			double fx = x;
			double fy = y;
			
			int rfx = x;
			int rfy = y;
			
			bool addx = true;
			bool addy = true;
			
			
			double g = 1;
			
			if((x2-x) != 0){
				std::cout << y2 << " " << y << " " << x2 << " " << x;
				g = (double)((y2 - y))/((x2 - x));
				std::cout << g <<std::endl;
			}else{
				addx = false;
			}
			
			if((y2-y)==0){
				addy = false;
			}
			
			bool yo = false;
			
			if (std::fabs(g) < 1.0){
				yo= true;
			}
			
			std::cout << "Creating a video sequence." << std::endl;
			
			//Allows the video to move vertically only or horizontally only.
			
			
			//Create video sequence.
			while(fx != x2 || fy != y2 ){
			
			//Check if end-point has been passed.
				if(x2<x){
				//std::cout << "break fx<x2";
					//std::cout << x2 << " " << x << " "<< fx << std::endl;
					if(fx < x2){
					//std::cout << x2 << " " << x << " "<< fx;
						break;
					}
				}else{
				//std::cout << "break fx>x2";
					if(fx>x2){
						break;
					}
				}
				
				if(y2<y){
				//std::cout << "break fy<y2";
				//std::cout << y2 << " " << y << " "<< fy << std::endl;
					if(fy<y2){
						break;
					}
				}else{
				//std::cout << "break fy>y2";
				//std::cout << y2 << " " << y << " "<< fy << std::endl;
					if(fy>y2){
						break;
					}
				}
				
					int v1 = 0; 
					int h1 = 0;
					
					for(int i = rfy; i< rfy + height; i++){
						
						for(int j = rfx; j< rfx + width ; j++){
							
							frame[v1][h1] = static_cast<unsigned char>(array[i][j]);
							
							h1++;
							}
						h1 = 0;	
						v1++;	
					}
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
					if(!yo){
						if(addx){
							if(x2<x){
								fx--;
								rfx--;
							}else{
								fx++;
								rfx++;
							}
						}
						
						if(addy){
							if(y2<y){
									fy = fy - std::fabs(g);
									rfy = std::round(fy);
								}else{
									fy = fy + std::fabs(g);
									rfy = std::round(fy);
								}
							}
					}else{
					
						if(addx){
							if(x2<x){
								fx = fx - (1/std::fabs(g));
								rfx = std::round(fx);
							}else{
								fx = fx + (1/std::fabs(g));
								rfx = std::round(fx);
							}
						}
						if(addy){
							if(y2<y){
								fy--;
								rfy--;
								}
							else{
								fy++;
								rfy++;	
								}
							}
						}
			}
	
	}
	
	
void DLMARD001::FrameSequence::noneExportFrames(std::string outputName){

	std::stringstream ss;
	std::string number;
	
	for(std::vector<unsigned char **>::size_type i = 0; i != imageSequence.size(); i++) {
		FILE* outfile;
		
		ss << std::setw(4) << std::setfill('0') << i;
		ss >> number;
		
		std::string out = "Frames/" + outputName + "-" + number+ ".pgm";
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
		
		ss.clear();
		
	}
	
	for(std::vector<unsigned char **>::size_type i = 0; i != imageSequence.size(); i++) {
		unsigned char** m = imageSequence[i];
		for(int j =0; j< height; ++j)
		  	{ delete [] m[j]; }
		  	
		  	delete [] m;
	}
	imageSequence.clear();
}
void DLMARD001::FrameSequence::invertAddFrame(){
			unsigned char ** frame = nullptr;
			
			if((frame = new unsigned char*[height])!= nullptr){
				for(int i=0; i<height; ++i){
					if((frame[i] = new unsigned char[width]) == nullptr)
						{std::cerr << "Allocation error!"; break;}
				}
			}
			
			//frame's starting point for each frame.
			
			
			//set boundaries to avoid seg faults.
			if(y2 + height > imageHeight){
				y2 = imageHeight - height;
			}
			if(x2 + width > imageWidth){
				x2 = imageWidth - width;
			}
			if(y2<0){
				y2 = 0;
			}
			if(x2<0){
				x2 = 0;
			}
			
			if(y + height > imageHeight){
				y = imageHeight - height;
			}
			if(x + width > imageWidth){
				x = imageWidth - width;
			}
			if(y<0){
				y = 0;
			}
			if(x<0){
				x = 0;
			}
			
			double fx = x;
			double fy = y;
			
			int rfx = x;
			int rfy = y;
			
			bool addx = true;
			bool addy = true;
			
			
			double g = 1;
			
			if((x2-x) != 0){
				g = (double)((y2 - y))/((x2 - x));
			}else{
				addx = false;
			}
			
			if((y2-y)==0){
				addy = false;
			}
			
			bool yo = false;
			
			if (std::fabs(g) < 1.0){
				yo= true;
			}
			
			std::cout << "Creating a video sequence." << std::endl;
			
			//Allows the video to move vertically only or horizontally only.
			
			
			//Create video sequence.
			while(fx != x2 || fy != y2 ){
			
			//Check if end-point has been passed.
				if(x2<x){
					if(fx < x2){
						break;
					}
				}else{
					if(fx>x2){
						break;
					}
				}
				
				if(y2<y){
					if(fy<y2){
						break;
					}
				}else{
					if(fy>y2){
						break;
					}
				}
				
					int v1 = 0; 
					int h1 = 0;
					
					for(int i = rfy; i< rfy + height; i++){
						
						for(int j = rfx; j< rfx + width ; j++){
							
							frame[v1][h1] = 255 - static_cast<unsigned char>(array[i][j]);
							
							h1++;
							}
						h1 = 0;	
						v1++;	
					}
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
					if(!yo){
						if(addx){
							if(x2<x){
								fx--;
								rfx--;
							}else{
								fx++;
								rfx++;
							}
						}
						
						if(addy){
							if(y2<y){
									fy = fy - std::fabs(g);
									rfy = std::round(fy);
								}else{
									fy = fy + std::fabs(g);
									rfy = std::round(fy);
								}
							}
					}else{
					
						if(addx){
							if(x2<x){
								fx = fx - (1/std::fabs(g));
								rfx = std::round(fx);
							}else{
								fx = fx + (1/std::fabs(g));
								rfx = std::round(fx);
							}
						}
						if(addy){
							if(y2<y){
								fy--;
								rfy--;
								}
							else{
								fy++;
								rfy++;	
								}
							}
						}
			}
	}

void DLMARD001::FrameSequence::reverseExportFrames(std::string outputName){

	std::stringstream ss;
	std::string number;
	
	int s = 0;
	for(int i = imageSequence.size() - 1 ; i >= 0; i--) {
		
		FILE* outfile;
		
		ss << std::setw(4) << std::setfill('0') << s;
		ss >> number;
		
		std::string out = "Frames/" + outputName + "-" + number+ ".pgm";
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
		s++;
		ss.clear();
		
	}
	for(std::vector<unsigned char **>::size_type i = 0; i != imageSequence.size(); i++) {
		unsigned char** m = imageSequence[i];
		for(int j =0; j< height; ++j)
		  	{ delete [] m[j]; }
		  	
		  	delete [] m;
	}
	imageSequence.clear();
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
		
		//std::cout << line << std::endl;
	}
	
	getline(infile, line);//Go to next line with Binary data.

	//std::cout << previous << std::endl;
	
	ss.clear();
	ss << previous;
	
	ss >> imageWidth;
	ss >> imageHeight;
	
	//std::cout << imageWidth <<" "<< imageHeight << " " << "columns" << std::endl;
	
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


