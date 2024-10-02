# Define the compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Define the source files
#SRCS = Book.cpp classFunction.cpp function.cpp Journals.cpp Library.cpp LibraryItem.cpp main.cpp PublicationRank.cpp User.cpp
SRCS = main.cpp
# Define the object files
OBJS = $(SRCS:.cpp=.o)

# Define the executable name
TARGET = library_system

# Default rule to build the executable
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
