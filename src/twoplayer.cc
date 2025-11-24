export module TwoPlayerMode;

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

const int NUM_PLAYERS = 2;

export class TwoPlayerMode : public GameMode {
	public:
		TwoPlayerMode(const ProcessedInput &input);
		PlayerID runGame() override;
		bool conductPlayerTurn(PlayerID current_player, 
							   std::shared_ptr<Player> current_player_ptr,
							   bool &ability_used);
};
