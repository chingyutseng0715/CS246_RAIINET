export module FourPlayerMode;

import <istream>;
import <string>;
import GameMode;
import Board;
import Player;

const int NUM_PLAYERS = 4;

export enum class Turn {
	Player1,
	Player2,
	Player3,
	Player4
};

export class FourPlayerMode : public GameMode {
	public:
		FourPlayerMode(std::string ability1_order, std::string ability2_order,
					   std::string ability3_order, std::string ability4_order,
					   std::string link1_order, std::string link2_order,
					   std::string link3_order, std::string link4_order);
		void runGame() override;
};
