test :
# Question 1
	g++ -c problem1.cpp
	g++ -g -o debug1 problem1.o
	g++ -O3 -o optimize1 problem1.o

	./debug1


# Question 2
	g++ -c problem2.cpp
	g++ -g -o debug2 problem2.o
	g++ -O3 -o optimize2 problem2.o

	./debug2

.PHONY: clean

clean:
	rm -f debug2 debug1 optimize2 optimize1 problem2.o problem1.o
