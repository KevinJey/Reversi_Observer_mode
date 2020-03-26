#ifndef CELL_H
#define CELL_H
#include <cstddef>
#include "state.h"
#include "subject.h"
#include "observer.h"
#include "info.h"

class Cell : public Subject<Info, State>, public Observer<Info, State> {
	const size_t r, c;
	Colour colour = Colour::NoColour;

	// Add other private members if necessary

public:
	Cell(const size_t r = 0, const size_t c = 0);

	void setPiece(Colour colour);    // Place a piece of given colour here.
	void toggle();         // Toggles my colour.

	void notify(Subject<Info, State> &whoFrom) override;// My neighbours will call this
														// when they've changed state
														//继承observer类而来的方法 覆写重构
														
	Info getInfo() const override;
};
#endif
