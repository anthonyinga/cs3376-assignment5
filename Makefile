#Makefile for "assignment5" C++ app
#CS 3376.502 April 7, 2017

CCc = g++ -c
CCo = g++ -o
clear = rm -rf *.o main

dynpipe: DynPipe.c 
	gcc -o dynpipe DynPipe.c -I

twoPipeTwoChil: TwoPipesTwoChildren.c
	gcc -o twoPipeTwoChil TwoPipesTwoChildren.cpp -I
twoPipeThreeChil: TwoPipesThreeChildren.c
	gcc -o twoPipeThreeChil TwoPipesThreeChildren.cpp -I
clean:
	$(clear)
