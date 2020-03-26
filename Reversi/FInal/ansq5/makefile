main: main.o cell.o grid.o textdisplay.o window.o
	g++ window.o main.o cell.o grid.o textdisplay.o -std=c++14 -o main `pkg-config --cflags --libs x11`

cell.o:
	g++ -c cell.cpp 
grid.o:
	g++ -c grid.cpp
textdisplay.o:
	g++ -c textdisplay.cpp
window.o:
	g++ -c window.cc
main.o:
	g++ -c main.cpp
clean:
	rm -rf *.o




