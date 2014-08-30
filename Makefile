CXX:= g++
LDFLAGS := -lpthread 
INCPATHS := -I ext
LIBPATHS := -L ext
CXXFLAGS :=-c -Wall -std=c++11 -g $(INCPATHS)
# Sources are all .cpp files in this dir
SRCS :=         $(wildcard *.cpp)
# Object files are everything in $SRCS, with the .cpp replaced by a .o
OBJS :=         $(patsubst %.cpp, %.o, $(SRCS))
TARGET :=       spider

# Default target makes the executable
default :       $(TARGET)

# Make every .o file require it's corresponding .cpp file
# For each such file, call the compiler with the specified flags
# Use the requisite ($<) as input (the .cpp file)
# Use the target name ($@) as the output file name (the .o file)
%.o : %.cpp %.h
	$(CXX) $(CXXFLAGS) $< -o $@

# Make the executable require all the object files
# Use all the requisites ($^), as input files (the .o files) for the linker
# Output file is $TARGET, which is executable_name
$(TARGET) :     $(OBJS)
	$(CXX) $(LIBPATHS) $(LDFLAGS) $^ -o $(TARGET)

# Simple clean up target
clean :
	rm -f $(OBJS) $(TARGET) *~

redo:
	make -s clean
	make -s -j4
	./$(TARGET)
	