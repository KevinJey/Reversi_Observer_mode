#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "grid.h"
#include "state.h"
using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
	cin.exceptions(ios::eofbit | ios::failbit);
	string cmd;

	Colour cur_colour = Colour::Black;
	Grid g;

	// Add code here
	vector<vector<bool > > vis;
	int grid_size = -1;
	bool started = false;
	try {
		while (true) {
			cin >> cmd;
			if (cmd == "new") {
				int n;
				cin >> n;
				grid_size = n;
				g.init(n);
				vis.resize(n);
				for (int k = 0; k < n; ++k) vis[k].resize(n);
				vis[n / 2][n / 2] = true;
				vis[n / 2][n / 2 - 1] = true;
				vis[n / 2 - 1][n / 2] = true;
				vis[n / 2 - 1][n / 2 - 1] = true;
				// Add code here
				cout << g ;
				started = true;
			}
			else if (cmd == "play") {
				if (started == false) {
					cout << "Please start a new game frist!" << endl;
					continue;
				}
				int r = 0, c = 0;
				cin >> r >> c;
				if (vis[r][c]) {
					cout << "You can't do this!" << endl;
					continue;
				}

				if (r < 0 || r >= grid_size) {
					cout << "Enter Error!" << endl;
					cout << g;
					continue;
				}
				if (c < 0 || c >= grid_size) {
					cout << "Eenter Error" << endl;
					cout << g;
					continue;
				}
				// Add code here

				g.setPiece(r, c, cur_colour);
				if (cur_colour == Colour::Black) {
					cur_colour = Colour::White;
				}
				else {
					cur_colour = Colour::Black;
				}
				cout << g ;				
				if (g.isFull()) {
					Colour winner = g.whoWon();
					if (winner == Colour::Black) {
						cout << "Black win!" << endl;
					}
					else {
						cout << "White win" << endl;
					}
					return 0;
				}
			}
			else if (cmd == "exit") {
				return 0;
		}
		}
	}
	catch (ios::failure &) {}  // Any I/O failure quits
}
