export module TwoPlayerBoard;

import <string>;
import Observer;
import Board;

export class TwoPlayerBoard: public Board {
	public:
		TwoPlayerBoard();
		void addPlayer(Observer *player, std::string linkorder) override;
};
