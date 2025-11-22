export module Board;

import <iostream>;
import <vector>;
import <map>;
import <stdexcept>;
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

void Board::updateLink(int row, int col, char link_char) {

void setFireWall(int row, int col, Observer *player) {
	if (row < 1 || row >= height - 1 || col < 0 || col >= width) {
		throw std::out_of_range("The coordinate of the Firewall is invalid.");
	} else if (theBoard[row][col] != '.') {
		throw std::invalid_argument("The designated coordinate is invalid.");
	}
	if (player->getName() == PLAYER1) {
		theBoard[row][col] = 'x';
	} else if (player->getName() == PLAYER2) {
        theBoard[row][col] = 'y';
    } else if (player->getName() == PLAYER3) {
        theBoard[row][col] = 'z';
    } else if (player->getName() == PLAYER4) {
        theBoard[row][col] = 'w';
    }
	charOwner[make_pair(row, col)] = player;
}

Link* getLink(char link_char);
char getState(int row, int col);
Observer *getcharOwnership(int row, int col);

std::ostream &operator<<(std::ostream &os, const Board &board) {
	for (int i = 0; i < board.height; ++i) {
		for (int j = 0; j < board.width; ++j) {
			os << board.theBoard[i][j];
		}
		os << '\n';
	}
	return os;
}
