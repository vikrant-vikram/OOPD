<div id="header" align="center">
 <iframe src="https://giphy.com/embed/VePtB3roynxfLYicuV" width="480" height="480" style="" frameBorder="0" class="giphy-embed" allowFullScreen></iframe>
</div>

<h1 align="center" >
  Problem 1
</h1>

# Pass all values to the program while execution
	g++ -c problem1.cpp
	g++ -g -o debug1 problem1.o
	g++ -O3 -o optimize1 problem1.o

	./debug1


<h1 align="center" >
  Problem 2
</h1>

# Pass all values to the program while execution Since new LTCG is applied from 2024 so year of selling and purchese should be between 2024 and 2029
	g++ -c problem2.cpp
	g++ -g -o debug2 problem2.o
	g++ -O3 -o optimize2 problem2.o

	./debug2


# To remove all files created
	rm -f debug2 debug1 optimize2 optimize1 problem2.o problem1.o
