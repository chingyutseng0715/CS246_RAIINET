module Board;

import <iostream>;
import <vector>;
import <map>;
import <stdexcept>;
import Observer;
import Link;

using std::make_pair;

const std::string PLAYER1 = "Player 1";
const std::string PLAYER2 = "Player 2";
const std::string PLAYER3 = "Player 3";
const std::string PLAYER4 = "Player 4";

Board::Board(int height, int width): height{height}, width{width} {
	for (int i = 0; i < height; ++i) {
		theBoard.emplace_back(std::vector<char>{});
		for (int j = 0; j < width; ++j) {
			if (i == 0 || i == height - 1) {
				theBoard[i].emplace_back('=');
			} else {
				theBoard[i].emplace_back('.');
			}
		}
	}
}

void Board::updateLink(char link_char, std::string direction) {
	int row = -1;
	int col = -1;
	for (int i = 1; i < height - 1; ++i) {
		for (int j = 0; j < width; ++j) {
			if (theBoard[i][j] == link_char) {
				row = i;
				col = j;
			}
		}
	}
	if (row == -1 && col == -1) {
		throw std::invalid_argument("The link is not found.");
	}
	
	int move_row = row;
	int move_col = col;
	int move = charLinkMapping[link_char].get()->getMovePerStep();
	if (direction == "up") {
		move_row -= move;
		if (move_row < 0) move_row = 0;
	} else if (direction == "down") {
		move_row += move;
		if (move_row > height - 1) move_row = height - 1;
	} else if (direction == "left") {
		move_col -= move;
	} else if (direction == "right") {
		move_col += move;
	} else {
		throw std::invalid_argument("The direction is invalid.");
	}
	
	if (move_col < 0 || move_col >= width) {
		throw std::invalid_argument("Invalid Move.");
	}
	
	Link *link = charLinkMapping[link_char].get();
	Observer *player = link->getPlayer();
	char next_char = theBoard[move_row][move_col];
	if (next_char != '.' && charOwner[make_pair(move_row, move_col)] != player) {
		if (next_char == '=') {
			player->download(link_char);
		} else if (next_char == 'x' || next_char == 'y' || next_char == 'z' || next_char == 'w') {
			link->Reveal();
			if (link->isVirus()) {
				player->download(link_char);
				theBoard[move_row][move_col] = '.';
				charOwner.erase(make_pair(row, col));
			} else {
				theBoard[move_row][move_col] = link_char;
				charOwner[make_pair(move_row, move_col)] = player;
			}
		} else {
			Link *other_link = charLinkMapping[next_char].get();
			link->Reveal();
			other_link->Reveal();
			if (*link < *other_link) {
				other_link->getPlayer()->download(link_char); 
			} else {
				player->download(next_char);
				theBoard[move_row][move_col] = link_char;
                charOwner[make_pair(move_row, move_col)] = player;
			}
		}
	} else if (next_char == 'x' || next_char == 'y' || next_char == 'z' || next_char == 'w'|| next_char == '.') {
		theBoard[move_row][move_col] = link_char;
        charOwner[make_pair(move_row, move_col)] = player;
	} else {
		throw std::invalid_argument("Invalid move.");
	}
	theBoard[row][col] = '.';
	charOwner.erase(make_pair(row, col));
}

void Board::setFireWall(int row, int col, Observer *player) {
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

void Board::setObstacle(int row, int col, char direction) {
    std::vector<std::pair<int, int>> positions;
    positions.emplace_back(std::make_pair(row, col));
    
    if (direction == 'v') {
        positions.emplace_back(std::make_pair(row - 1, col));
        positions.emplace_back(std::make_pair(row + 1, col));
    } else if (direction == 'h') {
        positions.emplace_back(std::make_pair(row, col - 1));
        positions.emplace_back(std::make_pair(row, col + 1));
    } else if (direction == 'r') {
        positions.emplace_back(std::make_pair(row - 1, col - 1));
        positions.emplace_back(std::make_pair(row + 1, col + 1));
    } else if (direction == 'l') {
        positions.emplace_back(std::make_pair(row - 1, col + 1));
        positions.emplace_back(std::make_pair(row + 1, col - 1));
    } else {
		throw std::invalid_argument("Invalid direction.");
	}
    

    for (auto [r,c] : positions) {
        if (r < 1 || r >= height - 1 || c < 0 || c >= width) {
            throw std::out_of_range("Obstacle is outside, cannot be placed");
        }
        
        if ( theBoard[r][c] != '.') {
            throw std::invalid_argument("Obstacle position is not empty");
        }
    }
    
    for (auto [r,c] : positions) {
        theBoard[r][c] = '#';
    }
}

void Board::infectLink(char link_char, Observer *player) {
	Link *link = getLink(link_char);
	if (link->isInfected()) {
		throw std::invalid_argument("The Virus is alreadly infected");
	} else if (!link->isVirus()) {
		throw std::invalid_argument("The Link is not a virus.");
	} else if (link->getPlayer() != player) {
		throw std::invalid_argument("You cannot infect others' link.");
	}
	link->setType('I');
}
	
Link* Board::getLink(char link_char) {
	if (charLinkMapping.count(link_char)) {
		return charLinkMapping[link_char].get();
	}
	return nullptr;
}

char Board::getState(int row, int col) { return theBoard[row][col]; }

Observer *Board::getcharOwnership(int row, int col) {
	if (charOwner.count(make_pair(row, col))) {
		return charOwner[make_pair(row, col)];
	}
	return nullptr;
}

std::ostream &operator<<(std::ostream &os, const Board &board) {
	for (int i = 0; i < board.height; ++i) {
		for (int j = 0; j < board.width; ++j) {
			os << board.theBoard[i][j];
		}
		os << '\n';
	}
	return os;
}
