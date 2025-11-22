export module TwoPlayerMode;

import GameMode;

const int NUM_PLAYERS = 2;

export class TwoPlayerMode : public GameMode {
	public:
		TwoPlayerMode(std::string ability1_order, std::string ability2_order,
					  std::string link1_order, std::string link2_order);
		void runGame() override;
};
