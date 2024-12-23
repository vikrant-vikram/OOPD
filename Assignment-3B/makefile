# Compiler settings
CLANGXX = clang++
GXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS_SQLITE = -lsqlite3

# Target executables
TARGET_CLANG = program2_debug
TARGET_GCC = program1_debug

# Source files
SRC_CLANG = program2.cpp
SRC_GCC = program1.cpp

# Directories for Boost or other libraries (if needed)
#BOOST_INCLUDE_DIR = /path/to/boost/include
#BOOST_LIB_DIR = /path/to/boost/lib

# Default target (build both programs)
all: $(TARGET_CLANG) $(TARGET_GCC)

# Rule for compiling and linking with clang++ (SQLite3)
$(TARGET_CLANG): $(SRC_CLANG)
	$(CLANGXX) $(CXXFLAGS) -o $(TARGET_CLANG) $(SRC_CLANG) $(LDFLAGS_SQLITE)

# Rule for compiling and linking with g++
$(TARGET_GCC): $(SRC_GCC)
	$(GXX) $(CXXFLAGS) -o $(TARGET_GCC) $(SRC_GCC)

# Clean rule to remove generated files
clean:
	rm -f $(TARGET_CLANG) $(TARGET_GCC)

# Phony targets (not actual files)
.PHONY: all clean
