export module Board;

import <iostream>;
import <vector>;
import <map>;
import Game;
import Link;

export class Board : public Game {
	vector<vector<char>> theBoard;
	map<char, Link*> char_map_link;
	public:
		void updateBoard(int row, int col, char changed_char);
		char getState(int row, int col);
	friend ostream &operator<<(ostream &, const Board &);
};

export ostream &operator<<(ostream &os, const Board &board);
