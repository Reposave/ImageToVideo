#include <string>
#include <vector>

#ifndef _FRAMESEQUENCE
#define _FRAMESEQUENCE

namespace DLMARD001{
	class FrameSequence{
	
	
	
	public:
		std::vector<unsigned char** > imageSequence;
	
		void myMethod(int maxSpeed);
		void AddFrame(unsigned char** frame);
		
		FrameSequence(void);
		~FrameSequence();
		
		
	};
}        

#endif
