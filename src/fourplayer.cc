export module FourPlayerMode;

import <iostream>;
import <fstream>;
import <string>;
import <memory>;
import <vector>;
import CommandLineProcessor;
import GameMode;
import FourPlayerBoard;
import Player;

const int NUM_PLAYERS = 4;

export class FourPlayerMode : public GameMode {
	std::vector<bool> eliminated_players;
	std::vector<PlayerID> player_order = {PlayerID::Player1, PlayerID::Player2, 
										  PlayerID::Player3, PlayerID::Player4};
	int remaining_players = NUM_PLAYERS;
	public:
		FourPlayerMode(const ProcessedInput &input);
		PlayerID runGame() override;
};
