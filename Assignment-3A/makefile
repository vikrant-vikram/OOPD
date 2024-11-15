CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

SRCS = test.cpp station.cpp line.cpp plateform.cpp train.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = railway_system

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(EXEC)
