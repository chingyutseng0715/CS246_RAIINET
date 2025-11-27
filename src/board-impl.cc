module Board;

import <iostream>;
import <vector>;
import <map>;
import <stdexcept>;
import Constants;
import Observer;
import Link;

using std::make_pair;

Board::Board(int height, int width): height{height}, width{width} {
	for (int i = 0; i < height; ++i) {
		theBoard.emplace_back(std::vector<char>{});
		for (int j = 0; j < width; ++j) {
			if (i == 0 || i == height - 1) {
				theBoard[i].emplace_back(HORIZONTAL_BORDER_CHAR);
			} else {
				theBoard[i].emplace_back(EMPTY_SQUARE_CHAR);
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
		throw std::invalid_argument("Link not found.");
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
		throw std::invalid_argument("Invalid move.");
	}
	
	Link *link = getLink(link_char);
	Observer *player = link->getPlayer();
	char next_char = theBoard[move_row][move_col];
	std::pair<int, int> pos = make_pair(row, col);
	std::pair<int, int> next_pos = make_pair(move_row, move_col);
	if (next_char == EMPTY_SQUARE_CHAR) {
		theBoard[move_row][move_col] = link_char;
		charOwner[next_pos] = player;
	} else if (firewalls.count(next_pos)) {
		if (firewalls[next_pos] == player) {
			theBoard[move_row][move_col] = link_char;
		} else {
			link->Reveal();
			if (link->isVirus()) {
				player->download(link_char);
			} else {
				theBoard[move_row][move_col] = link_char;
				charOwner[next_pos] = player;
			}
		}
	} else if (charOwner[next_pos] == player || next_char == OBSTACLE_CHAR) {
		throw std::invalid_argument("Invalid move.");
	} else if (next_char == SERVER_PORT_CHAR) {
		charOwner[next_pos]->download(link_char);
	} else if (next_char == HORIZONTAL_BORDER_CHAR) {
		player->download(link_char);
	} else if (getLink(next_char)) {
		Link *other_link = getLink(next_char);
		link->Reveal();
		other_link->Reveal();
		if (*link < *other_link) {
			other_link->getPlayer()->download(link_char);
		} else {
			player->download(next_char);
			theBoard[move_row][move_col] = link_char;
			charOwner[next_pos] = player;
		}
	} else {
		throw std::invalid_argument("Invalid move.");
	}
	
	theBoard[row][col] = EMPTY_SQUARE_CHAR;
    charOwner.erase(pos);
	if (firewalls.count(pos)) {
		setFireWall(row, col, firewalls[pos]);
	}
}

void Board::setFireWall(int row, int col, Observer *player) {
	if (row < 1 || row >= height - 1 || col < 0 || col >= width) {
		throw std::out_of_range("The coordinate of the Firewall is invalid.");
	} else if (theBoard[row][col] != EMPTY_SQUARE_CHAR) {
		throw std::invalid_argument("The designated coordinate is invalid.");
	}
	if (player->getName() == PLAYER1) {
		theBoard[row][col] = PLAYER1_FIREWALL;
	} else if (player->getName() == PLAYER2) {
        theBoard[row][col] = PLAYER2_FIREWALL;
    } else if (player->getName() == PLAYER3) {
        theBoard[row][col] = PLAYER3_FIREWALL;
    } else if (player->getName() == PLAYER4) {
        theBoard[row][col] = PLAYER4_FIREWALL;
    }
	firewalls[make_pair(row, col)] = player;
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
            throw std::out_of_range("Obstacle is outside, cannot be placed.");
        }
        
        if (theBoard[r][c] != EMPTY_SQUARE_CHAR) {
            throw std::invalid_argument("Obstacle position is not empty.");
        }
    }
    
    for (auto [r,c] : positions) {
        theBoard[r][c] = OBSTACLE_CHAR;
    }
}

void Board::infectLink(char link_char, Observer *player) {
	Link *link = getLink(link_char);
	if (link->isInfected()) {
		throw std::invalid_argument("The selected virus is alreadly infected.");
	} else if (!link->isVirus()) {
		throw std::invalid_argument("The selected link is not a virus.");
	} else if (link->getPlayer() != player) {
		throw std::invalid_argument("You cannot infect others' links.");
	}
	link->Infect();
}
	
Link * Board::getLink(char link_char) {
	if (charLinkMapping.count(link_char)) {
		return charLinkMapping[link_char].get();
	}
	std::cout << charLinkMapping.count(link_char);
	return nullptr;
}

char Board::getState(int row, int col) { return theBoard[row][col]; }

Observer * Board::getcharOwnership(int row, int col) {
	if (charOwner.count(make_pair(row, col))) {
		return charOwner[make_pair(row, col)];
	}
	return nullptr;
}

Observer * Board::getPlayer(std::string name) {
	for (Observer *player: players) {
		if (player->getName() == name) {
			return player;
		}
	}
	return nullptr;
}

void Board::printBoard(std::ostream &os, Observer *player) {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			os << theBoard[i][j];
		}
		os << '\n';
	}
	for (size_t i = 0; i < players.size(); ++i) {
		if (players[i] != player) {
			players[i]->printPlayer(os, true);
		}
	}
}
