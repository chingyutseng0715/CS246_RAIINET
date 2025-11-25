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
import FourPlayerBoard;
import Player;

const int NUM_PLAYERS = 4;

export class FourPlayerMode : public GameMode {
	std::map<PlayerID, bool> eliminatedPlayers; // HOW TO ASSUME IT'S FALSE BY DEFAULT
	int remaining_players = NUM_PLAYERS;
	public:
		FourPlayerMode(const ProcessedInput &input);
		PlayerID runGame() override;
		bool conductPlayerTurn(PlayerID current_player, 
							   std::shared_ptr<Player> current_player_ptr,
							   bool &ability_used);
};
