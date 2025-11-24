module TwoPlayerBoard;

import <memory>;
import <string>;
import Observer;
import Board;
import Link;

using std::make_pair;

const std::string PLAYER1 = "Player 1";
const std::string PLAYER2 = "Player 2";

TwoPlayerBoard::TwoPlayerBoard(): Board{8, 8} {
	for (int i = 0; i < width; ++i) {
		theBoard[1][i] = 'a' + i;
	}
	theBoard[1][3] = 'S';
	theBoard[1][4] = 'S';
	theBoard[2][3] = 'd';
	theBoard[2][4] = 'e';
	for (int i = 0; i < width; ++i) {
        theBoard[height - 2][i] = 'A' + i;
    }
    theBoard[height - 2][3] = 'S';
    theBoard[height - 2][4] = 'S';
    theBoard[height - 3][3] = 'D';
    theBoard[height - 3][4] = 'E';
}

void TwoPlayerBoard::addPlayer(Observer *player, std::string linkorder) {
	char start_char = 'a';
	if (player->getName() == PLAYER1) {
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
	for (int i = 0; i < width; ++i) {
		charLinkMapping[start_char + i] = std::make_shared<Link>(player, start_char + i, linkorder[2 * i], linkorder[2 * i + 1] - '0');
		player->addLink(start_char + i);
	}
	players.emplace_back(player);
}
