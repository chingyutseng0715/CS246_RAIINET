module FourPlayerBoard;

import <memory>;
import <string>;
import Constants;
import Observer;
import Board;
import Link;

using std::make_pair;

FourPlayerBoard::FourPlayerBoard(): Board{BOARD_HEIGHT, FOUR_PLAYER_BOARD_WIDTH} {
	for (int i = 0; i < width; ++i) { // consturct the char on the board
		theBoard[1][i] = 'a' + i;
	}
	theBoard[1][3] = SERVER_PORT_CHAR;
	theBoard[1][4] = SERVER_PORT_CHAR;
	theBoard[2][3] = 'd';
	theBoard[2][4] = 'e';
	theBoard[1][11] = SERVER_PORT_CHAR;
    theBoard[1][12] = SERVER_PORT_CHAR;
    theBoard[2][11] = 'l';
    theBoard[2][12] = 'm';
	for (int i = 0; i < width; ++i) {
        theBoard[height - 2][i] = 'A' + i;
    }
    theBoard[height - 2][3] = SERVER_PORT_CHAR;
    theBoard[height - 2][4] = SERVER_PORT_CHAR;
    theBoard[height - 3][3] = 'D';
    theBoard[height - 3][4] = 'E';
	theBoard[height - 2][11] = SERVER_PORT_CHAR;
    theBoard[height - 2][12] = SERVER_PORT_CHAR;
    theBoard[height - 3][11] = 'L';
    theBoard[height - 3][12] = 'M';
}

void FourPlayerBoard::addPlayer(Observer *player, std::string link_order) {
	char start_char = 'a';
	if (player->getName() == PLAYER1) { // set up the coordinate ownership corresponding to the owned char
		start_char = 'a';
		for (int i = 0; i < width / 2; ++i) {
        	charOwner[make_pair(0, i)] = player;
			charOwner[make_pair(1, i)] = player;
    	}
		charOwner[make_pair(2, 3)] = player;
		charOwner[make_pair(2, 4)] = player;
	} else if (player->getName() == PLAYER2) {
		start_char = 'A';
		for (int i = 0; i < width / 2; ++i) {
	        charOwner[make_pair(height - 2, i)] = player;
			charOwner[make_pair(height - 1, i)] = player;
	    }
		charOwner[make_pair(height - 3, 3)] = player;
        charOwner[make_pair(height - 3, 4)] = player;
	} else if (player->getName() == PLAYER3) {
        start_char = 'i';
        for (int i = width / 2; i < width; ++i) {
            charOwner[make_pair(0, i)] = player;
            charOwner[make_pair(1, i)] = player;
        }
        charOwner[make_pair(2, 11)] = player;
        charOwner[make_pair(2, 12)] = player;
    } else if (player->getName() == PLAYER4) {
        start_char = 'I';
        for (int i = width / 2; i < width; ++i) {
            charOwner[make_pair(height - 2, i)] = player;
            charOwner[make_pair(height - 1, i)] = player;
        }
        charOwner[make_pair(height - 3, 11)] = player;
        charOwner[make_pair(height - 3, 12)] = player;
    }
	for (int i = 0; i < width / 2; ++i) { // consturct links and recored the char mapping to the links
		charLinkMapping[start_char + i] = std::make_shared<Link>(player, start_char + i, link_order[2 * i], link_order[2 * i + 1] - '0');
		player->addLink(start_char + i); // added according to alphabet order
	}
	players.emplace_back(player); // add observer
}
