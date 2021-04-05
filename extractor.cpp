#include "FrameSequence.h"
#include <string>
#include <vector>
#include <iostream>

int main (int argc, char *argv[])
{
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
}
