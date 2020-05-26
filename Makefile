all:
	g++ -c Cell.cxx
	g++ main.cxx Cell.o -l SDL2-2.0 -o gameoflife
