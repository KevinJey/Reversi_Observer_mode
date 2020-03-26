#include "textdisplay.h"
#include "subject.h"
#include "info.h"
#include "state.h"
TextDisplay::TextDisplay(int n):gridSize(n)
{
	theDisplay.resize(n);
	for (auto it : theDisplay) {
		it.resize(n);
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			theDisplay[i][j] = '-';
		}
	}
	theDisplay[n / 2 ][n  / 2] = 'B';
	theDisplay[n / 2][n / 2 - 1] = 'W';
	theDisplay[n / 2 - 1][n  / 2] = 'W';
	theDisplay[n / 2 - 1][n / 2 - 1] = 'B';
}

void TextDisplay::notify(Subject<Info, State> &whoNotified)  {

}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {

	for (int i = 0; i < td.gridSize; ++i) {
		for (int j = 0; j < td.gridSize; ++j) {
			out << td.theDisplay[i][j];
		}
		out << std::endl;
	}
	return out;
}
