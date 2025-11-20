export module TwoPlayerMode;

import GameMode;

export class TwoPlayerMode: public GameMode {
	public:
		void operatingGame() override;
};
