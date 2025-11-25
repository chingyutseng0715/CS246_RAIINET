export module TwoPlayerBoard;

import <string>;
import Observer;
import Board;

export class TwoPlayerBoard: public Board {
	public:
		TwoPlayerBoard();
		void addPlayer(Observer *player, std::string linkorder = "V1V2V3V4D1D2D3D4") override;
};
