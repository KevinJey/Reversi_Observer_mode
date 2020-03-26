#include "grid.h"
#include "textdisplay.h"
#include <iostream>
using namespace std;
Grid::~Grid() {
	this->theGrid.clear();
	if(td)
		delete td;
	if(ob)
		delete ob;
	if(this->displayWindows)
		delete displayWindows;
	//release memory 
}

void Grid::setObserver(Observer<Info, State> *ob) {
	this->ob = ob;
}//set one's observer

bool Grid::isFull() const {
	for (int i = 0; i < this->theGrid.size(); ++i) {
		for (auto single_cell : this->theGrid[i]) {//visit them
			if (single_cell.getInfo().colour == Colour::NoColour) return false; 
		}
	}
	return true;
}

Colour Grid::whoWon() const { // do count and return a colour
	int black_count;
	int white_count;
	black_count = white_count = 0;
	for (int i = 0; i < this->theGrid.size(); ++i) {
		for (auto single_cell : this->theGrid[i]) {
			if (single_cell.getInfo().colour == Colour::Black) {
				black_count++;
			}
			else if (single_cell.getInfo().colour == Colour::White) {
				white_count++;
			}
		}
	}
	//call displyWIndows to output on the windwos
	if (white_count == black_count) {
		cout << "No one win! " << endl;
		this->displayWindows->drawString(250,200,"No one win!"); 
		return Colour::NoColour;
	}
	else if (white_count > black_count) {
		cout << "White win!" << endl;
		this->displayWindows->drawString(250,200,"White  win!");
		return Colour::White;
	}
	else {
		cout << "Black win!" << endl;
		this->displayWindows->drawString(250,200,"Black  win!");
		return Colour::Black;
	}
}


//	enum {White=0, Black, Red, Green, Blue}; // Available colours.
void Grid::init(size_t n) {
	this->blockDistance = 500/n;
	int bd = this->blockDistance;
	this->theGrid.clear();
	this->theGrid.resize(n);
	if(this->displayWindows) 
		delete this->displayWindows;
	//this->td = new TextDisplay(n);
	this->displayWindows = new Xwindow();
	this->displayWindows->fillRectangle(0,0,n*bd,n*bd,4); //every cell is blue
	for (int i = 0; i < n; ++i) {
		this->theGrid[i].resize(n);
	}
	for (int i = 0; i < n; ++i) {
		for(int j = 0 ; j < n ; ++j){
			this->theGrid[i][j].setPiece(Colour::NoColour);
		}
	}

	//logical init
	theGrid[n / 2][n/ 2].setPiece(Colour::Black);
	theGrid[n / 2][n / 2 - 1].setPiece(Colour::White);
	theGrid[n / 2 - 1][n / 2].setPiece(Colour::White);
	theGrid[n / 2 - 1][n / 2 - 1].setPiece(Colour::Black);
	//draw on the windows
	this->displayWindows->fillRectangle(n/2*bd,n/2*bd,bd,bd,1);
	this->displayWindows->fillRectangle(n/2*bd,(n/2-1)*bd,bd,bd,0);
	this->displayWindows->fillRectangle((n/2-1)*bd,(n/2)*bd,bd,bd,0);
	this->displayWindows->fillRectangle((n/2-1)*bd,(n/2-1)*bd,bd,bd,1);


}

 void Grid::setPiece(size_t r ,size_t c,Colour colour) {  
	 //set the place and the colour
	if (this->theGrid[r][c].getInfo().colour != Colour::NoColour) return;
	int bd = this->blockDistance;
	int color_option = colour == Colour::Black ?1 : 0;
	this->displayWindows->fillRectangle(r*bd,c*bd,bd,bd,color_option);
	this->theGrid[r][c].setPiece(colour);
	this->toggle(r, c);
}

 void Grid::toggle(size_t r,size_t c){  //when you put a chess use it to search 
	 size_t cur_r = r;
	 size_t cur_c = c;
	 Colour cur_color = theGrid[r][c].getInfo().colour;
	 size_t n= theGrid.size();

	 int fr[] = {1,-1,0,0,-1,-1,1,1};
	 int fc[] = {0,0,-1,1,-1,1,-1,1}; //indicate eight direction
	 bool tag = false;
	 for (int d = 0; d < 8; ++d) { //visit the direction array
		 tag = false;
		 Subject<Info, State> *op = new Cell(); 
		 r = cur_r;
		 c = cur_c;
		 
		 while (1) {
			 r += fr[d];
			 c += fc[d];
			 if (r <0 || c <0 || r >= n || c >= n) {
				 break;
			 }
			 
			 if (theGrid[r][c].getInfo().colour == cur_color) {
				 tag = true;
				 break;
			 }
			 if(theGrid[r][c].getInfo().colour == Colour::NoColour){
				 break;
			 }
			if (theGrid[r][c].getInfo().colour != Colour::NoColour && theGrid[r][c].getInfo().colour != cur_color) {
				op->attach(&theGrid[r][c]); // let them into vector
			}			
			
		 }
		 if (tag) {
			 op->notifyObservers(); //called the observer provided api
		 }
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				int bd = this->blockDistance;
				Colour currentColour = this->theGrid[i][j].getInfo().colour ;
				int colour = (currentColour == Colour::White ? 0 : currentColour == Colour::Black ?1 : 4);
				this->displayWindows->fillRectangle(j*bd,i*bd,bd,bd,colour); // draw them on the windwos again 
			}
		}
		delete op;
	}
 }
std::ostream &operator<<(std::ostream &out, const Grid &g) { //out put the char on terminal 
	int n = g.theGrid.size();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			Colour cur_colour = g.theGrid[i][j].getInfo().colour;
			if (cur_colour == Colour::NoColour) {
				out << "-";
			}
			else if (cur_colour == Colour::Black) {
				out << "B";
			}
			else {
				out << "W";
			}
		}
		out << std::endl;
	}
	return out;
}
