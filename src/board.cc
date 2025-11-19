export module Board;

import <iostream>;
import <vector>;
import <map>;
import Observer;
import Link;

export class Board final {
	int height;
	int width;
	vector<Observer*> players;
	vector<vector<char>> theBoard;
	map<pair<int, int>, Observer*> charLinkMapping;
	public:
		Board(int height, int width);
		void updateBoard(int row, int col, char changed_char);
		char getState(int row, int col);
	friend ostream &operator<<(ostream &, const Board &);
};

export ostream &operator<<(ostream &os, const Board &board);
