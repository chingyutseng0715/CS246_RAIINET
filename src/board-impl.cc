export module Board;

import <iostream>;
import <vector>;
import <map>;
import Observer;
import Link;

const std::string PLAYER1 = "Player 1";
const std::string PLAYER2 = "Player 2";
const std::string PLAYER3 = "Player 3";
const std::string PLAYER4 = "Player 4";

export class Board final {
	int height;
	int width;
	std::vector<Observer*> players;
	std::vector<std::vector<char>> theBoard;
	std::map<char, Link> charLinkMapping;
	std::map<std::pair<int, int>, Observer*> charOwner;
	public:
Board::Board(int height, int width): height{height + 2}, width{width} {
	for (int i = 0; i < height; ++i) {
		theBoard.emplace_back({});
		for (int j = 0; j < width; ++j) {
			if (i == 0 || i == height - 1) {
				theBoard[i].emplace_back('=');
			} else {
				theBoard[i].emplace_back('.');
			}
		}
	}
}

		
void updateBoard(int row, int col, char changed_char);
		void setcharOwnership(int row, int col, Observer *player);
		Link* getLink(char link_char);
		char getState(int row, int col);
		Observer *getcharOwnership(int row, int col);
	friend std::ostream &operator<<(std::ostream &, const Board &);
};

std::ostream &operator<<(std::ostream &os, const Board &board) {
	for (int i = 0; i < board.height; ++i) {
		for (int j = 0; j < board.width; ++j) {
			os << board.theBoard[i][j];
		}
		os << '\n';
	}
	return os;
}
