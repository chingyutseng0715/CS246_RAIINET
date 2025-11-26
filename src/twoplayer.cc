export module TwoPlayerMode;

import <iostream>;
import <fstream>;
import <string>;
import <memory>;
import <vector>;
import Constants;
import CommandLineProcessor;
import GameMode;
import TwoPlayerBoard;
import Player;

const int NUM_PLAYERS = 2;

export class TwoPlayerMode : public GameMode {
	public:
		TwoPlayerMode(const ProcessedInput &input);
		PlayerID runGame() override;
};
