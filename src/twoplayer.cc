export module TwoPlayerMode;

import GameMode;

const int NUM_PLAYERS = 2;

export class TwoPlayerMode : public GameMode {
	public:
		TwoPlayerMode();
		void runGame() override;
};
