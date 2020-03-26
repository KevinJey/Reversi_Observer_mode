#include <iostream>
#include <string>
#include <cstring>
// You may include other allowed headers, as needed
#include "grid.h"
#include "state.h"
#include "window.h"
using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
	cin.exceptions(ios::eofbit | ios::failbit);
	string cmd;

	Colour cur_colour = Colour::Black; //Set the primary colour first.
	Grid g;

	// Add code here
	vector<vector<bool > > vis; //use the varible to make sure every block is visited only once
	int grid_size = -1; 
	bool started = false ; //you should start the game first
	try {
		while (true) {
			cin >> cmd;
			if (cmd == "new") {
				int n;
				cin >> n;
				grid_size = n;
				g.init(n); //create a gird an draw it on a window
				//vis init
				vis.clear();
				vis.resize(n);
			
				for (int k = 0; k < n; ++k){
					vis[k].resize(n);
					for(int j = 0 ; j < n ; ++j) vis[k][j] = false; //make sure every block not be visited
				} 
				
				vis[n / 2][n / 2] = true;
				vis[n / 2][n / 2 - 1] = true;
				vis[n / 2 - 1][n / 2] = true;
				vis[n / 2 - 1][n / 2 - 1] = true;//the beginning four block 
				// Add code here
				cout << g ; //using operator<< to output
				started = true;
				if(n == 2){
					g.whoWon(); //special situation shoule be deal with specialy
				}
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
				}//visit judgement 

				if (r < 0 || r >= grid_size) {
					cout << "Enter Error!" << endl;
					cout << g;
					continue;
				}
				if (c < 0 || c >= grid_size) {
					cout << "Eenter Error" << endl;
					cout << g;
					continue;
				}//make sure not outrange
				// Add code here

				g.setPiece(r, c, cur_colour);//set a cell's colour
				vis[r][c] = true;//make sure it has been visited and mark it in vector<vector<>>
				
				if (cur_colour == Colour::Black) {//change the colour state
					cur_colour = Colour::White;
				}
				else {
					cur_colour = Colour::Black;
				}
				cout << g ;				
				if (g.isFull()) {
					 g.whoWon(); //call whoWon and output the final outcome
				}
			}
			else if (cmd == "exit") { //say byebye
				return 0;
		}
		}
	}
	catch (ios::failure &) {}  // Any I/O failure quits
}
