export module FourPlayerMode;

import <iostream>;
import <fstream>;
import <string>;
import <memory>;
import <vector>;
import <map>;
import CommandLineProcessor;
import GameMode;
import FourPlayerBoard;
import Player;

const int NUM_PLAYERS = 4;

export class FourPlayerMode : public GameMode {
	std::map<PlayerID, bool> eliminatedPlayers; // HOW TO ASSUME IT'S FALSE BY DEFAULT
	int remaining_players = NUM_PLAYERS;
	public:
		FourPlayerMode(const ProcessedInput &input);
		PlayerID runGame() override;
};
