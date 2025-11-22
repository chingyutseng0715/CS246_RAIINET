export module FourPlayerMode;

import GameMode;

export class FourPlayerMode : public GameMode {
	public:
		FourPlayer();
		void runGame() override;
};
