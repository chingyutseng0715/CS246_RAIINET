export module FourPlayerBoard;

import <string>;
import Observer;
import Board;

export class FourPlayerBoard: public Board {
	public:
		FourPlayerBoard();
		void addPlayer(Observer *player, std::string linkorder = "V1V2V3V4D1D2D3D4") override;
};
