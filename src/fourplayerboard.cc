export module FourPlayerBoard;

import <string>;
import Constants;
import Observer;
import Board;

export class FourPlayerBoard: public Board {
	public:
		// Constructor; create the board for a game with four players
		FourPlayerBoard();

		// addPlayer(player, link_order) add the given player to the board, and set their links
		//   to be associated with the given link_order
		void addPlayer(Observer *player, std::string link_order = DEFAULT_LINK_ORDER) override;
};
