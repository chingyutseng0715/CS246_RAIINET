export module FourPlayerMode;

import GameMode;

const int NUM_PLAYERS = 4;

export class FourPlayerMode : public GameMode {
	public:
		FourPlayer();
		void runGame() override;
};
