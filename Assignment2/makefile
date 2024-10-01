# Compiler
CXX = g++

# Source files for both programs
SRC_problem1 = problem1.cpp
SRC_problem2 = problem2.cpp
SRC_problem3 = problem3.cpp


# Object files
OBJ_problem1 = $(SRC_problem1:.cpp=.o)
OBJ_problem2 = $(SRC_problem2:.cpp=.o)
OBJ_problem3 = $(SRC_problem3:.cpp=.o)


# Binary names for problem1 and problem2
DEBUG_BIN_problem1 = problem1_debug
OPT_BIN_problem1 = problem1_opt

DEBUG_BIN_problem2 = problem2_debug
OPT_BIN_problem2 = problem2_opt


DEBUG_BIN_problem3 = problem3_debug
OPT_BIN_problem3 = problem3_opt


# Compiler flags
CXXFLAGS_DEBUG = -g -Wall
CXXFLAGS_OPT = -O2 -Wall

# Default target to build everything
all: $(DEBUG_BIN_problem1) $(OPT_BIN_problem1) $(DEBUG_BIN_problem2) $(OPT_BIN_problem2) $(DEBUG_BIN_problem3) $(OPT_BIN_problem3)

# Rule to build problem1 debug version
$(DEBUG_BIN_problem1): $(OBJ_problem1)
	$(CXX) $(CXXFLAGS_DEBUG) -o $@ $^

# Rule to build problem1 optimized version
$(OPT_BIN_problem1): $(OBJ_problem1)
	$(CXX) $(CXXFLAGS_OPT) -o $@ $^

# Rule to build problem2 debug version
$(DEBUG_BIN_problem2): $(OBJ_problem2)
	$(CXX) $(CXXFLAGS_DEBUG) -o $@ $^

# Rule to build problem2 optimized version
$(OPT_BIN_problem2): $(OBJ_problem2)
	$(CXX) $(CXXFLAGS_OPT) -o $@ $^

# Rule to build problem3 debug version
$(DEBUG_BIN_problem3): $(OBJ_problem3)
	$(CXX) $(CXXFLAGS_DEBUG) -o $@ $^

# Rule to build problem3 optimized version
$(OPT_BIN_problem3): $(OBJ_problem3)
	$(CXX) $(CXXFLAGS_OPT) -o $@ $^


# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS_DEBUG) -c $< -o $@

# Clean up the build
clean:
	rm -f $(OBJ_problem1) $(OBJ_problem2) $(OBJ_problem3) $(DEBUG_BIN_problem1) $(OPT_BIN_problem1) $(DEBUG_BIN_problem2) $(OPT_BIN_problem2) $(DEBUG_BIN_problem3) $(OPT_BIN_problem3)

# Phony targets
.PHONY: all clean
