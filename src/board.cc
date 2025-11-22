export module Board;

import <iostream>;
import <vector>;
import <map>;
import Observer;
import Link;

export class Board {
	protected:
		int height;
		int width;
		std::vector<Observer*> players;
		std::vector<std::vector<char>> theBoard;
		std::map<char, Link> charLinkMapping;
		std::map<std::pair<int, int>, Observer*> charOwner;
	public:
		Board(int height, int width);
		virtual void addPlayer(Observer *player) = 0;
		void updateBoard(int row, int col, char changed_char);
		void setcharOwnership(int row, int col, Observer *player);
		Link* getLink(char link_char);
		char getState(int row, int col);
		Observer *getcharOwnership(int row, int col);
	friend std::ostream &operator<<(std::ostream &, const Board &);
};

export std::ostream &operator<<(std::ostream &os, const Board &board);
