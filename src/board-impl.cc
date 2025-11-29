module Board;

import <iostream>;
import <vector>;
import <map>;
import <stdexcept>;
import <algorithm>;
import Constants;
import Observer;
import Link;

using std::make_pair;

Board::Board(int height, int width): height{height}, width{width}, obstacle_tick{0} {
	for (int i = 0; i < height; ++i) { // construct the board with empty square and the boarder only
		theBoard.emplace_back(std::vector<char>{});
		for (int j = 0; j < width; ++j) { // note that the row includes the border
			if (i == 0 || i == height - 1) { // so the coordinate needs to be shifted
				theBoard[i].emplace_back(HORIZONTAL_BORDER_CHAR);
			} else {
				theBoard[i].emplace_back(EMPTY_SQUARE_CHAR);
			}
		}
	}
}

void Board::battle(char link_char, char other_link_char) {
	Link *link = getLink(link_char);
	Link *other_link = getLink(other_link_char);
	std::pair<int, int> next_pos = getIndex(other_link_char);
	if (link && other_link) {
		// Reveal both links
        link->Reveal();
        other_link->Reveal();
        if (*link < *other_link) { // If other_link is stronger than link, let it's owner download link
            downloadLink(other_link->getPlayer(), link_char);
        } else { // Otherwise, let the owner of link download other_link and move the link
            downloadLink(link->getPlayer(), other_link_char);
			charOwner[next_pos] = link->getPlayer();// move the link
			theBoard[next_pos.first][next_pos.second] = link_char;
        }
    }
}

std::pair<int, int> Board::getIndex(char link_char) {
	for (int i = 1; i < height - 1; ++i) {
		for (int j = 0; j < width; ++j) {
			if (theBoard[i][j] == link_char) {
				return make_pair(i, j);
			}
		}
	}
	throw std::invalid_argument("Link not found.");
}

bool Board::movable(char link_char) {
	std::pair<int, int> pos = getIndex(link_char);
	Link *link = getLink(link_char);
	Observer *player = link->getPlayer();
	int row = pos.first;
	int col = pos.second;
	int move = link->getMovePerStep();
	std::vector<std::pair<int, int>> possible_pos;
	
	// emplacing possible coordinates to move to
	possible_pos.emplace_back(make_pair(std::max(0, row - move), col));
	possible_pos.emplace_back(make_pair(std::min(height - 1, row + move), col));
	possible_pos.emplace_back(make_pair(row, col + move));
	possible_pos.emplace_back(make_pair(row, col - move));
	
	for (std::pair<int, int> cur_pos: possible_pos) {
		if (cur_pos.second < 0 || cur_pos.second >= width) { // cannot escape off other boarders
			continue;
		}
		// cannot move to obstacle or over the player's own part
		if (theBoard[cur_pos.first][cur_pos.second] == OBSTACLE_CHAR || (charOwner.count(cur_pos) && charOwner[cur_pos] == player)) {
			continue;
		} else {
			return true;
		}
	}
	return false;
}
	
	
void Board::downloadLink(Observer *player, char link_char) {
	std::pair<int, int> pos = getIndex(link_char);
	theBoard[pos.first][pos.second] = EMPTY_SQUARE_CHAR;
	charOwner.erase(pos); // remove the link from the board
	if (firewalls.count(pos)) { // check if the original places is a firewall
		setFirewall(pos.first, pos.second, firewalls[pos]);
	}
	player->download(link_char); // notify the player to download it
}

void Board::updateLink(char link_char, std::string direction) {
	std::pair<int, int> pos = getIndex(link_char);
	int row = pos.first;
	int col = pos.second;
	
	int move_row = row;
	int move_col = col;
	int move = charLinkMapping[link_char].get()->getMovePerStep();
	if (direction == "up") { // valid direction checking and coordinates calculating
		move_row = std::max(move_row - move, 0);
	} else if (direction == "down") {
		move_row = std::min(move_row + move, height - 1);
	} else if (direction == "left") {
		move_col -= move;
	} else if (direction == "right") {
		move_col += move;
	} else {
		throw std::invalid_argument("The direction is invalid.");
	}
	
	if (move_col < 0 || move_col >= width) { // cannot escape of the side border
		throw std::invalid_argument("Invalid move.");
	}
	
	Link *link = getLink(link_char);
	Observer *player = link->getPlayer();
	char next_char = theBoard[move_row][move_col]; // the char of the coordinates to move to
	std::pair<int, int> next_pos = make_pair(move_row, move_col);
	if ((charOwner.count(next_pos) && charOwner[next_pos] == player) || next_char == OBSTACLE_CHAR) {
        throw std::invalid_argument("Invalid move."); // one cannot move to obstacle or its own stuff (excluding firewall)
    }
	
	if (firewalls.count(next_pos)) { // firewall is the top priority to check
		if (firewalls[next_pos] != player) { // firewall only affect the link not belonged to who place the firewall
            link->Reveal();
            if (link->isVirus()) {
                downloadLink(player, link_char);
				next_char = EMPTY_SQUARE_CHAR; // this is just to avoid entering any following if
            }
        }
	}
	
	if (next_char == SERVER_PORT_CHAR) { // ports download behaviour
		downloadLink(charOwner[next_pos], link_char);
	} else if (next_char == HORIZONTAL_BORDER_CHAR) { // opponent board download behaviour
		downloadLink(player, link_char);
	} else if (getLink(next_char)) { // if valid for battle
		battle(link_char, next_char);
    } 
	
	if (!link->isDownloaded()) { // process the original pos if not downloaded (if downloaded, the original pos is processed)
		theBoard[move_row][move_col] = link_char;
        charOwner[next_pos] = player;
        theBoard[row][col] = EMPTY_SQUARE_CHAR;
        charOwner.erase(pos);
        if (firewalls.count(pos)) { // check if the original pos is a firewall
            setFirewall(row, col, firewalls[pos]);
        }
	}
	
	if (obstacle_tick > 0) { // deduct the count for obstacle if obstacle exists (0 means not exist)
		obstacle_tick -= 1;
		if (obstacle_tick == 0) { // if the count goes to 0, erase the obstacle
			for (int i = 1; i < height - 1; ++i) {
				for (int j = 0; j < width; ++j) {
					if (theBoard[i][j] == OBSTACLE_CHAR) {
						theBoard[i][j] = EMPTY_SQUARE_CHAR;
					}
				}
			}
		}
	}
}

void Board::setFirewall(int row, int col, Observer *player) {
	if (row < 1 || row >= height - 1 || col < 0 || col >= width) {
		throw std::out_of_range("The coordinate of the Firewall is invalid.");
	} else if (theBoard[row][col] != EMPTY_SQUARE_CHAR) {
		throw std::invalid_argument("The designated coordinate is invalid.");
	}
	if (player->getName() == PLAYER1) { // check which symbol to place for firewall w.r.t player
		theBoard[row][col] = PLAYER1_FIREWALL;
	} else if (player->getName() == PLAYER2) {
        theBoard[row][col] = PLAYER2_FIREWALL;
    } else if (player->getName() == PLAYER3) {
        theBoard[row][col] = PLAYER3_FIREWALL;
    } else if (player->getName() == PLAYER4) {
        theBoard[row][col] = PLAYER4_FIREWALL;
    }
	firewalls[make_pair(row, col)] = player; // record the firewall placer by coordinates
}

void Board::setObstacle(int row, int col, char direction) {
	if (obstacle_tick != 0 ) {
		throw std::invalid_argument("Only one obstacle can exist at once.");
	}
	
    std::vector<std::pair<int, int>> positions;
    positions.emplace_back(std::make_pair(row, col));
    
    if (direction == 'v') { // different directions of the obstacles
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
    

    for (auto [r,c] : positions) { // check if all the positions are valid
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
	
	obstacle_tick = OBSTACLE_ROUND * players.size(); // the obstacles can last for only 3 rounds (see constants.cc)
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
	return nullptr; // if not found
}

int Board::getObstacleTick() { return obstacle_tick; }

Observer * Board::getPlayer(std::string name) {
	for (Observer *player: players) {
		if (player->getName() == name) {
			return player;
		}
	}
	return nullptr;
}

void Board::eliminatePlayer(Observer *player) {
	for (int i = 1; i < height - 1; ++i) { // we need to leave the border
		for (int j = 0; j < width; ++j) {
			std::pair<int,int> pos = make_pair(i, j); // eliminate the firewalls, ports, links the player placed
			if ((charOwner.count(pos) && charOwner[pos] == player) || (firewalls.count(pos) && firewalls[pos] == player)) {
				if (getLink(theBoard[i][j])) {
					getLink(theBoard[i][j])->Download(); // we mark the links as downloaded as not on the board
				}
				theBoard[i][j] = EMPTY_SQUARE_CHAR;
				charOwner.erase(pos);
				if (firewalls.count(pos)) { // remove the firewalls
					if (firewalls[pos] == player) {
						firewalls.erase(pos);
					} else {
						setFirewall(i, j, firewalls[pos]); // set back the firewalls if occupied by links
					}
				}
			}
		}
	}
	for (auto it = players.begin(); it != players.end(); ++it) {
		if (*it == player) {
			players.erase(it); // erase the player from observers list
			break;
		}
	}
}
					
void Board::printBoard(std::ostream &os, Observer *player) {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			os << theBoard[i][j];
		}
		os << std::endl;
	}
	for (size_t i = 0; i < players.size(); ++i) {
		if (players[i] != player) {
			players[i]->printPlayer(os, true);
		}
	}
}
