export module TwoPlayerBoard;

import <string>;
import Constants;
import Observer;
import Board;

export class TwoPlayerBoard: public Board {
	public:
		TwoPlayerBoard();
		void addPlayer(Observer *player, std::string link_order = DEFAULT_LINK_ORDER) override;
};
