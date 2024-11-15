CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

SRCS = main.cpp Station.cpp Line.cpp Platform.cpp Train.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = railway_system

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(EXEC)
