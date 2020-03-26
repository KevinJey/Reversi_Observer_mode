main: main.o cell.o grid.o textdisplay.o 
	g++ main.o cell.o grid.o textdisplay.o -std=c++14 -o main
cell.o:
	g++ -c cell.cpp 
grid.o:
	g++ -c grid.cpp
textdisplay.o:
	g++ -c textdisplay.cpp
main.o:
	g++ -c main.cpp

clean:
	rm -rf *.o




