export module TwoPlayerMode;

import GameMode;

export class TwoPlayerMode : public GameMode {
	public:
		TwoPlayerMode();
		void runGame() override;
};
