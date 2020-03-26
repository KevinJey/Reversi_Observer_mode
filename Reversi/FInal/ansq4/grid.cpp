#include "grid.h"
#include "textdisplay.h"
#include <iostream>
using namespace std;
Grid::~Grid() {
	this->theGrid.clear();
	
}

void Grid::setObserver(Observer<Info, State> *ob) {

}

bool Grid::isFull() const {
	for (int i = 0; i < this->theGrid.size(); ++i) {
		for (auto single_cell : this->theGrid[i]) {
			if (single_cell.getInfo().colour == Colour::NoColour) return false; //从信息包中判断颜色
		}
	}
	return true;
}

Colour Grid::whoWon() const {
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
	if (white_count == black_count) {
		return Colour::NoColour;
	}
	else if (white_count > black_count) {
		return Colour::White;
	}
	else {
		return Colour::Black;
	}
}


void Grid::init(size_t n) {
	this->theGrid.clear();
	this->theGrid.resize(n);
	//this->td = new TextDisplay(n);
	
	for (int i = 0; i < n; ++i) {
		this->theGrid[i].resize(n);
	}
	for (int i = 0; i < n; ++i) {
		for(int j = 0 ; j < n ; ++j){
			this->theGrid[i][j].setPiece(Colour::NoColour);
		}
	}
	theGrid[n / 2][n/ 2].setPiece(Colour::Black);
	theGrid[n / 2][n / 2 - 1].setPiece(Colour::White);
	theGrid[n / 2 - 1][n / 2].setPiece(Colour::White);
	theGrid[n / 2 - 1][n / 2 - 1].setPiece(Colour::Black);
}

 void Grid::setPiece(size_t r ,size_t c,Colour colour) {  //设置cell的颜色
	 if (this->theGrid[r][c].getInfo().colour != Colour::NoColour) return;
	this->theGrid[r][c].setPiece(colour);
	this->toggle(r, c);
}

 void Grid::toggle(size_t r,size_t c){ //触发 对八个方向进行寻路 发现有同色之后 调用notifyobservers 让每一个对象都被通知到
//被通知到的对象
	 size_t cur_r = r;
	 size_t cur_c = c;
	 Colour cur_color = theGrid[r][c].getInfo().colour;
	 size_t n= theGrid.size();

	 int fr[] = {1,-1,0,0,-1,-1,1,1};
	 int fc[] = {0,0,-1,1,-1,1,-1,1};
	 bool tag = false;
	 for (int d = 0; d < 8; ++d) { //对八个方向上进行讨论
		 tag = false;
		 Subject<Info, State> *op = new Cell();;
		 r = cur_r;
		 c = cur_c;
		 while (1) {
			 r += fr[d];
			 c += fc[d];
			 if (r <0 || c <0 || r >= n || c >= n) break;
			 if (theGrid[r][c].getInfo().colour == cur_color) {
				 tag = true;
				 break;
			 }
			if (theGrid[r][c].getInfo().colour != Colour::NoColour && theGrid[r][c].getInfo().colour != cur_color) {
				op->attach(&theGrid[r][c]); //存下这个格子
			}			
			if(r == 0 || c == 0)
				break;
		 }
		 if (tag) {
			 op->notifyObservers(); //通知所有的观察者 并调用观察者们所提供的notify接口
		 }
	 }
 }
std::ostream &operator<<(std::ostream &out, const Grid &g) {
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