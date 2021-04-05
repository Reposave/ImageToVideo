# This is a Makefile comment
CC=g++         # the compiler
LIBS=-lm       # the libraries we will ref

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
   
# copies/moves the relevant binaries and/or libraries to the correct folders   
install:
  
	@mv extractor ~/bin