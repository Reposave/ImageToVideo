#How to Run

In the terminal, type 'make' to compile.

'make clean' to remove binary files.

'make clear' to erase .pgm files from Frames folder.

to run, type the following:

```bash
./extrator img.pgm -t x1 y1 x2 y2 -s w h -w flag outputName
```
where x1, y1 is the starting coordinate
      x2, y2 is the ending coordinate
      w h width and height of screen
      flag some kind of special effect e.g: invert, none, reverse or revinvert
      outputName output of the sequence will be named "example-0000.pgm"

#Put pgm files in the Image folder
#The output sequences go into the Frames folder. If there is no Frames folder, an error or nothing will occur.

extractor.h is used to define destructor and constructor.

FrameSequence.h  is the header file which contains the declarations for methods and structs needed by FrameSequence.cpp. It contains the constructor and destrutor definition as well.

FrameSequence.cpp contains the definitions for the methods declared in the header file. FrameSequence is the class that creates the Array which stores the whole image and it's also the class that processes that array in order to create the imageSequence vector. This vector contains 2D arrays of frames to be printed. Results are placed in the frames folder.

extractor.cpp reads in the arguments passed by the user and creates the FrameSequence object.

.gitignore excludes binary files from the repository.