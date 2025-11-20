export module Board;

import <iostream>;
import <vector>;
import <map>;
import Observer;

export class Board final {
	int height;
	int width;
	std::vector<Observer*> players;
	std::vector<std::vector<char>> theBoard;
	std::map<std::pair<int, int>, Observer*> charOwner;
	public:
		Board(int height, int width);
		void updateBoard(int row, int col, char changed_char);
		char getState(int row, int col);
	friend std::ostream &operator<<(std::ostream &, const Board &);
};

export std::ostream &operator<<(std::ostream &os, const Board &board);
