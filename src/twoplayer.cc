export module TwoPlayerMode;

import <istream>;
import <string>;
import <stdexcept>;
import <vector>;
import <memory>;
import GameMode;
import Board;
import Player;

const int NUM_PLAYERS = 2;
const std::string PLAYER1 = "Player 1";
const std::string PLAYER2 = "Player 2";
const std::string PLAYER1_VALID_LINKS = "abcdefgh";
const std::string PLAYER2_VALID_LINKS = "ABCDEFGH";
const int DATA_DOWNLOADS_TO_WIN = 4;
const int VIRUS_DOWNLOADS_TO_LOSE = 4;

export class TwoPlayerMode : public GameMode {
	public:
		TwoPlayerMode(std::string ability1_order, std::string ability2_order,
					  std::string link1_order, std::string link2_order);
		Winner runGame() override;
};
