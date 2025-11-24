export module FourPlayerMode;

import <iostream>;
import <fstream>;
import <istream>;
import <string>;
import <memory>;
import <vector>;
import <map>;
import <stdexcept>;
import GameMode;
import CommandLineProcessor;
import Board;
import Player;

const int NUM_PLAYERS = 4;

export class FourPlayerMode : public GameMode {
	public:
		FourPlayerMode(const ProcessedInput &input);
		Player runGame() override;
};
