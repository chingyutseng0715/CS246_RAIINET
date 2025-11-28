export module FourPlayerBoard;

import <string>;
import Constants;
import Observer;
import Board;

export class FourPlayerBoard: public Board {
	public:
		FourPlayerBoard();
		void addPlayer(Observer *player, std::string link_order = DEFAULT_LINK_ORDER) override;
};
