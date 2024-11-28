# Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

# Output binary names
TARGET1 = wifi4
TARGET2 = wifi5
TARGET3 = wifi6

# Source files
SRC1 = problem1.cpp
SRC2 = problem2.cpp
SRC3 = problem3.cpp

# Object files
OBJ1 = $(SRC1:.cpp=.o)
OBJ2 = $(SRC2:.cpp=.o)
OBJ3 = $(SRC3:.cpp=.o)

# Header files (these are included directly, no need for object files for headers)
HEADERS = includes.h base.h constants.h

# Default target
all: $(TARGET1) $(TARGET2) $(TARGET3)

# Rule to build the first problem
$(TARGET1): $(OBJ1)
	$(CXX) $(OBJ1) -o $(TARGET1)

# Rule to build the second problem
$(TARGET2): $(OBJ2)
	$(CXX) $(OBJ2) -o $(TARGET2)

# Rule to build the third problem
$(TARGET3): $(OBJ3)
	$(CXX) $(OBJ3) -o $(TARGET3)

# Generic rule to compile .cpp files to .o files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and binaries
clean:
	rm -f $(OBJ1) $(OBJ2) $(OBJ3) $(TARGET1) $(TARGET2) $(TARGET3)

# Phony targets
.PHONY: all clean
