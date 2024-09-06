<div id="header" align="center">
  <img src="https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExNXVxcmZoNjNjYThwdGxuaW55YzdhdWMwcG8ydndyODNoancyN3ByMSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/aLVLqlZvKW6XSYy3td/giphy.gif" width="250"/>
</div>




<h1 align="center" >
  Problem 1
</h1>

#### Pass all values to the program while execution
##### Since Provided range in CSV file is in between 2001 and 2029 so INPUT for the year should also be between the range OtherWise Error will be throwen with error message "Year our of Bound"
	g++ -c problem1.cpp
	g++ -g -o debug1 problem1.o
	g++ -O3 -o optimize1 problem1.o

	./debug1


<h1 align="center" >
  Problem 2
</h1>

#### Pass all values to the program while execution 
##### Since new LTCG is applied from 2024 so year of selling and purchese should be between 2024 and 2029 -> Output will be Profit with respect to new Long-term Capital Gains Tax (LTCG) and different in taxation scheme.
	g++ -c problem2.cpp
	g++ -g -o debug2 problem2.o
	g++ -O3 -o optimize2 problem2.o

	./debug2


#### To remove all files created
	rm -f debug2 debug1 optimize2 optimize1 problem2.o problem1.o
