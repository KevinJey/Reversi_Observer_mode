#include "cell.h"


Cell::Cell(const size_t r , const size_t c):r(r),c(c) {
	this->colour = Colour::NoColour;
}

void Cell::setPiece(Colour set_colour) {
	this->colour = set_colour;
}

void Cell::toggle() {
	if (this->colour == Colour::Black) {
		this->colour = Colour::White;
	}
	else if(this->colour == Colour::White){
		this->colour = Colour::Black;
	}
}
/*
Cell:
		r,c,colour,
		Cell(const size_t r = 0, const size_t c = 0);
		void setPiece(Colour colour);    // Place a piece of given colour here.
		void toggle();         // Toggles my colour.
		void notify(Subject<Info, State> &whoFrom) override;
		Info getInfo() const override;
		void setState(StateType newS);
		void attach(Observer<InfoType, StateType> *o);
		void notifyObservers();
		StateType getState() const;

		template <typename InfoType, typename StateType>
		void Subject<InfoType, StateType>::notifyObservers() {
			for (auto &ob : observers) ob->notify(*this);
		}
*/
void Cell::notify(Subject<Info, State> &whoFrom) {
	
	if (this->colour == Colour::NoColour) return;
	this->toggle();
}

Info Cell::getInfo() const {
	return{ this->r,this->c,this->colour };
}//返回一个信息包

