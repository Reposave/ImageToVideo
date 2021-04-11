#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>

#ifndef _FRAMESEQUENCE
#define _FRAMESEQUENCE

namespace DLMARD001{
	class FrameSequence{
	
	public:
		std::vector<unsigned char** > imageSequence;
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
		
		void myMethod(int maxSpeed);
		void AddFrame(unsigned char** frame);
		void noneAddFrame();
		void noneExportFrames(std::string outputName);
		void ExportOriginalImage(std::string filename);
		void BuildArray(std::string filename);
		
		FrameSequence(int x, int y, int x2, int y2, int width, int height);
		FrameSequence(void);
		~FrameSequence();
		
		
	};
}        

#endif
