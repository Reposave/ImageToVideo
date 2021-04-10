#include "FrameSequence.h"
#include <iostream>
#include <vector>



void DLMARD001::FrameSequence::myMethod(int maxSpeed) {
	std::cout << "Hello World!";
	}

void DLMARD001::FrameSequence::AddFrame(unsigned char** frame) {
	DLMARD001::FrameSequence::imageSequence.push_back(frame);
}

DLMARD001::FrameSequence::FrameSequence(void){}
DLMARD001::FrameSequence::~FrameSequence(){}


