# Q1
# take user input and pass to functions then execute the following using GitBash

test :
# Question 1
	g++ -c problem1.cpp
	g++ -g -o debug1 problem1.o
	g++ -O3 -o optimize1 problem1.o

	./debug1


# Q2
# take user input and pass to functions then execute the following using GitBash
# At last comparison is done b/w republican  & dictatorial era


# Question 2
	g++ -c problem2.cpp
	g++ -g -o debug2 problem2.o
	g++ -O3 -o optimize2 problem2.o

	./debug2


# To remove all files created
clean:
	rm -f debug2 debug1 optimize2 optimize1 problem2.o problem1.o
