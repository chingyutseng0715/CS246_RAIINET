module TwoPlayerBoard;

import <memory>;
import <string>;
import Constants;
import Observer;
import Board;
import Link;

using std::make_pair;

TwoPlayerBoard::TwoPlayerBoard(): Board{BOARD_HEIGHT, TWO_PLAYER_BOARD_WIDTH} {
	for (int i = 0; i < width; ++i) { // placing the char on the board
		theBoard[1][i] = 'a' + i;
	}
	theBoard[1][3] = SERVER_PORT_CHAR;
	theBoard[1][4] = SERVER_PORT_CHAR;
	theBoard[2][3] = 'd';
	theBoard[2][4] = 'e';
	for (int i = 0; i < width; ++i) {
        theBoard[height - 2][i] = 'A' + i;
    }
    theBoard[height - 2][3] = SERVER_PORT_CHAR;
    theBoard[height - 2][4] = SERVER_PORT_CHAR;
    theBoard[height - 3][3] = 'D';
    theBoard[height - 3][4] = 'E';
}

void TwoPlayerBoard::addPlayer(Observer *player, std::string link_order) {
	char start_char = 'a';
	if (player->getName() == PLAYER1) { // set the ownership of the coordinate corresponding to the char owned
		start_char = 'a';
		for (int i = 0; i < width; ++i) {
        	charOwner[make_pair(0, i)] = player;
			charOwner[make_pair(1, i)] = player;
    	}
		charOwner[make_pair(2, 3)] = player;
		charOwner[make_pair(2, 4)] = player;
	} else if (player->getName() == PLAYER2) {
		start_char = 'A';
		for (int i = 0; i < width; ++i) {
	        charOwner[make_pair(height - 2, i)] = player;
			charOwner[make_pair(height - 1, i)] = player;
	    }
		charOwner[make_pair(height - 3, 3)] = player;
        charOwner[make_pair(height - 3, 4)] = player;
	}
	for (int i = 0; i < width; ++i) { // construct the links and record the char mapping the the links
		charLinkMapping[start_char + i] = std::make_shared<Link>(player, start_char + i, link_order[2 * i], link_order[2 * i + 1] - '0');
		player->addLink(start_char + i); // be added according to alphabet order
	}
	players.emplace_back(player); // add observer
}
