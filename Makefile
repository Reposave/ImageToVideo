# This is a Makefile comment
CC=g++         # the compiler
LIBS=-lm       # the libraries we will ref
MANDIR=~/CSC3022F/Assignment2/Frames

# Need object files tag.o and tagDriver.o to create exe tagENUM 
extractor: FrameSequence.o extractor.o
	$(CC) FrameSequence.o extractor.o -o extractor $(LIBS)

# Implicit pattern rule for compiling object files
%.o : %.cpp   # $< is the first dependancy and $@ is the target
	$(CC) -c $< -o $@
   
# other rules; invoked by make clean etc 

# deletes all the object code files
clean:
	@rm -f *.o
	@rm extractor

clear:
	rm ~/CSC3022F/Assignment2/Frames/*.pgm
   
# copies/moves the relevant binaries and/or libraries to the correct folders   
install:
  
	@mv extractor ~/bin
	
run:
	./extractor larger_image.pgm -t 0 10 5000 5000 -s 640 480 -w invert invseq -w none sequence2

run1:
	./extractor sloan_image.pgm -t 0 10 3 13 -s 640 480 -w invert invseq -w none sequence2
	
run2:
	./extractor sloan_image.pgm -t 0 10 5000 5000 -s 640 480 -w invert invseq -w none sequence2

run3:
	./extractor sloan_image.pgm -t 0 10 1 11 -s 640 480 -w invert invseq -w none sequence2
	
reverseSmall:
	./extractor sloan_image.pgm -t 0 10 3 13 -s 640 480 -w reverse sequence3

reverseLarge:
	./extractor sloan_image.pgm -t 0 10 400 300 -s 640 480 -w reverse sequence3
	
revinvert:
	./extractor sloan_image.pgm -t 0 10 4 14 -s 640 480 -w revinvert revinv -w none sequence2
	
revinvertLarge:
	./extractor sloan_image.pgm -t 0 10 400 300 -s 1280 720 -w revinvert revinv -w none sequence2
